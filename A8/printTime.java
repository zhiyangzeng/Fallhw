import java.util.concurrent.atomic.AtomicInteger;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.*;
import java.util.*;

public class printTime extends Thread{
private int delay=1000;
private static AtomicInteger counter;
public static int temp;
public printTime(AtomicInteger c){
	counter=c;
	//temp=0;
}
private Lock lock = new ReentrantLock();
private Condition doneEdit = lock.newCondition(); 

public void timeMessage() {
	lock.lock();
	try{
		System.out.println("");
		System.out.println("7 second message");
	} 

	finally {
		lock.unlock();
	}

}

public void timeMessage2() {
	lock.lock();
	try{
		System.out.println("");
		System.out.println("15 second message");
	} 

	finally {
		lock.unlock();
	}

}
public void increment(){
	lock.lock();
	try{
		temp=this.counter.incrementAndGet();
		System.out.print(temp+" ");
		if (temp>0&&(temp%7==0)){
			doneEdit.signalAll();
		}
		if (temp>0&&(temp%15==0)){
			doneEdit.signalAll();
		}
	} 
	finally {
		lock.unlock();
	}
}

public void run() {
	
	synchronized(counter){
	try {
		while (true){
			if (temp>0&&(temp%7==0)){
				timeMessage();
			}
			if (temp>0&&(temp%15==0)){
				timeMessage2();
			}
			increment();
			Thread.sleep(1000);
		}
		} catch (InterruptedException e) {
	             // A sleeping thread may be interrupted to be terminated, 
	             // which raises an exception		
	             return; // end this thread
		}
	}
	}
}



