all : item-consumer item-producer newproc-posix newproc-return omp-1 omp-2 omp-3 thrd-multisum thrd-sum two-way-pipes unix-pipe many-procs

clean :
	-rm item-consumer item-producer newproc-posix newproc-return omp-1 omp-2 omp-3 thrd-multisum thrd-sum two-way-pipes unix-pipe many-procs 2> /dev/null

item-consumer : item-consumer.c
	gcc item-consumer.c -lrt -o item-consumer

item-producer : item-producer.c
	gcc item-producer.c -lrt -o item-producer

newproc-posix : newproc-posix.c
	gcc newproc-posix.c -o newproc-posix

newproc-return : newproc-return.c
	gcc newproc-return.c -o newproc-return

omp-1 : omp-1.c
	gcc -fopenmp omp-1.c -l gomp -o omp-1

omp-2 : omp-2.c
	gcc -fopenmp omp-2.c -l gomp -o omp-2

omp-3 : omp-3.c
	gcc -fopenmp omp-3.c -l gomp -o omp-3

thrd-multisum : thrd-multisum.c
	gcc thrd-multisum.c -pthread -o thrd-multisum

thrd-sum : thrd-sum.c
	gcc thrd-sum.c -pthread -o thrd-sum

two-way-pipes : two-way-pipes.c
	gcc two-way-pipes.c -o two-way-pipes

unix-pipe : unix-pipe.c
	gcc unix-pipe.c -o unix-pipe

many-procs : many-procs.c
	gcc many-procs.c -o many-procs

