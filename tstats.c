#include <stdio.h>
#include "switchs.h"
#include "libhpd/libhpd.h"
int core = -1;
unsigned int time = 3;
void printhelptext() {
	printf("tstats - a terminal program for performance data\n"
		    "\n"
		    "usage: tstats [options]\n"
		    "\n"
		    "options:\n"
		    "-s displays the percent of time the cpu has spent on tasks\n");
}
	
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
int main(int argc, char* argv[]) {
	
	if(argc > 1) {
			for(int i = 1; i < argc; i++) {
				switchs(argv[i]) {
					cases("--help")
						printhelptext();
						return 0;
						break;
					cases("-s")
						printcputasks(-1, 3);
						break;
				    defaults
						printf("Invalid argument(s): \"%s\"\n", argv[i]);
						printhelptext();
						return 1;
						break;
					} switchs_end;
			}
	}
	else { 
		printbasicstats(-1, 3);
		return 0;
		}
				
}
