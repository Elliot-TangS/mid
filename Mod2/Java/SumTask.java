import java.util.concurrent.*;

public class SumTask extends RecursiveTask<Long> {
   static final int SIZE = 1_00_000_000;
   static final int THRESHOLD = 100_000;

   private int begin;
   private int end;
   private int[] array;

   public SumTask(int begin, int end, int[] array) {
      this.begin = begin;
      this.end   = end;
      this.array = array;
   }

   protected Long compute() {
      if (end - begin < THRESHOLD) {
         long sum = 0;
         for (int i = begin; i <= end; i++)
            sum += array[i];

         return sum;
      } else {
         int mid = begin + (end - begin) / 2;

         SumTask leftTask  = new SumTask(begin, mid, array);
         SumTask rightTask = new SumTask(mid + 1, end, array);

         leftTask.fork();
         rightTask.fork();

         return rightTask.join() + leftTask.join();
      }
   }

   public static void main(String[] args) {
      long startTime, endTime;
      float duration1, duration2;

      int[] array = new int[SIZE];
      for (int i = 0; i < SIZE; i++)
         array[i] = (i * 7) % 10000;

      ForkJoinPool pool = ForkJoinPool.commonPool();
      long iterativeSum = 0;
      startTime = System.nanoTime();
      for (int i = 0; i < SIZE; i++)
         iterativeSum += array[i];
      endTime = System.nanoTime();
      duration1 = (float) ((endTime - startTime) / 1000000.0);

      startTime = System.nanoTime();
      SumTask task = new SumTask(0, SIZE - 1, array);
      long parallelSum = pool.invoke(task);
      endTime = System.nanoTime();
      duration2 = (float) ((endTime - startTime) / 1000000.0);

      System.out.printf("The iterative sum is %d and took %.3f milliseconds\n", iterativeSum, duration1);
      System.out.printf("The parallel sum is %d and took %.3f milliseconds\n", parallelSum, duration2);
   }
}
