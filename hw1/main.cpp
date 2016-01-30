#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <time.h>
#include <cmath>

/*todo:
*invalid input in guessing
*/
using namespace std;
int interpret (int, int);
int array_size(int []);
int main (){
    vector<int> range={1,2,4,8,16,32,64,128,256,512,1024,2048};
    vector<int> range2={1,3,7,15,31,63,127,255,511,1023,2047};
    vector<vector<int>> results(3, vector<int>(range.size()));
    results[0]=range;
    int target;
    int low,high,num_guess,guess,result;
    char testing;
    ofstream out;
    srand (time(NULL));
    cout<<"Testing Y/N ?    ";
    cin>>testing;
    try{
        for (int i=0; i<range.size(); i++) {
            if (i>11){
                throw "Index out of bound.";
            }
            if (tolower(testing)=='y'){
                /* for arbitrary number
                cout<<endl;
                cout<<"Please set the target number:   ";
                cin>>target; 
                if (target<1 || target>range[i]{
                    throw "Invalid target entry!";
                 }
                 */
                
                target= range[i];
                results[1][i]=target;
                
            } else {
                target=rand() % range[i]+1;
            }
            low=1;
            high=range[i];
            num_guess=1;
            guess = (low+high)/2;
            result=interpret(guess, target);
            while (result!=0){
                if (result==1){
                    low=guess+1;
                }
                else if (result==-1) {
                    high=guess-1;
                }
                else {
                    throw "Unknown error occured.";
                }
                guess=(low+high)/2;
                result=interpret(guess, target);
                num_guess+=1;
            }
            results[2][i]=num_guess;
            cout<<"For range of "<<range[i]<<" the number of guesses took is "<<num_guess<<endl;
            result=-2;
            
            
        }
        //prints the results vector to file
        out.open("output.txt");
        for (int j=0; j<3;j++){
            for (int i=0;i<results[0].size();i++){
                out<<results[j][i]<<"   ";
            }
            out<<endl;
        }
        out.close();
    }
    catch (string msg){
        cout<<"Exception: "<<msg<<endl;
    }
    
    return 0;
}

int interpret (int guess, int target){
    if (target>guess) {
        cout<<"higher\n";
        return 1;}
    else if (target<guess) {
        cout<<"lower\n";
        return -1;}
    else if (target==guess){
        cout<<"yes\n";
        return 0;
    }
    else{
        cout<<"Exception: Comparison error\n";
        return -6;
    }
}
