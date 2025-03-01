#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

#define BUFFER_SIZE 10

typedef struct {
   float f;
} item;

struct shm_buffer {
   int in;
   int out;
   item buffer[BUFFER_SIZE];
};

void consume(struct shm_buffer *b, int max);

int main()
{
   const char *name = "ACO350-shm";
   int shm_fd;
   void *ptr;
   struct shm_buffer *mybuf;
   int size = sizeof(struct shm_buffer);

   /* open the shared memory segment */
   shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
   if (shm_fd == -1) {
      printf("Consumer: shared memory failed\n");
      exit(-1);
   }

   /* map the shared memory segment in the address space of the process */
   ptr = mmap(0, size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
   if (ptr == MAP_FAILED) {
      printf("Consumer: memory map failed\n");
      exit(-1);
   }

   mybuf = (struct shm_buffer *)ptr;
   
   /* consume items from the buffer */
   consume(mybuf, 15);

   /* remove the shared memory segment */
   if (shm_unlink(name) == -1) {
      printf("Consumer: error removing %s\n",name);
      exit(-1);
   }

   return 0;
}

void consume(struct shm_buffer *b, int max) {
   int i = 1;
   item next_consumed;

   while (i <= max) {
      while (b->in == b->out) // Buffer is Empty!
         ; /* do nothing */

      printf("Consumer: found an item in position %d\n", b->out);

      next_consumed = b->buffer[b->out]; 
      b->out = (b->out + 1) % BUFFER_SIZE;

      /* consume the item */
      printf("Consumer: consumed %f\n", next_consumed.f);
      sleep(1);
      i++;
   }
}
