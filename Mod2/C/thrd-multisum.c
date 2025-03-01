#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
   int start_val;
   int end_val;
} instruction_t;

int sum = 0;
int num_threads;

void *runner(void *param); /* the thread */

int main(int argc, char *argv[]) {
   if (argc != 3) {
      fprintf(stderr,"usage: %s <num-threads> <sum-value>\n", argv[0]);
      return 1;
   }

   int num_threads = atoi(argv[1]);
   int val = atoi(argv[2]);

   if (num_threads < 1 || val < num_threads) {
      fprintf(stderr,"num-threads (%d) must be > 0 and the sum-value (%d) must be > num-threads\n", 
         num_threads, val);
      return -1;
   }

   pthread_t tids[num_threads]; /* the thread identifier */
   pthread_attr_t attr; /* set of attributes for the thread */

   /* get the default attributes */
   pthread_attr_init(&attr);

   /* create the threads */
   int num = 1;
   for(int i = 0; i < num_threads; i++) {
      instruction_t *inst = (instruction_t *)(malloc(sizeof(instruction_t)));
      inst->start_val = num;
      inst->end_val =  i < num_threads - 1 ? ((i+1) * val / num_threads) - 1 : val;
      
      num = inst->end_val + 1;
      pthread_create(&tids[i], &attr, runner, inst);
   }

   /* now wait for all of the threads to exit */
   for(int i = 0; i < num_threads; i++) {
      pthread_join(tids[i], NULL);
   }

   printf("sum = %d\n", sum);
}

void *runner(void *param) {
   instruction_t *inst = (instruction_t *)param;

   printf("Thread: %2d -> %2d\n", inst->start_val, inst->end_val);
   for (int i = inst->start_val; i <= inst->end_val; i++)
      sum += i;

   pthread_exit(0);
}
