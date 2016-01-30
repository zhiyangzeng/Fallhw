import java.awt.*;
import java.awt.geom.*;


public class Line extends Shape implements Comparable<Shape>{
	private final Point point1;
	private final Point point2;
	
	public Line(Point p1, Point p2){
		this.point1=p1;
		this.point2=p2;

	}
	
	@Override
	public Point position() {
		return point1;
	}

	public Point point2() {
		return point2;
	}
	@Override
	public double area() {
		return 0.0;
	}

	@Override
	public boolean equals(Shape obj) {
		if (obj instanceof Line){
			Line lobj=(Line) obj; 
			return (this.position().eq(lobj.position()) && this.point2().eq(lobj.point2()));

		} else {
			return false;
		}
	} 

	@Override
	public String toString(){
		//Line<(x, y), (x2,y2)>
		StringBuilder result=new StringBuilder();
		result.append("Line Segment<("+point1.x+","+point1.y+"), "+ "("+ point2.x+","+point2.y+")> | Area: "+ area());
		return result.toString();
	}

	@Override
	public void draw(Graphics g){
		Graphics2D g2d = (Graphics2D) g;
		g2d.draw(new Line2D.Double(point1.x, point1.y, point2.x, point2.y));
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
