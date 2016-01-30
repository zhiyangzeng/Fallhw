import java.util.concurrent.atomic.AtomicInteger;
import java.util.concurrent.*;
import java.util.*;

public class Main2{

private static AtomicInteger counter=new AtomicInteger(0);



public static void main (String[] args) {
	//printTime
	try {
	//printTime pt = new printTime(counter);
	//timeMessage tm1=new timeMessage();
	Thread t1=new Thread(new printTime(counter));
	//Thread m1=new Thread(tm1);
	t1.start();
	
}
	catch (Exception e) {}

}

}