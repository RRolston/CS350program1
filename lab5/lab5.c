//Raymond Rolston, Joe Kim, Cameron Parlman
//CS350
//due 3/21/16
//Programming Assignment 1
//lab5
/*SUMMARY:
-does not implement page replacement
-ignores page faults (just counts them)
-worst case order(frames-of-memory) for each command
*/

#include<stddef.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include <assert.h>
#include<time.h>

#define MAX_PID 32768//max process id name on my personal system

int main(int argc, char *argv[]) {

  if(argc!=3){
    fprintf(stderr,"Unacceptable number of arguments %d encountered.", argc);
    fprintf(stderr," ./lab5 <frames-of-memory> <input-file>");
    exit(1);
  }



//Variables------------------------------------------------
FILE * inputFile;
inputFile = fopen(argv[2],"r");
char *ptr;//used for strtol
const unsigned int frames_of_memory = strtol(argv[1], &ptr, 10);
unsigned long int page_faults=0;//no page replacement
int process_number;
unsigned int address_space_size;
int * RAM = ( int*) malloc(sizeof(unsigned int)*frames_of_memory);//simulated memory not actually RAM
assert(RAM);
unsigned int * BASE = (unsigned int*) malloc(sizeof(unsigned int)*MAX_PID);//stores first location of process in memory used to make references
assert(BASE);
unsigned int j;//iterators
unsigned int i;
for (j = 0; j < frames_of_memory; j++){
  RAM[j] = -1;//-1 means empty
}

long int space_left=frames_of_memory-1;
unsigned int virtual_page_number;
int z;//checks result of fscanf
int first=1;//used to identify first allocation of a process within our table
int overflow =0;//used to identify overflow in a loop using unsigned int as we cannot use negative numbers
char command[10];//stores first string of line
while(1){
  z= fscanf(inputFile, "%s ",command);
  if( z == EOF ) break;

//START-----------------------------------------------------

  if(strcmp(command,"START")==0){
     fscanf(inputFile, "%d %u\n", &process_number, &address_space_size);
     for (j = 0; j < address_space_size; j++){
       if(overflow){
         address_space_size--;
         j=0;
         overflow=0;
       }
       if(space_left==-1){
         page_faults++;
         //printf("%s : %d : %ld\n",command, process_number, page_faults );

       }else if(RAM[j]==-1){
         if(first){
           BASE[process_number]=j;
           first=0;
         }
         RAM[j] = process_number;
         space_left--;
       }else{
         address_space_size++;
       }
       if((j+1)==frames_of_memory){
         address_space_size=address_space_size-j;
         j=0;
         overflow=1;
       }
     }
     first=1;//reset
     overflow=0;//reset
  }

//TERMINATE-------------------------------------------------

  if(strcmp(command,"TERMINATE")==0){
    fscanf(inputFile, "%d\n", &process_number);
    for(i=0; i<frames_of_memory;i++){
      if(RAM[i]==process_number){
        RAM[i]=-1;
        space_left++;
      }
    }
  }

//REFERENCE-------------------------------------------------

  if(strcmp(command,"REFERENCE")==0){
     fscanf(inputFile, "%d %u\n", &process_number,&virtual_page_number);
     int k=BASE[process_number];
     int f=BASE[process_number];
     if(f==0){
        f=frames_of_memory;
     }else{
       f=f-1;
     }

     i=0;
     while(i<virtual_page_number){
       //printf("%d : %d: %d\n",i ,k, f);
       if(RAM[k]==process_number) i++;
       if(i<virtual_page_number){
          k++;
       }else{
         break;
       }
       if(k==f) break;
       if(k==frames_of_memory) k=0;
       if(k==f) break;
     }
     if(k==frames_of_memory){
       if(RAM[0]!=process_number){
         page_faults++;
         //printf("%s : %d : %ld\n",command, process_number, page_faults );
       }
     }else{
        if(RAM[k]!=process_number){
          page_faults++;
          //printf("%s : %d : %ld\n",command, process_number, page_faults );
        }
     }
  }

}

printf("PAGE FAULTS: %ld\n", page_faults );
free(BASE);
free(RAM);
fclose(inputFile);

//-----------------------------------------------------------


exit(0);
}
