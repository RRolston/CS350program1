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
int process_number;
int address_space_size;
int virtual_page_number;
  fscanf(outputFile, "START %d %d\n", process_number, address_space_size);
  fscanf(outputFile, " %d\n", process_number, address_space_size);
  fscanf(outputFile, "START %d %d\n", process_number,virtual_page_number);

fclose(outputFile);
//-----------------------------------------------------------

  free(stringA);

return 0;
}
