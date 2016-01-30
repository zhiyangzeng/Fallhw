// Written by Hyunyoung Lee for CSCE 314 students

import java.util.concurrent.atomic.AtomicInteger;

class IncrementRunnableA implements Runnable
{
  public IncrementRunnableA(NonblockingCounter nc1, int cnt) {
    myNC = nc1; count = cnt;
  }
  public void run() {
   try {
    for (int i = 0; i < count; i++) {
      System.out.println("trialCount for "+i+
                         "th increment = "+myNC.increment());
      Thread.sleep(10); // to cause pronounced interleaving
    }
   } catch (InterruptedException e) {}
  }
  private NonblockingCounter myNC;
  private int count;
}


public class NonblockingCounter {
  private AtomicInteger value = new AtomicInteger();

  public int getValue() { return value.get(); }

  public int increment() {
    int v;
    int cnt = 0;
    do {
      cnt++; // local variables, not shared
      v = value.get();
    } while (!value.compareAndSet(v, v + 1));
    return cnt;
  }

  public static void main(String args[]) {
    NonblockingCounter nc = new NonblockingCounter();
    try {
    int count = Integer.parseInt(args[0]);
    Thread t1 = new Thread( new IncrementRunnableA(nc, count) ); 
    Thread t2 = new Thread( new IncrementRunnableA(nc, count) ); 
    Thread t3 = new Thread( new IncrementRunnableA(nc, count) ); 
    Thread t4 = new Thread( new IncrementRunnableA(nc, count) ); 
    t1.start();
    t2.start();
    t3.start();
    t4.start();
    try { // example of barrier synchronization using join
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    } catch (InterruptedException e) {}
    System.out.println("Final value = "+nc.getValue());
    } catch (Exception e) {
      System.out.println(
       "** Usage: java NonblockingCounter <positive_int>");
    }
  }
}
