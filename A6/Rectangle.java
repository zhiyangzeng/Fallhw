import java.awt.*;
import java.awt.geom.*;


public class Rectangle extends Shape implements Comparable<Shape>{
	private final Point point1;
	private final Point point2;

	public Rectangle (Point p1, Point p2){
		this.point1=p1;
		this.point2=p2;

	}

	@Override
	public Point position() {
		return point1;
	}
	
	
	@Override
	public double area() {
		return (point2.x-point1.x)*(point2.y-point1.y);
	}
	
	@Override
	public boolean equals(Shape obj) {
		return (this.position().eq(obj.position()) && this.getClass()==obj.getClass() && this.area()==obj.area());
	} 

	@Override
	public String toString(){
		//Rectangle<(x, y), (x,y)> | Area
		StringBuilder result=new StringBuilder();
		result.append("Rectangle<("+point1.x+","+point1.y+"), "+ "("+ point2.x+","+point2.y+")> | Area: "+ area());
		return result.toString();
	}

	@Override
	public void draw(Graphics g){
		Graphics2D g2d = (Graphics2D) g;
		Rectangle2D rect = new Rectangle2D.Double(point1.x, point1.y, point2.x, point2.y);
		g2d.draw(rect);
		//g.drawRect(point1.x, point1.y, abs(point1.x-point2.x), abs(point1.y-point2.y));
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
    public int hashCode() {
        int hash = 1+ (int)point1.x * 7 + (int)point1.y * 11;
        return hash;
    }
}
