//
//  main2.cpp
//  HWs
//
//  Created by Zhiyang Zeng on 9/16/15.
//  Copyright (c) 2015 Zhiyang. All rights reserved.
//
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
bool palindrome (string);

int main () {
    //0 = false; 1 = true
    cout<<palindrome("")<<endl;
    cout<<palindrome("gohangasalamiimalasagnahog")<<endl;
    cout<<palindrome("racecar")<<endl;
    cout<<palindrome("amanaplanacanalpanama")<<endl;
    cout<<palindrome("tattarrattat")<<endl;
    cout<<palindrome("notpalin")<<endl;
    cout<<palindrome("sarahpalindrome")<<endl;
 

    
}

bool palindrome (string str){
    bool palin=true;
    int size=str.size();
    if (size==0) return palin;
    for (int i=0; i<(size/2); i++){
        if (tolower(str.at(i))!=tolower(str.at(size-i-1))){
            palin=false;
            break;
        }
    }
    
    return palin;
}