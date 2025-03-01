public class RangeRunner extends Thread {
   private int min;
   private int max;
   private Sum sum;
   
   public RangeRunner(int min, int max, Sum s) {
      this.min = min;
      this.max = max;
      sum = s;
   }
   
   public void run() {
      System.out.printf("Thread %d->%d Running...\n", min, max);
      
      for (int i = min; i <= max; i++)
         sum.add(i);
   }   
}
