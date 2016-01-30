import java.util.Iterator;

public final class LinkedList<T> implements Iterable<T>{
	public Node<T> head;
	public Node<T> tail;
	public Node<T> current;

	public LinkedList(){
		head=null;
		tail=null;
		current=null;
	}

	public LinkedList(Iterable<T> it){
		for (T e : it){
			if (this.head==null) { //initialize head if not already done
				Node<T> h = new Node<T>(e, null);   //header is first node here, can be an empty pointer?
				this.head=h;  //head and tail as first node if head is empty
				this.tail=h;
				this.current=this.head;  //set current to be head so they can be linked
			} else {
				Node<T> h = new Node<T>(e, null);
				current.next=h;   //last node's next is connected
				current=h;
				this.tail=h;
			}			
		}
		
	}

	@Override
    public Iterator<T> iterator() {
        Iterator<T> it = new Iterator<T>() {

        Node<T> node = new Node<T>(null, head);
        //node.next = head; why won't this work?
        
        @Override
	 	public boolean hasNext(){
			return node.next!=null;
		}

		@Override
		public T next() {
			if (!hasNext()) throw new IllegalArgumentException("empty list");
			return (node = node.next).v;
		}

		@Override
		public void remove() {
	        throw new UnsupportedOperationException("no changes allowed");
	    }
        };
        return it;
    }


	public LinkedList<T> reverse(){  //reverse a singly linked list
		LinkedList<T> rev= new LinkedList<T>();
		rev.head=this.tail;
		rev.current=rev.head;

		for (T e : this){
			Node<T> n = new Node<T>(e, null); 
			if (rev.current!=rev.head) {			
				n.next=rev.current;//if this is not the new tail, set next
			} else {
				//this is the tail, set it
				rev.tail=n;
			}
			rev.current=n;  
		}
		rev.head=rev.current; //connect to head
		
		/* testing
		System.out.println("rev head is: "+rev.head.v);
		System.out.println("rev head is connected to "+rev.head.next.v); 
		System.out.println("rev tail is: "+rev.tail.v); */

		//clone reversed to this
		this.head=rev.head;
		this.tail=rev.tail;
		this.current=rev.current;
		return this;
	}
	@Override
	public String toString(){
		StringBuilder result=new StringBuilder();
		result.append("[");
		String prefix="";
		for (T e : this){
			result.append(prefix);
			prefix=",";
			result.append(e);
		}
		result.append("]");
		return result.toString();
	}

}