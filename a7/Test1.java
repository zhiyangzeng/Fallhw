public class Test1 { 
	public static void main (String[] args){
		Node <Integer> n5 = new Node<Integer> (5, null);
		Node <Integer> n4 = new Node<Integer> (4, n5);
		Node <Integer> n3 = new Node<Integer> (3, n4);
		Node <Integer> n2 = new Node<Integer> (2, n3);
		Node <Integer> n1 = new Node<Integer> (1, n2);

		print(n1);
		System.out.println(sum(n1));

	}

	public static int sum(Node <Integer> n1) { //Node<T>
		int result=0;
		for (Integer e : n1) {result+=e;}
		return result;
	}

	public static void print(Node <Integer> n1){
		for (Integer e : n1) {System.out.println(e);}
	}

}