#include <stdio.h>
#include <argp.h>
#include <stdlib.h>
#include <string.h>
#include "switchs.h"
#include "libhpd/libhpd.h"
#include <errno.h>
#include <ctype.h>
#include <unistd.h>
int *cores = NULL;
int corec = 0;
int **corets;//Will point to an Array of ts pointers, set by parsecores() 
int **coretsb; // 2nd array of pointers for comparison with the 1st
bool cpuload = false;
unsigned int time = 3;
void printbasicstats(int core, int time) {
	float load = 1 - cpustm(core, STAT_IDLE, time);
	printf("CPU Load: %.2f%%\n",load*100);
}
int parsecores(char *str, int ***ts, int ***tsb) {
	int i=0; //Place in str
	int x=0; //Digits in buf
	int corecount=0;
	char strbuf[sizeof(char)*10];
	int *intbuf = malloc(sizeof(int *));
	if(intbuf == NULL) {
		exit(12);
	}	
	while(i < strlen(str)) {
		while(isdigit(str[i]) != 0) {
			strbuf[x] = str[i];
			x++;
			i++;
		} 
		x=0;
		i++;
		corecount++;
		intbuf = realloc(intbuf, sizeof(int) * corecount+1);
		if (intbuf == NULL) {
			exit(12);
		}
		intbuf[corecount] = atoi(strbuf);
		memset(strbuf, 0, sizeof strbuf);
	}
	*ts = malloc(sizeof(int *)*corecount+1);
	*tsb = malloc(sizeof(int *)*corecount+1);

	for(i =1; i<=corecount; i++) {
		ts[0][i] = gettscpu(intbuf[i]);
	}
	sleep(time);
	for(i=1; i<=corecount; i++) {
		tsb[0][i] = gettscpu(intbuf[i]);
	}	
	free(intbuf);
	return corecount;
}
void listcpuload() {
	if(corec > 0) {
	int i=1;
	while(i<=corec) {
	float *coreps = tspercents(corets[i], coretsb[i]);
		printf(
		"Core: %i\n"
		"User: %f\n"
		"Nice: %f\n"
		"System: %f\n"
		"Idle: %f\n"
		"IOwait: %f\n"
		"IRQ: %f\n"
		"SoftIRQ: %f\n"
		"Steal: %f\n"
		"Guest: %f\n"
		"Niced Guest: %f\n\n",
		corets[i][0],coreps[1],coreps[2],coreps[3],coreps[4],coreps[5],coreps[6],coreps[7],coreps[8],coreps[9],coreps[10]);
			i++;
		}
	} 
	else {
	float *coreps = tspercents(corets[0], coretsb[0]);
		printf(
		"Core: All\n"
		"User: %f\n"
		"Nice: %f\n"
		"System: %f\n"
		"Idle: %f\n"
		"IOwait: %f\n"
		"IRQ: %f\n"
		"SoftIRQ: %f\n"
		"Steal: %f\n"
		"Guest: %f\n"
		"Niced Guest: %f\n\n",
		coreps[1],coreps[2],coreps[3],coreps[4],coreps[5],coreps[6],coreps[7],coreps[8],coreps[9],coreps[10]);
		}
}
const char *argp_program_version = VERSION; //Define program version according to compiler argument -DVERSION
static char doc[] = "A terminal frontend to libHPD, a library that displays hardware data on linux machines";
static struct argp_option options[] = {
	{"cpuload",  'l', 0,      0,  "Display CPU load", 0 },
	{"core", 'c',     "CORE(s)",      0,  "Specify the CPU cores to display data for in a comma-separated-list.", 0},
	{"time", 't',     "time",      0,  "Specify the amount of seconds between timestamps.", 0},
	{ 0 }
};


static error_t parse_opt(int key, char *arg, struct argp_state *state) {

	switch(key)
	{

		case 'c': 
			corec = parsecores(arg, &corets, &coretsb);
			if(corec < 0){
				printf("Error parsing list: {%s} Ensure all values are separated by any non numeric character (i.e ',') and are only integers.", arg);
				exit(1);
			}
		break;

		case 'l':
			cpuload = true;
		break;
		case 't':
			for(int i=0; i<strlen(arg); i++) {
				if(isdigit(arg[i] != true)) {
					printf("Error parsing time value: %s\n", arg);
					exit(1);
				}
			}
			time = atoi(arg);
		break;
		case ARGP_KEY_ARG:
			printf("Unknown argument: %s\n", arg);
			argp_usage(state);
		break;

		default:
			return ARGP_ERR_UNKNOWN;
	}
	return 0;
}

// Options for argp
static struct argp argp = { options, parse_opt, 0, doc, 0, 0, 0 };


int main(int argc, char **argv) {
	
	if(argc <= 1) {
		printf("You must give tstats arguments for it to be useful.\n");
		exit(0);
	}
	if(argp_parse(&argp, argc, argv, 0, 0, NULL) != 0) {
		printf("Error parsing arguments");
		exit(1);
	}
	if(corec==0) {
		corets = malloc(sizeof(int**));
		coretsb = malloc(sizeof(int**));
		corets[0] = gettscpu(-1);
		sleep(time);
		coretsb[0] = gettscpu(-1);
		corec = -1; 
	}
	if(cpuload == true) {
		listcpuload();
		exit(0);
	}
	free(corets);
	free(coretsb);
}
