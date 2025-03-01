#include <stdio.h>
#include <pthread.h>
int fact = 1;
void *mul(void *param);

int main()
{
    pthread_t tid;
    pthread_attr_t attr;
    int n = 10;

    pthread_attr_init(&attr);
    pthread_create(&tid, &attr, mul, &n);
    pthread_join(tid, NULL);
    printf("%d factorial = %d\n", n, fact);
}
void *mul(void *param)
{
    // creates a thread to compute 10 factorial (10 x 9 x 8 … x 1):
    // n! = n x(n-1)x(n-2)x….x1
    int n = *(int *)param; // gets the interger value from the pointer param.
    fact = 1               // initize fact ==1
        // forloop :from 1 x to n
        for (int i = 1; i <= n; i++)
    {
        fact = fact * i;
    }
    pthread_exit(0);
}