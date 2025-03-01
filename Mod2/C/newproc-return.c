/*
   The WEXITSTATUS macro used in this code returns the exit status of the child.  
   This consists of the least significant 8 bits of the status argument 
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
pid_t pid;

   /* fork a child process */
   pid = fork();

   if (pid < 0) { /* error occurred */
      fprintf(stderr, "Fork Failed\n");
      return 1;
   }

   if (pid == 0) { /* child process */
      int my_ret_val = 0;
      printf("Child asks: What should my return status be? ");
      scanf("%d", &my_ret_val);
      exit(my_ret_val);
   }

   else { /* parent process */
      int wstatus;
      int child_pid = wait(&wstatus);
      int child_ret_val = WEXITSTATUS(wstatus);
      printf("Parent says: Child %d returned a %d\n", child_pid, child_ret_val);
   }
    
    return 0;
}
