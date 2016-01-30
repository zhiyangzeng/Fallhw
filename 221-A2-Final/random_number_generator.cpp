#include <iostream>
#include <fstream>
#include <cmath>
#include <random>

using namespace std;
int main() {
	
	ofstream out;
    srand (time(NULL));
	random_device rd; // random number from hardware
	mt19937 eng(rd()); //seed
    uniform_int_distribution<> distr(-32768, 32767); // define the range
	
	out.open("100_random.txt");
    for(int n=0; n<100; ++n) {
        out << distr(eng) << endl; // generate numbers
	}
	out.close();
	return 0;
}