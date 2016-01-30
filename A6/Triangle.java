import java.awt.*;
import java.awt.geom.*;
import java.lang.Exception.*;



public class Triangle extends Shape implements Comparable<Shape>{
	private final Point point1;
	private final Point point2;
	private final Point point3;
	public final double side1;
	public final double side2;
	public final double side3;
	
	public Triangle (Point p1, Point p2, Point p3){
		this.point1=p1;
		this.point2=p2;
		this.point3=p3;
		side1=p1.distance(p2);
		side2=p2.distance(p3);
		side3=p3.distance(p1);

	}
	
	@Override
	public Point position() {
		return point1;
	}
	

	@Override
	public double area() {
		
		double s=(side1+side2+side3)/2.0;
		double a=java.lang.Math.sqrt((s*(s-side1)*(s-side2)*(s-side3)));
		if (a==0.0) throw new IllegalArgumentException("Error: Illegal triangle formed");
 		return a;
	}
/*
	public boolean sameSides(Triangle obj){
		return (this.side1==obj.side1 && this.side2==obj.side2 && this.side3==obj.side3)

	} */

	@Override
	public String toString(){
		//Rectangle<(x, y), (x,y)> | Area
		StringBuilder result=new StringBuilder();
		result.append("Triangle<("+point1.x+","+point1.y+"), ("+ point2.x+","+point2.y+ "), ("+point3.x+","+point3.y+")> | Area: "+ area());
		return result.toString();
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
	public void draw(Graphics g){
		double x[]= {point1.x,point2.x,point3.x};
		double y[]= {point1.y,point2.y,point3.y};
		Graphics2D g2d = (Graphics2D) g;
		Path2D path= new Path2D.Double();
		path.moveTo(x[0], y[0]);
		path.lineTo(x[1], y[1]);
		path.lineTo(x[2], y[2]);
		path.closePath();
		g2d.draw(path);

		//g2d.draw(new Polygon2D.Double([point1.x,point2.x,point3.x], [point1.y,point2.y,point3.y], 3));
	}


	@Override
	public boolean equals(Shape obj) {
		if (obj instanceof Triangle){
			Triangle tobj=(Triangle) obj; 
			return (this.position().eq(obj.position()) && this.side1==tobj.side1 && this.side2==tobj.side2 && this.side3==tobj.side3);

		} else {
			return false;
		}

	} 

	@Override
    public int hashCode() {
        int hash = 1+ (int)point1.x * 7 + (int)point1.y * 11;
        return hash;
    }
}
