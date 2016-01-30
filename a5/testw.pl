#!/usr/bin/perl
# a sample testw script
# written by Hyunyoung Lee for CSCE 314 Students
 
$tested = 0; $succeeded = 0; $failed = 0; $intentional_error = 0;
 
# test case 1 should succeed
$tested += 1;
$output = `./w factorial.w`;
if( $output eq "result is 120\n" ) {
   $succeeded += 1;
}else{
   $failed += 1;
}
# test case 2 should succeed
$tested += 1;
$output = `./w empty-example.w`;
if( $output eq "Testing...\n" ) {
   $succeeded += 1;
}else{
   $failed += 1;
}
# test case 3 is for intentional error
$tested += 1;
$output = `./w factorial-wrong.w 2>&1 1>/dev/null`;
@words = split " ", $output;
if( $words[1] eq "Unused" && $words[4] eq "while") {
   $intentional_error += 1;
}else{
   $failed += 1;
}
#test case 4 is 7th fib number, should succeed
$tested += 1;
$output = `./w fibonacci.w`;
if( $output eq "The 7th number in fibinacci sequence is 13\n" ) {
   $succeeded += 1;
}else{
   $failed += 1;
}

#test case 5 should succeed
$tested += 1;
$output = `./w arith.w`;
if( $output eq "True Or True And False is False
True Or (True And False) is True
W language is left-associative
11
7
True
False
" ) {
   $succeeded += 1;
}else{
   $failed += 1;
}
 

#test case 6 should succeed
$tested += 1;
$output = `./w comp.w`;
if( $output eq "var scope outside of a loop is: 99
var scope inside of a loop is: 2
var scope outside of a loop is: 99
x is 57
y is 80
z is 35
" ) {
   $succeeded += 1;
}else{
   $failed += 1;
}


 
print "$tested tested\n";
print "$succeeded + $intentional_error passed and $failed failed\n";
 
# to run this script, type the following at the terminal command line prompt
# > perl testw.pl
# then the result should be the following two lines
# 6 tested
# 5 + 1 passed and 0 failed
 