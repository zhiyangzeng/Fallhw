import java.util.Iterator;

public class NodeIterator<T> implements Iterator<T>{

 	private Node<T> node;  //for keeping track of node pointer

    public NodeIterator(Node<T> n) {
 	
        Node<T> head = new Node<T>();
        head.next = n;
        this.node = head;
    }

	public boolean hasNext(){
		return this.node.next!=null;
	}

	public T next() {
		if (!hasNext()) throw new IllegalArgumentException("empty list");
		return (this.node = this.node.next).v;
	}

	public void remove() {
        throw new UnsupportedOperationException("no changes allowed");
    }

}