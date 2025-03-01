#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int sum;

void *runner(void *param); /* the thread */

int main(int argc, char *argv[]) {
   pthread_t tid; /* the thread identifier */
   pthread_attr_t attr; /* set of attributes for the thread */

   if (argc != 2) {
      fprintf(stderr,"usage: %s <integer value>\n", argv[0]);
      return 1;
   }

   int val = atoi(argv[1]);
   if (val < 0) {
      fprintf(stderr,"Argument %d must be non-negative\n",val);
      return -1;
   }

   /* get the default attributes */
   pthread_attr_init(&attr);

   /* create the thread */
   pthread_create(&tid,&attr,runner,&val);

   /* now wait for the thread to exit */
   pthread_join(tid,NULL);

   printf("sum = %d\n",sum);
}

void *runner(void *param) {
   int upper = *((int *)param);
   sum = 0;

   for (int i = 1; i <= upper; i++)
      sum += i;

   pthread_exit(0);
}
