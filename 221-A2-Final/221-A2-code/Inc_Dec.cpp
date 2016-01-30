#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iostream>
#include <fstream>
#include <math.h>
#include <string>

using namespace std;

int main ()
{
  int number, selector, size;
  string filename, direction;

  /* initialize random seed: */
  srand (time(NULL));
  cout<<"Increasing (i) or Decreasing (d): ";
  cin>>direction;

  cout<<"How many numbers do you want to have: ";
  cin>>size;

  cout<<"What is the name of the file: ";
  cin>>filename;

  ofstream myfile;
  myfile.open(filename);

  myfile<<size<<endl;
  if(direction == "i")
    for(int i = 0; i < size; i++){
    		myfile<<i<<endl;
    	}
  else 
    for(int i = size; i > 0; i--){
        myfile<<i<<endl;
      }
}