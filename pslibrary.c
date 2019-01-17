#include <string.h>
#include <stdio.h>
#include "pslibrary.h"

#define E_TASK_READY 0
#define E_TASK_RUNNING 1
#define E_TASK_WAITING 2
#define E_TASK_DONE 3

void part0(char *s1, char *s2){
   strcpy(s1,"RRwwwwwRRRRRRRRR");
   strcpy(s2,"rrRRRRwwwwwwwwrrRRRRRRR");
}

void display(char *heading, char *s1, char *s2){
   fprintf(stdout, "\n");
   fprintf(stdout, "%s" , heading);
   fprintf(stdout, "%s\n", s1);
   fprintf(stdout, "%s\n", s2);
   int i;
   int r1=0;
   int r2=0;
   int R1=0;
   int R2=0;
   int str1 = strlen(s1);
   int str2 = strlen(s2);
   float size = 0;
   for(i=0; i < str1; i++){
      if(s1[i] == 'r')
         r1++;
      else if(s1[i] == 'R')
         R1++;
   }
   for(i=0; i < str2; i++){
      if(s2[i] == 'r')
         r2++;
      else if(s2[i] == 'R')
         R2++;
   }
   size = (str1>str2) ? (float)(R1+R2)/str1 : (float)(R1+R2)/str2;
   fprintf(stdout, "%d %d %.1f %.5f\n", r1, r2, (float)(r1+r2)/2, size);
}

/*typedef struct TaskState{
    E_TASK_READY = 0,
    E_TASK_RUNNING,
    E_TASK_WAITING,
    E_TASK_DONE
}eTaskState;
*/
static char stateChars[] = {'r','R','w',0};

void fcfs(char *s1, char *s2, int x1, int y1, int z1, int  x2, int y2, int z2){
    int i;
    int state1 = E_TASK_READY;
    int state2 = E_TASK_READY;
    int cpuLeft1 = x1;
    int cpuLeft2 = x2;
    int ioLeft1 = y1;
    int ioLeft2 = y2;
    
    for(i=0 ; (state1 != E_TASK_DONE) || (state2 != E_TASK_DONE); i++){
        if((state1 == E_TASK_RUNNING) && (cpuLeft1 == 0)){
            if(ioLeft1 == 0){
                state1 = E_TASK_DONE;
                s1[i] = stateChars[state1];
            }
            else
                state1 = E_TASK_WAITING;
        }
        else if((state2 == E_TASK_RUNNING) && (cpuLeft2 == 0)){
            if(ioLeft2 == 0){
                state2 = E_TASK_DONE;
                s2[i] = stateChars[state2];
            }
            else
                state2 = E_TASK_WAITING;
        }
        if((state1 == E_TASK_WAITING) && (ioLeft1 == 0)){
            state1 = E_TASK_READY;
            cpuLeft1 = z1;
        }
        if((state2 == E_TASK_WAITING) && (ioLeft2 == 0)){
            state2 = E_TASK_READY;
            cpuLeft2 = z2;
        }
        if((state1 == E_TASK_READY) && (state2 == E_TASK_READY)){
            //... BOTH ARE READY
            state1 = E_TASK_RUNNING;
        }
        else if ((state1 == E_TASK_READY) && (state2 != E_TASK_RUNNING)){
            state1 = E_TASK_RUNNING;
        }
        else if ((state2 == E_TASK_READY) && (state1 != E_TASK_RUNNING)){
            state2 = E_TASK_RUNNING;
        }
        if(state1 != E_TASK_DONE)
            s1[i] = stateChars[state1];
        if(state2 != E_TASK_DONE)
            s2[i] = stateChars[state2];

        if(state1 == E_TASK_RUNNING)
            cpuLeft1--;
        if(state1 == E_TASK_WAITING)
            ioLeft1--;
        if(state2 == E_TASK_RUNNING)
            cpuLeft2--;
        if(state2 == E_TASK_WAITING)
            ioLeft2--;
    }
}

void sjf(char *s1, char *s2, int x1, int y1, int z1, int  x2, int y2, int z2){ 
    int i;
    int state1 = E_TASK_READY;
    int state2 = E_TASK_READY;
    int cpuLeft1 = x1;
    int cpuLeft2 = x2;
    int ioLeft1 = y1;
    int ioLeft2 = y2;
    
    for(i=0 ; (state1 != E_TASK_DONE) || (state2 != E_TASK_DONE); i++){
        if((state1 == E_TASK_RUNNING) && (cpuLeft1 == 0)){
            if(ioLeft1 == 0){
                state1 = E_TASK_DONE;
                s1[i] = stateChars[state1];
            }
            else
                state1 = E_TASK_WAITING;
        }
        else if((state2 == E_TASK_RUNNING) && (cpuLeft2 == 0)){
            if(ioLeft2 == 0){
                state2 = E_TASK_DONE;
                s2[i] = stateChars[state2];
            }
            else
                state2 = E_TASK_WAITING;
        }
        if((state1 == E_TASK_WAITING) && (ioLeft1 == 0)){
            state1 = E_TASK_READY;
            cpuLeft1 = z1;
        }
        if((state2 == E_TASK_WAITING) && (ioLeft2 == 0)){
            state2 = E_TASK_READY;
            cpuLeft2 = z2;
        }
        if((state1 == E_TASK_READY) && (state2 == E_TASK_READY)){
            if(cpuLeft1 <= cpuLeft2)
                state1 = E_TASK_RUNNING;
            else
                state2 = E_TASK_RUNNING;
        }
        else if ((state1 == E_TASK_READY) && (state2 != E_TASK_RUNNING)){
            state1 = E_TASK_RUNNING;
        }
        else if ((state2 == E_TASK_READY) && (state1 != E_TASK_RUNNING)){
            state2 = E_TASK_RUNNING;
        }
        if(state1 != E_TASK_DONE)
            s1[i] = stateChars[state1];
        if(state2 != E_TASK_DONE)
            s2[i] = stateChars[state2];

        if(state1 == E_TASK_RUNNING)
            cpuLeft1--;
        if(state1 == E_TASK_WAITING)
            ioLeft1--;
        if(state2 == E_TASK_RUNNING)
            cpuLeft2--;
        if(state2 == E_TASK_WAITING)
            ioLeft2--;
    }
}

void psjf(char *s1, char *s2, int x1, int y1, int z1, int  x2, int y2, int z2){
    int i;
    int state1 = E_TASK_READY;
    int state2 = E_TASK_READY;
    int cpuLeft1 = x1;
    int cpuLeft2 = x2;
    int ioLeft1 = y1;
    int ioLeft2 = y2;
    
    for(i=0 ; (state1 != E_TASK_DONE) || (state2 != E_TASK_DONE); i++){
        if((state1 == E_TASK_RUNNING) && (cpuLeft1 == 0)){
            if(ioLeft1 == 0){
                state1 = E_TASK_DONE;
                s1[i] = stateChars[state1];
            }
            else
                state1 = E_TASK_WAITING;
        }
        else if((state2 == E_TASK_RUNNING) && (cpuLeft2 == 0)){
            if(ioLeft2 == 0){
                state2 = E_TASK_DONE;
                s2[i] = stateChars[state2];
            }
            else
                state2 = E_TASK_WAITING;
        }
        if((state1 == E_TASK_WAITING) && (ioLeft1 == 0)){
            state1 = E_TASK_READY;
            cpuLeft1 = z1;
        }
        if((state2 == E_TASK_WAITING) && (ioLeft2 == 0)){
            state2 = E_TASK_READY;
            cpuLeft2 = z2;
        }
        if((state1 == E_TASK_READY) && (state2 == E_TASK_READY)){
            if(cpuLeft1 <= cpuLeft2)
                state1 = E_TASK_RUNNING;
            else
                state2 = E_TASK_RUNNING;
        }
        else if ((state1 == E_TASK_READY) && (state2 != E_TASK_RUNNING)){
            state1 = E_TASK_RUNNING;
        }
        else if ((state2 == E_TASK_READY) && (state1 != E_TASK_RUNNING)){
            state2 = E_TASK_RUNNING;
        }
        else if((state1 == E_TASK_READY) && (state2 == E_TASK_RUNNING)){
            if(cpuLeft1 < cpuLeft2){
                state1 = E_TASK_RUNNING;
                state2 = E_TASK_READY;
            }
        }
        else if((state2 == E_TASK_READY) && (state1 == E_TASK_RUNNING)){
            if(cpuLeft2 < cpuLeft1){
                state2 = E_TASK_RUNNING;
                state1 = E_TASK_READY;
            }
        }
        if(state1 != E_TASK_DONE)
            s1[i] = stateChars[state1];
        if(state2 != E_TASK_DONE)
            s2[i] = stateChars[state2];

        if(state1 == E_TASK_RUNNING)
            cpuLeft1--;
        if(state1 == E_TASK_WAITING)
            ioLeft1--;
        if(state2 == E_TASK_RUNNING)
            cpuLeft2--;
        if(state2 == E_TASK_WAITING)
            ioLeft2--;
    }

}

void rr(char *s1, char *s2, int q, int x1, int y1, int z1, int  x2, int y2, int z2){
    int i;
    int state1 = E_TASK_READY;
    int state2 = E_TASK_READY;
    int cpuLeft1 = x1;
    int cpuLeft2 = x2;
    int ioLeft1 = y1;
    int ioLeft2 = y2;
    int qLeft = q;

    for(i=0 ; (state1 != E_TASK_DONE) || (state2 != E_TASK_DONE); i++){
        if((state1 == E_TASK_RUNNING) && (cpuLeft1 == 0)){
            if(ioLeft1 == 0){
                state1 = E_TASK_DONE;
                s1[i] = stateChars[state1];
            }
            else
                state1 = E_TASK_WAITING;
        }
        else if((state2 == E_TASK_RUNNING) && (cpuLeft2 == 0)){
            if(ioLeft2 == 0){
                state2 = E_TASK_DONE;
                s2[i] = stateChars[state2];
            }
            else
                state2 = E_TASK_WAITING;
        }
/*        if((state1 == E_TASK_RUNNING) && (qLeft == 0)){
            state1 = E_TASK_READY;
            if(state2 == E_TASK_READY){
                state2 = E_TASK_RUNNING;
                qLeft = q;
            }
        }
        if((state2 == E_TASK_RUNNING) && (qLeft == 0)){
            state2 = E_TASK_READY;
            if(state1 == E_TASK_READY){
                state1 = E_TASK_RUNNING;
                qLeft = q;
            }
        }*/
        if((state1 == E_TASK_WAITING) && (ioLeft1 == 0)){
            state1 = E_TASK_READY;
            cpuLeft1 = z1;
        }
        if((state2 == E_TASK_WAITING) && (ioLeft2 == 0)){
            state2 = E_TASK_READY;
            cpuLeft2 = z2;
        }

        if((state1 == E_TASK_RUNNING) && (qLeft == 0)){
            state1 = E_TASK_READY;
            if(state2 == E_TASK_READY){
                state2 = E_TASK_RUNNING;
                qLeft = q;
            }
        }
        if((state2 == E_TASK_RUNNING) && (qLeft == 0)){
            state2 = E_TASK_READY;
            if(state1 == E_TASK_READY){
                state1 = E_TASK_RUNNING;
                qLeft = q;
            }
        }
        if((state1 == E_TASK_READY) && (state2 == E_TASK_READY)){
            //... BOTH ARE READY
            state1 = E_TASK_RUNNING;
            qLeft = q;
        }
        else if ((state1 == E_TASK_READY) && (state2 != E_TASK_RUNNING)){
            state1 = E_TASK_RUNNING;
            qLeft = q;
        }
        else if ((state2 == E_TASK_READY) && (state1 != E_TASK_RUNNING)){
            state2 = E_TASK_RUNNING;
            qLeft = q;
        }
        qLeft--;
        if(state1 != E_TASK_DONE)
            s1[i] = stateChars[state1];
        if(state2 != E_TASK_DONE)
            s2[i] = stateChars[state2];

        if(state1 == E_TASK_RUNNING)
            cpuLeft1--;
        if(state1 == E_TASK_WAITING)
            ioLeft1--;
        if(state2 == E_TASK_RUNNING)
            cpuLeft2--;
        if(state2 == E_TASK_WAITING)
            ioLeft2--;
    }

}
