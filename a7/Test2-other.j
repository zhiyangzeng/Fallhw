import java.util.*;
import java.math.*;

public class Test2 {
	public static void main (String[] args){

		LinkedList<Integer> empty=new LinkedList<Integer>();
		LinkedList<Integer> list=new LinkedList<Integer>(Arrays.asList(1,2,3,4,5,6));
		//System.out.println(empty);
		//System.out.println(empty.reverse());
		System.out.println(list);
		System.out.println(list.reverse());
		System.out.println(list.reverse().reverse());
		

		int sum=0;
		for (int e:list) {sum+=e;}
		System.out.println(sum);


	}

	public static Number sum(LinkedList <? extends Number> l) {
		try {
			BigDecimal result;
			for (Number e : l) {result+=e.floatValue();}
			return result.intValue();
		}
		catch (IllegalArgumentException e) {
			System.out.println(e.getMessage());
			System.exit(1);
		}
		catch (UnsupportedOperationException e) {
			System.out.println(e.getMessage());
			System.exit(1);
		}
		return 0;
	}

	public static void print(LinkedList <? extends Number> l){
		try{
			for (Number e : l) {System.out.println(e);}
		}
		catch (IllegalArgumentException e) {
			System.out.println(e.getMessage());
			System.exit(1);
		}
		catch (UnsupportedOperationException e) {
			System.out.println(e.getMessage());
			System.exit(1);
		}
	}
}