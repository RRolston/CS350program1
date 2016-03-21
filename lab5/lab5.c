//Raymond Rolston
//CS350
//due 3/21/16
//Programming Assignment 1

#include<stddef.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<time.h>

#define MAX_PID 32768//max on my personal system

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
FILE * inputFile;
inputFile = fopen(argv[2],"r");
char *ptr;
const unsigned int frames_of_memory = strtol(argv[1], &ptr, 10);
unsigned long int page_faults=0;//no page replacement
int process_number;
unsigned int address_space_size;
 int * RAM = ( int*) malloc(sizeof(unsigned int)*frames_of_memory);
unsigned int * BASE = (unsigned int*) malloc(sizeof(unsigned int)*MAX_PID);
unsigned int j;
unsigned int i;
for (j = 0; j < frames_of_memory; j++){
  RAM[j] = -1;
}
unsigned int space_left=frames_of_memory;
unsigned int counter=0;
unsigned int virtual_page_number;
int z;//
int bool1true=1;
char command[10];
while(1){
  z= fscanf(inputFile, "%s ",command);
  if( z == EOF ) break;
  if(strcmp(command,"START")==0){
     fscanf(inputFile, "%d %u\n", &process_number, &address_space_size);
     for (j = counter; j < address_space_size; j++){
       if(RAM[j]==-1){
         if(bool1true){
           BASE[process_number]=j;
           bool1true=0;
         }
         RAM[j] = process_number;
         space_left--;
       }else{
         address_space_size++;
       }
       if(space_left==0){
         for(i=0; i<frames_of_memory;i++){
           if(RAM[i]==process_number) RAM[i]=-1;
         }
         page_faults++;
         break;
       }
       if((j+1)==frames_of_memory){
         address_space_size=address_space_size-j;
         j=-1;
       }
     }
  }
  if(strcmp(command,"TERMINATE")==0){
    fscanf(inputFile, "%d\n", &process_number);
    for(i=0; i<frames_of_memory;i++){
      if(RAM[i]==process_number) RAM[i]=-1;
    }
  }
  if(strcmp(command,"REFERENCE")==0){
     fscanf(inputFile, "%d %u\n", &process_number,&virtual_page_number);
     int k=BASE[process_number];
     int f=BASE[process_number];
     if(f==0){
        f=frames_of_memory-1;
     }else{
       f=f-1;
     }
     for(i=0;i<virtual_page_number+1;){
       if(RAM[k]==process_number) i++;
       if(i!=virtual_page_number+1) k++;
       if(k==frames_of_memory) k=0;
       if(k==f) break;
     }
     if(RAM[k]==-1 || i!=virtual_page_number+1) page_faults++;
  }
  counter=j;
  //printf("%s %ld\n", command, process_number );
}

printf("PAGE FAULTS: %ld\n", page_faults );
free(BASE);
free(RAM);
fclose(inputFile);

//-----------------------------------------------------------


exit(0);
}
