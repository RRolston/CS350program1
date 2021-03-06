//Raymond Rolston, Joe Kim, Cameron Parlman
//CS350
//due 3/21/16
//Programming Assignment 1
//Lab4
/*SUMMARY:
-takes max table size, number of commands wished to generate, and an optional max processes as input
-randomly generates commands based on number of processes implemented
-will be useful for finding averages over a large use of different processes
*/

#include<stddef.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include <assert.h>
#include<time.h>

#define MAX_PID 32768//max on my personal system

void Start(unsigned int, unsigned int, FILE*);
void Terminate(unsigned int, FILE*);
void Reference(unsigned int, unsigned int, FILE*);

int main(int argc, char *argv[]) {
//quick argument check-----------------------------------------
  if(argc!=4 && argc!=5){
    fprintf(stderr,"Unacceptable number of arguments %d encountered.", argc);
    fprintf(stderr," ./lab4  <input-file> <max-address-size> <number-of-commands> <max-processes(optional)>");
    exit(1);
  }
//-----------------------------------------------------------

time_t t;
/* Intializes random number generator */
   srand((unsigned) time(&t));

//Variables------------------------------------------------------
FILE * oFile;
oFile = fopen(argv[1],"w");
char *ptr;
unsigned int PID_MAX=MAX_PID;//max on my personal system
if(argc==5){
  PID_MAX = strtol(argv[4], &ptr, 10);
}
if(PID_MAX>MAX_PID) PID_MAX=MAX_PID;
const unsigned int MAX_SIZE = strtol(argv[2], &ptr, 10);
const unsigned long long int COMMAND_SIZE = strtol(argv[3], &ptr, 10);
//int Pid[PID_MAX]={0};//process IDs 1 or 0 for running or not running
int* Pid = (int*) malloc(sizeof(unsigned int)*PID_MAX);
unsigned int j;
for (j = 0; j < PID_MAX; j++){
  Pid[j] = 0;
}
unsigned int* Address = (unsigned int*) malloc(sizeof(unsigned int)*PID_MAX);
assert(Address);
//unsigned int Address[PID_MAX];//address size of each process ID
unsigned long long int command_count=0;
unsigned int processes=1;

while(command_count<COMMAND_SIZE){
  unsigned int p_id= rand()%processes;
  unsigned int address_size= (rand()%MAX_SIZE)+1;
  int s=rand()%3;
  switch(s){
    case 0:
      if(Pid[p_id]==0){
        Pid[p_id]=1;
        Address[p_id]=address_size;
        Start(p_id,address_size,oFile);
        if(processes<PID_MAX) processes++;
        break;
      }else{
        unsigned int vpn = rand()%Address[p_id];
        Reference(p_id,vpn,oFile);
	break;
      }
    case 1:
      if(Pid[p_id]==0){
        Pid[p_id]=1;
        Address[p_id]=address_size;
        Start(p_id,address_size,oFile);//print to file
        if(processes<PID_MAX) processes++;
        break;
      }else{
        unsigned int vpn = rand()%Address[p_id];
        Reference(p_id,vpn,oFile);//print to file
        break;
      }
    case 2:
      if(Pid[p_id]==0){
        Pid[p_id]=1;
        Address[p_id]=address_size;
        Start(p_id,address_size,oFile);//print to file
        break;
      }else{
        Pid[p_id]=0;
        Terminate(p_id,oFile);
        break;
      }
  }
  command_count++;
}
//new code to terminate all processes on exit as requested by lab 4 new requirements
int j;
for(j=0; j<processes; j++){
  if(Pid[j]!=0){
    Pid[j]=0;
    Terminate(j,oFile);
  }
}
//end new code
fclose(oFile);
//-----------------------------------------------------------


return 0;
}
void Start(unsigned int process_number,unsigned  int address_space_size, FILE* outputFile){
  fprintf(outputFile, "START %u %u\n", process_number, address_space_size);
}
void Terminate(unsigned int process_number, FILE* outputFile){
  fprintf(outputFile, "TERMINATE %u\n", process_number);
}
void Reference(unsigned int process_number, unsigned int virtual_page_number, FILE* outputFile){
  fprintf(outputFile, "REFERENCE %u %u\n", process_number,virtual_page_number);
}
