import java.util.Scanner;

public class ThreadSum {
   public static void main(String[] args) {
      Scanner in = new Scanner(System.in);
      System.out.println("Add to what number? ");
      int max = in.nextInt();

      Runner r = new Runner(max);
      r.start();
      try {
         r.join();
      } catch (InterruptedException e) {
         e.printStackTrace();
      }
      System.out.printf("Total of 1 to %d is %d\n", max, r.getSum());

      in.close();
   }
}
