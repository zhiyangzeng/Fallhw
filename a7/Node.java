
/* Name: Zhiyang Zeng
*  CSCE 314 Section 501
*  UIN: 720005338
*  Help received: stackoverflow.com, oracle,tutorialpoints.com, piazza
*/  

//import java.util.Iterator;

public final class Node<T> implements Iterable<T>{
	public final T v;
	public Node<T> next;
	public Node (T val, Node<T> link) {v=val; next=link;}
	public Node() {v=null; next=null;}
	@Override
	public NodeIterator<T> iterator() {
		return new NodeIterator<T>(this);
	}
}