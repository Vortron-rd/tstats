#include <stdio.h>
#include <argp.h>
#include <stdlib.h>
#include "switchs.h"
#include "libhpd/libhpd.h"
	
void printcputasks(int core, int time) {	
	float *stats = cpustats(core, time);
	printf("User: %f\n"
		   "Nice: %f\n"
		   "System: %f\n"
		   "Idle: %f\n"
		   "IOwait: %f\n"
		   "IRQ: %f\n"
		   "SoftIRQ: %f\n"
		   "Steal: %f\n"
		   "Guest: %f\n"
		   "Niced Guest: %f\n"
		   ,stats[1],stats[2],stats[3],stats[4],stats[5],stats[6],stats[7],stats[8],stats[9],stats[10]);
}

void printbasicstats(int core, int time) {
	float load = 1 - cpustm(core, STAT_IDLE, time);
	printf("CPU Load: %.2f%%\n",load*100);
}
const char *argp_program_version = VERSION; //Define program version according to compiler argument -DVERSION
static char doc[] = "A terminal frontend to libHPD- A library that displays hardware data on linux machines";
static struct argp_option options[] = {
  {"cpuload",  'l', 0,      0,  "Display CPU load", 0 },
  { 0 }
};
struct arguments{
  bool cpuload; 
};

static error_t parse_opt(int key, char *arg, struct argp_state *state)
{
  struct arguments *arguments = state->input;

  switch(key)
    {
    case 'l':
      arguments->cpuload = true;
      break;

    case ARGP_KEY_ARG:
    	printf("Unknowm Argument: %s", arg);
        argp_usage (state);
	break;

    default:
      return ARGP_ERR_UNKNOWN;
    }
  return 0;
}

// Options for argp
static struct argp argp = { options, parse_opt, 0, doc, 0, 0, 0 };


int
main(int argc, char **argv)
{
	struct arguments arguments;
	int core = -1;
	unsigned int time = 3;
	argp_parse(&argp, argc, argv, 0, 0, &arguments);
	printf("Gathering data...\n\n");
	if(argc <= 1) {
		printbasicstats(core, time);
	}
	if(arguments.cpuload == true) {
		printcputasks(core, time); 
	}
	
	exit(0);
}
