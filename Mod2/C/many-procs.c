#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_PROCS 100
#define DELAY 2

int main() {
   pid_t pid[MAX_PROCS];
   srand(time(NULL));

   for (int i = 0; i < MAX_PROCS; i++) {
      pid[i] = fork();   
   
      if (pid[i] < 0) {   
         fprintf(stderr, "Fork Failed\n");   
         return 1;   
      } else if (pid[i] == 0) {
         printf("Child: #%d started. Sleeping for %d seconds.\n", i, DELAY);   
         sleep(DELAY);
         printf("Child: #%d done.\n", i);   
	 exit(i);
      } else {
         printf("Parent: Created child %d\n", pid[i]);   
      }   
   }
   
   for (int i = 0; i < MAX_PROCS; i++) {
      int wstatus;
      waitpid(pid[i], &wstatus, 0);
      int child_ret_val = WEXITSTATUS(wstatus);
      printf("Parent: Child %d Complete and returned a %d\n", pid[i], child_ret_val);   
   }
    
    return 0;
}
