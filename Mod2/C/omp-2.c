#include <omp.h>
#include <stdio.h>

#define NT 7

int main() {
   // Normal, single threaded print
   printf("OMP-Program 2 - starting\n");

   // Run the following for statement on the specified # of threads
   #pragma omp parallel for num_threads(NT)
   for(int i=0; i<NT; i++)  
      printf("Running Thead-no = %d\n",omp_get_thread_num());

   int a[] = {1, 5, 7, 2, 6, 9, 3, 6, 4, 8};
   int b[] = {3, 4, 8, 9, 5, 1, 0, 2, 6, 7};
   int size = sizeof(a)/sizeof(a[0]);
   int c[size];

   printf("\n");

   #pragma omp parallel for num_threads(NT)
   for(int i=0; i<size; i++) {
      c[i] = a[i] + b[i];
      printf("c[%d] = a[%d] + b[%d], Thead-no = %d\n", i, i, i, omp_get_thread_num());
   }

   printf("\n");

   // Normal, single threaded print
   printf("OMP-Program 2 - ending\n");
}
