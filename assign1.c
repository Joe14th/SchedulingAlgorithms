#include <stdio.h>
#include <stdlib.h>
#include "pslibrary.h"

int main( int argc, char *argv[]){
   if(argc != 8){
      printf("Program takes exactly 7 integer command line parameters\n");
      exit(-1);
   }

   int i;
   int sum = 0;
   char *header;
   char *s1;
   char *s2;

   printf("Assignment 1 program was written by Jasmine Ramirez\n");
   printf("inputs:");
   for(i = 1; i < argc; i++){
      printf(" %s", argv[i]);
   }
   printf("\n");


   for(i = 2; i < argc; i++){
      sum += atoi(argv[i]);
   }
   s1 = malloc(sizeof(char)*(sum));
   s2 = malloc(sizeof(char)*(sum));
   if(s1 == NULL || s1 == NULL){
      printf("Allocation of character array failed\n");
      exit(-1);
   }


   fcfsa(s1, s2,atoi(argv[2]), atoi(argv[3]), atoi(argv[4]), atoi(argv[5]), atoi(argv[6]), atoi(argv[7]));
   header = "Part 1\n";
   display( header, s1, s2);


   free(s1);
   free(s2);

   return(0);
}
