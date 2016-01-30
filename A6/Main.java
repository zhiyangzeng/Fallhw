/*  Name: Zhiyang Zeng
*   Section: 501
*   Help received: stackoverflow.com, oracle documentation, wikipedia,tutorialpoints,http://www.javapractices.com/, ntu.edu
*/

import java.util.Random;
import java.util.Arrays;
import java.awt.*;
import javax.swing.*;
import java.util.List;
import java.util.*;
import java.awt.Graphics;
import java.lang.Exception.*;
import static java.lang.Math.*;


public class Main extends JFrame{

   public static final int CANVAS_WIDTH  = 800;
   public static final int CANVAS_HEIGHT = 600;
   // Declare an instance the drawing canvas (extends JPanel)
   private static Shape[] shapeArr;
   private static double[] coor;

   private DrawCanvas canvas;
 
   /* Constructor to set up the GUI components */
   public Main() {
      canvas = new DrawCanvas();    // Construct the drawing canvas
      canvas.setPreferredSize(new Dimension(CANVAS_WIDTH, CANVAS_HEIGHT));
 
      Container cp = getContentPane();
      cp.add(canvas);
      this.setDefaultCloseOperation(EXIT_ON_CLOSE);   // CLOSE button
      this.pack();              // pack() the components; 
      //this.setSize(200,200);
      this.setTitle("Draw Output");  
      this.setVisible(true);    
   }
   	
	public static void main (String[] args){
		try {
		if (args [0].charAt(0)=='R') {

			Random rand=new Random();
			int size = Integer.parseInt(args[1]);
			shapeArr = new Shape[size];
			List<Character> type=Arrays.asList('t','r','s','c','l');
			for (int i=0; i<size; i++){
				char c=type.get(rand.nextInt(type.size()));
				switch (c){
					//rangeMin + (rangeMax - rangeMin) * r.nextDouble();
					case 't':
					shapeArr[i]=new Triangle (new Point((0+100*rand.nextDouble()), (0+100*rand.nextDouble())),
											  new Point((0+100*rand.nextDouble()), (0+100*rand.nextDouble())),
											  new Point((0+100*rand.nextDouble()), (0+100*rand.nextDouble())));
					break;

					case 'r':
					shapeArr[i]=new Rectangle (new Point((0+100*rand.nextDouble()), (0+100*rand.nextDouble())),
											   new Point((0+100*rand.nextDouble()), (0+100*rand.nextDouble())));
					break;

					case 's':
					shapeArr[i]=new Square (new Point((0+100*rand.nextDouble()), (0+100*rand.nextDouble())),
											   (0+100*rand.nextDouble()));
					break;

					case 'c':
					shapeArr[i]=new Circle (new Point((0+100*rand.nextDouble()), (0+100*rand.nextDouble())),
											   (0+100*rand.nextDouble()));
					break;

					case 'l':
					shapeArr[i]=new Line (new Point((0+100*rand.nextDouble()), (0+100*rand.nextDouble())),
										  new Point((0+100*rand.nextDouble()), (0+100*rand.nextDouble())));
					break;

					default:
					throw new IllegalArgumentException("Error: Illegal format in second argument");
				}//end switch
			}//end for
			print(shapeArr);
			AreaCalculator a=new AreaCalculator();
			System.out.println("Total area is: "+ a.calculate(shapeArr));
		} //end R 

		else if (args [0].charAt(0)=='S'){
			//loop first to get size of array
			int sizecount=0;
			for (int i=0; i<args[1].length(); i++){ //detect - num
				if (args[1].charAt(i)=='-') throw new IllegalArgumentException("Error: Negative number is not allowed");
				if (args[1].charAt(i)=='t' || args[1].charAt(i)=='r' ||args [1].charAt(i)=='l' ||args[1].charAt(i)=='c' ||args[1].charAt(i)=='s'){
					sizecount++;
				}
			}
			System.out.println("Number of Shapes: "+ sizecount);

			//"c 1.0 2.0 3.0;r 1.0 2.0 5.0 4.0; t 1.0 2.0 3.0 4.0 0.0 6.0; l 4.0 4.0 0.0 0.0; s 0.0 5.0 7.8;"
			shapeArr = new Shape[sizecount];
			final int arrsize=sizecount;
		    int position=0;   //position for jumping beteen parameters and capturing input
			while (position<args[1].length()){ 
				switch (args[1].charAt(position)){  //create new shape object and push into array
					case ' ':
					position+=1;
					break;

					case 't':
					coor= new double[6];
					for (int i=0; i<5;i++){
						position= 1+args[1].indexOf(' ',position);
						if (position>=(args[1].indexOf(';',position)-1)) throw new IllegalArgumentException("Error: Illegal number of inputs in second argument given to constructor");
						coor[i]= Double.parseDouble(args[1].substring(position, args[1].indexOf(' ',position))); 

					}
					position= 1+args[1].indexOf(' ',position);
					if (args[1].substring(position, args[1].indexOf(';',position)).contains(" ")) throw new IllegalArgumentException("Error: Too many data input");
					coor[5]=Double.parseDouble(args[1].substring(position, args[1].indexOf(';',position)));
					/*
					position= 1+args[1].indexOf(' ',position); //position is after space, at 1.0
					double tp1x= Double.parseDouble(args[1].substring(position, args[1].indexOf(' ',position))); //capture p1x
					position= 1+args[1].indexOf(' ',position); //jump to 2.0
					double tp1y= Double.parseDouble(args[1].substring(position, args[1].indexOf(' ',position))); //capture p1y
					position= 1+args[1].indexOf(' ',position); //position is after space, at 1.0
					double tp2x= Double.parseDouble(args[1].substring(position, args[1].indexOf(' ',position))); //capture p2x
					position= 1+args[1].indexOf(' ',position); //jump to 2.0
					double tp2y= Double.parseDouble(args[1].substring(position, args[1].indexOf(' ',position))); //capture p2y
					position= 1+args[1].indexOf(' ',position); //position is after space, at 1.0
					double tp3x= Double.parseDouble(args[1].substring(position, args[1].indexOf(' ',position))); //capture p2x
					position= 1+args[1].indexOf(' ',position); //jump to 2.0
					double tp3y= Double.parseDouble(args[1].substring(position, args[1].indexOf(';',position))); //capture p2y
					*/

					//size-sizecount
					shapeArr[arrsize-sizecount] = new Triangle (new Point (coor[0], coor[1]), new Point (coor[2], coor[3]), new Point (coor[4], coor[5])); 
					position = 1+args[1].indexOf(";",position); //jump to ;
					sizecount--;
					break;
				
					case 'r':
					coor= new double[4];
					for (int i=0; i<3;i++){
						position= 1+args[1].indexOf(' ',position);
						if (position>=(args[1].indexOf(';',position)-1)) throw new IllegalArgumentException("Error: Illegal number of inputs in second argument given to constructor");
						coor[i]= Double.parseDouble(args[1].substring(position, args[1].indexOf(' ',position))); 

					}
					position= 1+args[1].indexOf(' ',position);
					if (args[1].substring(position, args[1].indexOf(';',position)).contains(" ")) throw new IllegalArgumentException("Error: Too many data input");
					coor[3]=Double.parseDouble(args[1].substring(position, args[1].indexOf(';',position)));
					/*
					position= 1+args[1].indexOf(' ',position); //position is after space, at 1.0
					double rp1x= Double.parseDouble(args[1].substring(position, args[1].indexOf(' ',position))); //capture p1x
					position= 1+args[1].indexOf(' ',position); //jump to 2.0
					double rp1y= Double.parseDouble(args[1].substring(position, args[1].indexOf(' ',position))); //capture p1y
					position= 1+args[1].indexOf(' ',position); //position is after space, at 1.0
					double rp2x= Double.parseDouble(args[1].substring(position, args[1].indexOf(' ',position))); //capture p2x
					position= 1+args[1].indexOf(' ',position); //jump to 2.0
					double rp2y= Double.parseDouble(args[1].substring(position, args[1].indexOf(';',position))); //capture p2y
					*/

					if (coor[0]>=coor[2] || coor[1]>=coor[3]) throw new IllegalArgumentException("Error: Illegal rectangle formed");
					shapeArr[arrsize-sizecount] = new Rectangle (new Point (coor[0], coor[1]), new Point (coor[2], coor[3])); 
					position = 1+args[1].indexOf(";",position); //jump to ;
					sizecount--;
					break;
				
					case 's':
					coor= new double[3];
					for (int i=0; i<2;i++){
						position= 1+args[1].indexOf(' ',position);
						if (position>=(args[1].indexOf(';',position)-1)) throw new IllegalArgumentException("Error: Illegal number of inputs in second argument given to constructor");
						coor[i]= Double.parseDouble(args[1].substring(position, args[1].indexOf(' ',position))); 

					}
					position= 1+args[1].indexOf(' ',position);
					if (args[1].substring(position, args[1].indexOf(';',position)).contains(" ")) throw new IllegalArgumentException("Error: Too many data input");
					coor[2]=Double.parseDouble(args[1].substring(position, args[1].indexOf(';',position)));
					/*
					position= 1+args[1].indexOf(' ',position); //position is after space, at 1.0
					double sp1x= Double.parseDouble(args[1].substring(position, args[1].indexOf(' ',position))); //capture p1x
					position= 1+args[1].indexOf(' ',position); //jump to 2.0
					double sp1y= Double.parseDouble(args[1].substring(position, args[1].indexOf(' ',position))); //capture p1y
					position= 1+args[1].indexOf(' ',position); //jump to 3.0
					double side= Double.parseDouble(args[1].substring(position, args[1].indexOf(';',position))); //capture s
					*/
					if (coor[2]<=0) throw new IllegalArgumentException("Error: Cannot have side <=0");
					shapeArr[arrsize-sizecount] = new Square (new Point (coor[0], coor[1]), coor[2]); 
					position = 1+args[1].indexOf(";",position);
					sizecount--;
					break;
				
					case 'c':
					coor= new double[3];
					for (int i=0; i<2;i++){
						position= 1+args[1].indexOf(' ',position);
						if (position>=(args[1].indexOf(';',position)-1)) throw new IllegalArgumentException("Error: Illegal number of inputs in second argument given to constructor");
						coor[i]= Double.parseDouble(args[1].substring(position, args[1].indexOf(' ',position))); 

					}
					position= 1+args[1].indexOf(' ',position);
					if (args[1].substring(position, args[1].indexOf(';',position)).contains(" ")) throw new IllegalArgumentException("Error: Too many data input");
					coor[2]=Double.parseDouble(args[1].substring(position, args[1].indexOf(';',position)));
					/*
					position= 1+args[1].indexOf(' ',position); //position is after space, at 1.0
					double cp1x= Double.parseDouble(args[1].substring(position, args[1].indexOf(' ',position))); //capture p1x
					position= 1+args[1].indexOf(' ',position); //jump to 2.0
					double cp1y= Double.parseDouble(args[1].substring(position, args[1].indexOf(' ',position))); //capture p1y
					position= 1+args[1].indexOf(' ',position); //jump to 3.0
					double radius= Double.parseDouble(args[1].substring(position, args[1].indexOf(';',position))); //capture r
					*/
					if (coor[2]<=0) throw new IllegalArgumentException("Error: Cannot have side <=0");
					shapeArr[arrsize-sizecount] = new Circle (new Point (coor[0], coor[1]), coor[2]); 					
					position = 1+args[1].indexOf(";",position);
					sizecount--;
					break;
				
					case 'l':
					coor= new double[4];
					for (int i=0; i<3;i++){
						position= 1+args[1].indexOf(' ',position);
						if (position>=(args[1].indexOf(';',position)-1)) throw new IllegalArgumentException("Error: Illegal number of inputs in second argument given to constructor");
						coor[i]= Double.parseDouble(args[1].substring(position, args[1].indexOf(' ',position))); 

					}
					position= 1+args[1].indexOf(' ',position);
					if (args[1].substring(position, args[1].indexOf(';',position)).contains(" ")) throw new IllegalArgumentException("Error: Too many data input");
					coor[3]=Double.parseDouble(args[1].substring(position, args[1].indexOf(';',position)));
					
					if (coor[0]==coor[2]&&coor[1]==coor[3]) throw new IllegalArgumentException("Error: Line is expected, but a Point is received");
					shapeArr[arrsize-sizecount] = new Line (new Point (coor[0], coor[1]), new Point (coor[2], coor[3])); //no need for object					
					position = 1+args[1].indexOf(";",position); //jump to ;
					sizecount--;
					break;

					default:
					throw new IllegalArgumentException("Error: Illegal format in second argument");
				} //endswitch
			}//endwhile

			System.out.println("-----------------------------------");
			System.out.println("Array before sorting:");
			System.out.println("-----------------------------------");
			print(shapeArr);   //print array
			shapeArr=sortShape(shapeArr);  
			System.out.println("-----------------------------------");
			System.out.println("Array after sorting:");
			System.out.println("-----------------------------------");
			print(shapeArr);
			AreaCalculator a=new AreaCalculator();
			System.out.println("Total area is: "+ a.calculate(shapeArr));

		} //end S
		else {
			throw new IllegalArgumentException("Error: The first argument is invalid. Use R for random object or S to specify");
		}
		SwingUtilities.invokeLater(new Runnable() {//method from ntu.edu
         @Override
         public void run() {
            new Main(); 
         }
      });
   
	}//end try
	catch(IllegalArgumentException e){
		System.out.println(e.getMessage());
		System.exit(1);
	}
	System.out.println("*** To test equals()");
    for ( int i = 0; i < shapeArr.length-1; i++ )
        for ( int j = i+1; j <= shapeArr.length-1; j++ ) {
            if (shapeArr[i].equals(shapeArr[j]))
               System.out.println(shapeArr[i] + " equals to " + shapeArr[j]);
        }
    //end testing
	}//end main
	
	private class DrawCanvas extends JPanel {
      // Override paintComponent to perform your own painting
      @Override
      public void paintComponent(Graphics g) {
         super.paintComponent(g);     // paint parent's background
         setBackground(Color.BLACK);  // set background color 
         g.setColor(Color.YELLOW);    // set the drawing color

         Graphics2D g2d=(Graphics2D) g;
         g2d.scale(3,3);

         for (int i=0; i<shapeArr.length; i++){
         	shapeArr[i].draw(g);  //this shows the overridden draw metod works!
         }

      }
   }

	public static Shape[] sortShape (Shape[] arr){
		for (int i=0; i<arr.length; i++) {
			int j=i;
			while (j>0 && arr[j].compareTo(arr[j-1])<0){
				Shape temp=arr[j];
				arr[j]=arr[j-1];
				arr[j-1]=temp;
				j--;
			}
		}
		return arr;
	}

	public static void print (Shape[] arr){
		for (int i=0; i<arr.length; i++){
			System.out.println(arr[i]);  //overridden toString
		}

	}
}//end main class




