/**
 * Example program demonstrating UNIX pipes.
 *
 * Figures 3.21 & 3.22
 *
 * @author Silberschatz, Galvin, and Gagne
 * Operating System Concepts  - Tenth Edition
 * Copyright John Wiley & Sons - 2018
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

#define BUFFER_SIZE 25
#define READ_END   0
#define WRITE_END   1

int main(void) {
   char parent_write_msg[BUFFER_SIZE] = "Parent text";
   char parent_read_msg[BUFFER_SIZE];
   char child_write_msg[BUFFER_SIZE] = "Child text";
   char child_read_msg[BUFFER_SIZE];
   pid_t pid;
   int fd_p2c[2];
   int fd_c2p[2];

   /* create the pipes */
   if (pipe(fd_p2c) == -1) {
      fprintf(stderr,"First Pipe failed");
      return 1;
   }
   if (pipe(fd_c2p) == -1) {
      fprintf(stderr,"Second Pipe failed");
      return 1;
   }

   /* now fork a child process */
   pid = fork();

   if (pid < 0) {
      fprintf(stderr, "Fork failed");
      return 1;
   }

   if (pid > 0) {  /* parent process */
      /* close the unused ends of the pipes */
      close(fd_p2c[READ_END]);
      close(fd_c2p[WRITE_END]);

      /* write to the p2c pipe */
      write(fd_p2c[WRITE_END], parent_write_msg, strlen(parent_write_msg)+1); 

      /* read from the c2p pipe */
      read(fd_c2p[READ_END], parent_read_msg, BUFFER_SIZE);
      printf("Parent read: %s\n", parent_read_msg);

      /* close the used ends of the pipes */
      close(fd_p2c[WRITE_END]);
      close(fd_c2p[READ_END]);
   }
   else { /* child process */
      /* close the unused ends of the pipes */
      close(fd_c2p[READ_END]);
      close(fd_p2c[WRITE_END]);

      /* write to the c2p pipe */
      write(fd_c2p[WRITE_END], child_write_msg, strlen(child_write_msg)+1); 

      /* read from the p2c pipe */
      read(fd_p2c[READ_END], child_read_msg, BUFFER_SIZE);
      printf("Child read: %s\n", child_read_msg);

      /* close the used ends of the pipes */
      close(fd_c2p[WRITE_END]);
      close(fd_p2c[READ_END]);
   }

   return 0;
}
