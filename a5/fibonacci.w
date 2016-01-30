var fibnum = 7;
var result=0;

if (fibnum==0) {
	result = 0;
} 
if (fibnum==1) {
	result=1;
} else {
	var n1=0;
	var n2=1;
	var i =1;
	while (i<fibnum) {
	result=n1+n2;
	n1=n2;
	n2=result;
	i=i+1;
	}
}

print "The ";
print fibnum;
print "th number in fibinacci sequence is ";
print result;
print "\n";
