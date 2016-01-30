
import java.awt.Color;
import java.awt.Graphics;

public abstract class Shape implements Comparable<Shape>{
	
	public abstract double area();
	public abstract Point position();
	public abstract boolean equals(Shape obj);
	public abstract void draw(Graphics g);

	
}