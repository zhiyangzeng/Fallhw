import java.lang.reflect.*; // for reflection operations
import java.util.*;
import java.lang.reflect.*;


public class Main4 {

static void displayMethodInfo(Class cl) {
	Method[] methods = cl.getMethods(); //get public method
	for (Method m : methods){
		if (Modifier.isStatic(m.getModifiers())) { //static method
			//System.out.println("static method found");
            Type[] param = m.getGenericParameterTypes();
            //String firstfour=m.getName().substring(0,4);
			if (param.length==0 && m.getReturnType().equals(boolean.class)&& m.getName().substring(0,4).equals("test")){  //no param, returns bool, first4 "test"
			//if (m.getReturnType().equals(Boolean.TYPE))	{
				//System.out.println("boolean no param test found");
				try{
					boolean re=(Boolean)m.invoke(null);
					if (re==true) {
						System.out.println("OK: "+m.getName()+" succeeded");
					} else {
						System.out.println("FAILED: "+m.getName()+" failed");
					}
				} catch (Exception e){

				}
			}
        }    
	}

	System.out.println("*****************finished output***************");
}

public static void main (String[] args) {

Class type = null;
    try {
      type = Class.forName(args[0]);//get the class
      displayMethodInfo(type);
    } catch (ClassNotFoundException e) {
      System.err.println(e);
      return;
    }
}

}