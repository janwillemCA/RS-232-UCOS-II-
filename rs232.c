#include "includes.h"
#include <unistd.h>
#include <fcntl.h>

/* Definition of Task Stacks */
#define TASK_STACKSIZE 2048
OS_STK task1_stk[TASK_STACKSIZE];

/* Definition of Task Priorities */

#define TASK1_PRIORITY 1

void task1(void * pdata) {
  FILE * fp;
  char test[10];
  fp = fopen(SERIAL_PORT_NAME, "r+");
  while (1) {
    if (fp == NULL) {
      printf("\nFile /RS232 not open for writing....");
    } else {
      fprintf(fp, "%s", "Hello World!");
      if (fscanf(fp, "%s", test) == 1) {
        printf("%s\n", test);
      }
    }

    OSTimeDlyHMSM(0, 0, 1, 0);
  }
  fclose(fp);
}

/* The main function creates two task and starts multi-tasking */
int main(void) {
  OSTaskCreateExt(task1,
    NULL,
    (void * ) & task1_stk[TASK_STACKSIZE - 1],
    TASK1_PRIORITY,
    TASK1_PRIORITY,
    task1_stk,
    TASK_STACKSIZE,
    NULL,
    0);
    
  OSStart();

  return 0;
}
