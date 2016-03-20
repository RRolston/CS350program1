//Raymond Rolston
//CS350
//due 3/21/16
//Programming Assignment 1

#include<stddef.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<time.h>


int main(int argc, char *argv[]) {

  if(argc!=3){
    fprintf(stderr,"Unacceptable number of arguments %d encountered.", argc);
    fprintf(stderr," ./lab5 <frames-of-memory> <input-file>");
    exit(1);
  }

time_t t;
/* Intializes random number generator */
   srand((unsigned) time(&t));

//Print format-----------------------------------------------
FILE * outputFile;
outputFile = fopen(argv[2],"r");
char *ptr;
const unsigned int frames_of_memory = strtol(argv[1], &ptr, 10);
unsigned long int FIFO_page_faults=0;
unsigned int process_number;
unsigned int address_space_size;
unsigned int virtual_page_number;
int z;//
char command[10];
while(1){
  z= fscanf(outputFile, "%s ",command);
  if( z == EOF ) break;
  if(strcmp(command,"START")==0) fscanf(outputFile, "%u %u\n", &process_number, &address_space_size);
  if(strcmp(command,"TERMINATE")==0) fscanf(outputFile, "%u\n", &process_number);
  if(strcmp(command,"REFERENCE")==0) fscanf(outputFile, "%u %u\n", &process_number,&virtual_page_number);
  printf("%s %u\n", command, process_number );
}
fclose(outputFile);
//-----------------------------------------------------------


return 0;
}
