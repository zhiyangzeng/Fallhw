public class AreaCalculator {
	public static double calculate (Shape[] shapes) {
		double result=0;
		for (int i=0; i<shapes.length; i++){
			result+=shapes[i].area();
		}
		return result;
	}

}