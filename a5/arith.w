


var x=23;
var y=35;
var z=5;
var bo=1>0;  //truth variable


//testing: / + - * and () precedence

var result = y/z+x-2*(y-x)+z;   // 35/5+23-2*(35-23)+5 is 11

//testing: == != || && and if else loop

if ( (result/2==0) || (!(result/3==3)) && result+2!=x){
//empty statement works
} else {
	z=y/z;
}

//testing empty ; statements and left association

if ((1>0) || (2>1) && (1<0)) {
	;;;;    ;;;;;    ;;;;;   ;;;  ;;  
	;;      ;;       ;; ;;   ;; ; ;;
	;;;;    ;;;;;    ;;;;    ;; ; ;;
	;;         ;;    ;;      ;;  ;;;
	;;;;    ;;;;;    ;;      ;;   ;;
 
} else {
	print "True Or True And False is False";
	print "\n";

}

if ( (1>0) || ((2>1) && (1<0))) {
	print "True Or (True And False) is True";
	print "\n";
}
print "W language is left-associative";
print "\n";

print result;
print "\n";
print z;
print "\n";
print bo;print "\n";
print !bo;
print "\n";
