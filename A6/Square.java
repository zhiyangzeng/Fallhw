import java.awt.*;
import java.awt.geom.*;



public class Square extends Shape implements Comparable<Shape>{
	private final Point point1;
	private final double side;
	
	public Square(Point p1, double side) {
		this.point1=p1;
		this.side=side;
	}

	@Override
	public Point position() {
		return point1;
	}
	

	@Override
	public double area() {
		return side*side;
	}

	@Override
	public boolean equals(Shape obj) {
		return (this.position().eq(obj.position()) && this.getClass()==obj.getClass() && this.area()==obj.area());
	} 

	@Override
	public void draw(Graphics g){
		Graphics2D g2d = (Graphics2D) g;
		Rectangle2D rect = new Rectangle2D.Double(point1.x, point1.y, point1.x+side, point1.y+side);
		g2d.draw(rect);
		//g.drawRect(point1.x, point1.y, side, side);
	}

	@Override
	public String toString(){
		//Circle<(x, y), r> | Area
		StringBuilder result=new StringBuilder();
		result.append("Square<("+point1.x+","+point1.y+"), "+side+"> | Area: "+ area());
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
    public int hashCode() {
        int hash = 1+ (int)point1.x * 7 + (int)point1.y * 11;
        return hash;
    }
}