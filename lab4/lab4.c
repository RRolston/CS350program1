//Raymond Rolston
//CS375
//due 3/18/16
//Programming Assignment 1

#include<stddef.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<time.h>

#define PID_MAX 32768;//max on my personal system

char* stringGen(const int len);
void Start(int,int, FILE*);
void Terminate(int, FILE*);
void Reference(int, int, FILE*);

int main(int argc, char *argv[]) {
//quick argument check-----------------------------------------
  if(argc!=2){
    fprintf(stderr,"Unacceptable number of arguments %d encountered.", argc);
    fprintf(stderr," ./lab4  <input-file>");
    exit(1);
  }
//-----------------------------------------------------------

time_t t;
/* Intializes random number generator */
   srand((unsigned) time(&t));
char* stringA;

//Print format-----------------------------------------------
FILE * oFile;
oFile = fopen(argv[1],"w");
int Pid[PID_MAX];//process IDs 1 or 0 for running or not running
unsigned int address[PID_MAX];//address size of each process ID


fclose(oFile);
//-----------------------------------------------------------

  free(stringA);

return 0;
}
void Start(int process_number, int address_space_size, FILE* outputFile){
  fprintf(outputFile, "START %d %d\n", process_number, address_space_size);
}
void Terminate(int process_number, FILE* outputFile){
  fprintf(outputFile, "TERMINATE %d\n", process_number);
}
void Reference(int process_number, int virtual_page_number, FILE* outputFile){
  fprintf(outputFile, "REFERENCE %d %d\n", process_number,virtual_page_number);
}
char* stringGen( const int len) {

    char* s = (char*)malloc(sizeof(int)*len);
    static const char alphanum[] =     "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    int i;
    for (i = 0; i < len; ++i) {
        s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    s[len] = 0;
    return s;
}
