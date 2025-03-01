public class Runner extends Thread {
   private int max;
   private int sum;
   
   public Runner(int m) {
      max = m;
      sum = 0;
   }
   
   public void run() {
      System.out.println("Thread Running...");
      
      for (int i = 1; i <= max; i++)
         sum += i;
   }
   
   public int getSum() {
      return sum;
   }
}
