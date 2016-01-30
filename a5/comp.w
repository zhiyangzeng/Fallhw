



//testing scoping and if loop without else

var scope = 99;
print "var scope outside of a loop is: ";
print scope;
print "\n";
if (scope > 1) {
  var scope=2;
  print "var scope inside of a loop is: ";
  print scope;
  print "\n";
}
print "var scope outside of a loop is: ";
print scope;
print "\n";

//testing comparison < > <= >= and nested loop
var x=50;
var y=5;
var z=0;


while (y<x) {

	if ( (z <= x/2) && (z >= 0) || !(z+y!=23)){
	 	z=z+(x-y*3);
	 	while (z>1000){
	 		z=z/100;
	 	}
	 	if (z>0){
	 		x=x+1;
	 	}
	} else {
	 	x=x+2;
	}
	y=y*2;
}

print "x is ";
print x;
print "\n";
print "y is ";
print y;
print "\n";
print "z is ";
print z;
print "\n";