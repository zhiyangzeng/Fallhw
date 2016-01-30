import java.util.*;
import java.math.*;

public class Test2 {
	public static void main (String[] args){

		LinkedList<Integer> empty=new LinkedList<Integer>();
		LinkedList<Integer> list=new LinkedList<Integer>(Arrays.asList(1,2,3,4,5,6,7));
		System.out.println(empty);
		System.out.println(empty.reverse());
		System.out.println(list);
		System.out.println(list.reverse());
		System.out.println(list.reverse().reverse().reverse()); 
		System.out.println(list);


		int sum=0;
		for (int e:list) {sum+=e;}
		System.out.println(sum);


	}

	public static int sum(LinkedList <Integer> n1){ 
		int result=0;
		for (Integer e : n1) {result+=e;}
		return result;

	}

	public static void print(LinkedList <Integer> n1){
		for (Integer e : n1) {System.out.println(e);}
	}
}