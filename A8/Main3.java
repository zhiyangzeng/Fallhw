import java.lang.reflect.*; // for reflection operations
import java.util.*;
import java.lang.reflect.*;
import static java.lang.System.out;
import static java.lang.System.err;

public class Main3 {

static void displayMethodInfo(Object obj) {
	Class c=obj.getClass();
	Method[] methods = c.getDeclaredMethods();
	String cl=c.getName();
	boolean sta=false;
	String com;  //control comma output for nicety
	for (Method m : methods){
		Type[] param = m.getGenericParameterTypes();
		if (param.length==0){
			com="";
		} else {
			com=", ";
		}
		if (Modifier.isStatic(m.getModifiers())) {
            //System.out.println("Static method!");
            sta=true;
        }
        if (sta){
        	System.out.print(m.getName()+" (");
        } else {
			System.out.print(m.getName()+" ("+cl+com);
		}  //foo(A, |
        
        //out.println(" parameters: ");
        String comma="";
        for (Type t: param){
        	System.out.print(comma+t);//T1, T2
        	comma=", ";
        }
        System.out.println(") -> "+m.getReturnType());
        sta=false;
	}

	System.out.println("*****************finished output***************");
}

static class A{ //inner class with Main3$ sign in front

	A(){}
	void foo(int t1, int t2){
		t1=t1+t2;
	}

	int bar (int t1, double t2, long t3){
		return t1*t1;
	}
	static double doo(){
		return 4.0;
	}
	void fo2() {

	}

}
public static void main (String[] args) {
	A a=new A();
	MyClass m=new MyClass();
	Node <Integer> n5 = new Node<Integer> (5, null);
	NodeIterator n=new NodeIterator(n5);
	LinkedList l=new LinkedList();
	displayMethodInfo(a);
	displayMethodInfo(m);
	displayMethodInfo(n5);
	displayMethodInfo(n);
	displayMethodInfo(l);
}

}