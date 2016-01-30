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
  string filename;

  /* initialize random seed: */
  srand (time(NULL));
  cout<<"How many numbers do you want to have: ";
  cin>>size;

  cout<<"What is the name of the file: ";
  cin>>filename;

  ofstream myfile;
  myfile.open(filename);

  myfile<<size<<endl;

  for(int i = 0; i < size; i++){
  	selector = rand() % 2;
  	if(selector  == 1){
  		number = rand() % 32768;
  		myfile<<number<<endl;
  	}
  	else{
  		number = - (rand() % 32768);
  		myfile<<number<<endl;
  	}
  }
}