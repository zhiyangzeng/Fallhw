import java.awt.*;
import java.awt.geom.*;


public class Circle extends Shape implements Comparable<Shape>{
	private final Point point1;
	private final double radius;

	public Circle (Point p1, double r) {
		this.point1=p1;
		this.radius=r;

	}
	
	@Override
	public Point position() {
		return point1;
	}

	@Override
	public double area() {
		return 3.14159*radius*radius;
	}

	@Override
	public boolean equals(Shape obj) {
		return (this.position().eq(obj.position()) && this.getClass()==obj.getClass() && this.area()==obj.area());
	} 

	@Override
	public int compareTo(Shape s) {
	double sArea= s.area();
	double thisArea=this.area();
	if (thisArea > sArea) return 1;
	else if (thisArea == sArea) return 0;
	else return -1;

	}

	@Override
	public String toString(){
		//Circle<(x, y), r> | Area
		StringBuilder result=new StringBuilder();
		result.append("Circle<("+point1.x+","+point1.y+"), "+radius+"> | Area: "+ area());
		return result.toString();
	}
	
	@Override
	public void draw(Graphics g){
		Graphics2D g2d=(Graphics2D) g;
		g2d.draw(new Ellipse2D.Double(point1.x, point1.y, radius, radius));
	}

	@Override
    public int hashCode() {
        int hash = 1+ (int)point1.x * 7 + (int)point1.y * 11;
        return hash;
    }

}

/*
extends Shape implements Comparable<Shape>
public int compareTo(Shape s) {
	double sArea= s.area();
	double thisArea=this.area();
	if (thisArea > sArea) return 1;
	else if (thisArea == sArea) return 0;
	else return -1;

}

*/