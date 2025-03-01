#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int sum = 0;
int threads;

int main(int argc, char *argv[]) {
   if (argc != 3) {
      fprintf(stderr,"usage: %s <num-threads> <sum-value>\n", argv[0]);
      return 1;
   }

   int threads = atoi(argv[1]);
   int val = atoi(argv[2]);

   if (threads < 1 || val < threads) {
      fprintf(stderr,"num-threads (%d) must be > 0 and the sum-value (%d) must be > num-threads\n", 
         threads, val);
      return -1;
   }

   #pragma omp parallel for num_threads(threads)
   for(int i = 1; i <= val; i++)
      sum = sum + i;

   printf("sum = %d\n", sum);
}
