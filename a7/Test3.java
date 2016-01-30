import java.util.LinkedList;
import java.util.Queue;
import java.util.*;

public class Test3 {
	public static void main (String[] args){
		//testing shop and queue 
		Shop<Number> numshop = new Shop<Number>();
		Queue<Integer> queue = new LinkedList<Integer>();
		for (int i = 0; i < 5; i++)
            queue.add(i);
        Queue<Number> qd = new LinkedList<Number>();
        qd.add(0.2); qd.add(1.5);qd.add(2.3);qd.add(3); 
        Stack<Object> cus=new Stack<Object>();
        cus.push("Hello");
        cus.push("It's me");
		numshop.sell(qd);
        numshop.sell(queue);  //subtype bound can sell into shop of higher level
        System.out.println("********NumShop before customer buying******");
        System.out.println(numshop);
        System.out.println("********NumShop after customer buying******");
        numshop.buy();
        numshop.buy(4,cus);
        System.out.println(numshop);
        System.out.println("********Customer with super typing after buying******");
        for (Object e : cus){
        	System.out.print(e+" ");
       	}
       	System.out.println("\n");

        //testing set,deque and special classes
        Shop<Food> heb=new Shop<Food>();
        Set<Fruit> supply=new HashSet<Fruit>();
        Deque<Grocery> customer = new ArrayDeque<Grocery>();
        Fruit farm[]={new Watermelon(), new Fruit(), new Watermelon(), new Mango(),new Watermelon()};
        for (int i=0; i<farm.length; i++){ //add items to Set
        	supply.add(farm[i]);
        }

        heb.sell(supply);  //add Set with upper bound to Shop
        System.out.println("********HEB before customer buying******");
        System.out.println(heb);
        System.out.println("********HEB after customer buying******");
       	//heb.buy(new Watermelon(), watermelon_dude);
       	heb.buy(4, customer);  //move from Shop to Deque of higher hierarchy class
       	System.out.println(heb);
        System.out.println("********Customer after buying******");
       	for (Grocery e : customer) { //
       		System.out.print(e+" ");
       	}
       	System.out.println("\n");

       	//hashmap
       	HashMap<String, Food> hm = new HashMap<String, Food>();
	    hm.put("Food", new Food());
	    hm.put("Mango", new Mango());
	    hm.put("Watermelon", new Watermelon());
	    hm.put("Fruit", new Fruit());
       	heb.sell(hm.values());  //get the mapped value to heb

       	System.out.println("********HEB after resupply ******");
       	System.out.println(heb);
      

	}

	static class Grocery {
	public Grocery() {}

	@Override
	public String toString(){
		StringBuilder result=new StringBuilder();
		result.append("[Grocery item]");
		return result.toString();
	}
	}


	static class Food extends Grocery{
	public Food() {}

	@Override
	public String toString(){
		StringBuilder result=new StringBuilder();
		result.append("[Food item]");
		return result.toString();
	}

	}

	static class Fruit extends Food {
	public Fruit() {}

	@Override
	public String toString(){
		StringBuilder result=new StringBuilder();
		result.append("[Fruit item]");
		return result.toString();
	}
	}

	static class Watermelon extends Fruit {
	public Watermelon() {}

	@Override
	public String toString(){
		StringBuilder result=new StringBuilder();
		result.append("[Watermelon]");
		return result.toString();
	}
	}

	static class Mango extends Fruit {
    public Mango() {}

	@Override
	public String toString(){
		StringBuilder result=new StringBuilder();
		result.append("[Mango]");
		return result.toString();
	}
	}


}