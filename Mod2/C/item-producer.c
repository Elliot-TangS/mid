#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/types.h>

#define BUFFER_SIZE 10

typedef struct {
   float f;
} item;

struct shm_buffer {
   int in;
   int out;
   item buffer[BUFFER_SIZE];
} ;

void produce(struct shm_buffer *b, int max);

int main() {
   const char *name = "ACO350-shm";
   int shm_fd;
   void *ptr;
   struct shm_buffer *mybuf;
   int size = sizeof(struct shm_buffer);

   /* create the shared memory segment */
   shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);

   /* configure the size of the shared memory segment */
   ftruncate(shm_fd, size);

   /* map the shared memory segment in the address space of the process */
   ptr = mmap(0, size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
   if (ptr == MAP_FAILED) {
      printf("Producer: Map failed\n");
      return -1;
   }

   /* initialize the shared memory contents */
   mybuf = (struct shm_buffer *)ptr;
   mybuf->in = 0;
   mybuf->out = 0;

   /* produce items and place them in the buffer */
   produce(mybuf, 15);

   return 0;
}

void produce(struct shm_buffer *b, int max) {
   int i = 1;
   item next_produced;

   while (i <= max) { 
      /* produce an item */ 
      sleep(2);
      next_produced.f = (float) i * (float) i;
      printf("Producer: created %f\n", next_produced.f);
      i++;

      while (((b->in + 1) % BUFFER_SIZE) == b->out) // Buffer is Full!
         ; /* do nothing */ 

      printf("Producer: placing item in position %d\n", b->in);

      b->buffer[b->in] = next_produced; 
      b->in = (b->in + 1) % BUFFER_SIZE; 
   }
}
