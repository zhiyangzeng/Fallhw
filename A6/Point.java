import java.lang.Math;

public class Point {
	public double x;
	public double y;
	public Point (double xcoor, double ycoor) {
		this.x=xcoor; 
		this.y=ycoor;
	}

	public double distance (Point p2) {
		return Math.sqrt(Math.pow((this.x-p2.x),2)+Math.pow((this.y-p2.y),2));

	}

	public boolean eq (Point p2) {
		return (this.x==p2.x) && (this.y==p2.y);
	}
	
}