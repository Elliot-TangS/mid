#include <stdio.h>
#include <omp.h>

int main(void) {
   // Normal, single threaded print
   printf("OMP-Program 1 - starting\n");

   // Run the following 1 statement on each of the available cores
   #pragma omp parallel
   printf("Print A on each core. Thread-no = %d\n", omp_get_thread_num());

   // Run the following 1 statement (a block statement, in this case) on 
   // each of the available cores
   #pragma omp parallel
   {
      printf("Print B on each core. Thread-no = %d\n", omp_get_thread_num());
      printf("Print C on each core. Thread-no = %d\n", omp_get_thread_num());
   }

   // Normal, single threaded print
   printf("OMP-Program 1 - ending\n");

   return 0;
}
