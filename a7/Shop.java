import java.util.LinkedList;
import java.util.List;
import java.util.*;

public class Shop<T> {
	List<T> stock;  
	public Shop() {stock=new java.util.LinkedList<T>();}

	void sell(T item) {
		stock.add(item);
	}

	T buy() {
		return stock.remove(0); 
	}

	void sell(Collection<? extends T> items) {
		for (T e : items){
			stock.add(e);
		}
	}

	void buy(int n, Collection<? super T> items) {
		for (T e : stock.subList(0,n)){  
			items.add(e);
		} 
		for (int i=0; i<n; ++i) stock.remove(0);  
	}

	@Override
	public String toString(){
		StringBuilder result=new StringBuilder();
		result.append("Items in Shop: ");
		String prefix="";
		for (T e : stock){
			result.append(prefix);
			prefix=",";
			result.append(e);
		}
		result.append("\n");
		return result.toString();
	}
	/*
	void buy(T item, Collection<? super T> items) {
		
		for (T e : stock){
			if (e.getClass()==item.getClass()) {
				items.add(e);
				stock.remove(e);
			}
			
		}
	}*/
}