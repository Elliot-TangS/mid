import java.util.Scanner;

public class ThreadMultiSum {
   public static void main(String[] args) {
      Scanner in = new Scanner(System.in);
      System.out.print("Add to what number? ");
      int max = in.nextInt();
      System.out.print("How many threads? ");
      int num_threads = in.nextInt();

      if (num_threads < 1 || max < num_threads) {
         System.out.printf("num-threads (%d) must be > 0 and the sum-value (%d) must be > num-threads\n", num_threads, max);
         System.exit(1);
      }

      Sum s = new Sum();
      RangeRunner[] threads = new RangeRunner[num_threads];
      
      int start_val = 1; 
      for(int i = 0; i < num_threads; i++) {
         int end_val = i < num_threads - 1 ? ((i+1) * max / num_threads) - 1 : max;
         threads[i] = new RangeRunner(start_val, end_val, s);
         start_val = end_val + 1; 
          threads[i].start();
      }      

      for(int i = 0; i < num_threads; i++) {
         try {
            threads[i].join();
         } catch (InterruptedException e) {
            e.printStackTrace();
         }
      }      

      System.out.printf("Total of 1 to %d is %d\n", max, s.getValue());

      in.close();
   }
}
