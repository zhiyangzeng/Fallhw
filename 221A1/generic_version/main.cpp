
// main.cpp
//Tests all functionality of the My_vec class.

#include <iostream>
#include <stdexcept>
#include "My_vec.h"

//works only when implementation and declaration of template in header

using namespace std;
int main(){
    try{
        //---------------------------------------------------------------------------------------------
        // testing for type char with My_vec object v, v1, v2
        //---------------------------------------------------------------------------------------------
        

        My_vec<int> v;
        v.insert_at_rank(0, 1);
        cout<<v<<endl; //1
        cout<<v.get_size()<<endl; //1
   
       
        v.insert_at_rank(0, 2);
        cout<<v[0]<<endl;  //2
        cout<<v[1]<<endl;  //1
        cout<<v[2]<<endl;  //0
        cout<<v[3]<<endl; //0
        cout<<v<<endl;  //2 1
        cout<<v.get_size()<<endl; //2
        
        
       
        v.insert_at_rank(2,3);
        cout<<v[0]<<endl; //2
        cout<<v[1]<<endl;  //1
        cout<<v[2]<<endl;  //3
        cout<<v[3]<<endl; //0
        cout<<v<<endl;
        cout<<v.get_size()<<endl; //3
        
        v.insert_at_rank(0, 90);
        cout<<v[0]<<endl; //90
        cout<<v[1]<<endl;  //2
        cout<<v[2]<<endl;  //1
        cout<<v[3]<<endl;  //3   
        cout<<v<<endl;//90 2 1 3
        // remove a character at the rank 2 from the vector v
        v.remove_at_rank(2);  //90 2 3
        cout<<v<<endl;
        
        
        v.replace_at_rank(2, 5);
        cout<<v[0]<<endl;
        cout<<v[1]<<endl;
        cout<<v[2]<<endl;
        cout<<v[3]<<endl;
        cout<<v<<endl;
        cout<<v.get_size()<<endl;
       
        
        My_vec<int> v1=My_vec<int>(v);
        cout<<v1<<endl;
        v1.replace_at_rank(2, 23);
        cout<<v1<<endl;
        
     
        My_vec<int> v2;
        v2.insert_at_rank(0, 14);
        cout<<v2<<endl;
        cout<<v2.get_size()<<endl;
        
     
        v2=v1;
        cout<<v2<<endl;
        
        cout<<find_max_index(v2, v2.get_size())<<endl;  //0
        
        sort_max(v2);
        cout<<v2<<endl;  //90 23 2
        
        
        v2.replace_at_rank(14, 20);
        cout<<v2<<endl;
        
        //---------------------------------------------------------------------------------------------
        // testing for type char with My_vec object v3, v4, v5
        //---------------------------------------------------------------------------------------------

        
        
        My_vec<char> v3;
        v3.insert_at_rank(0, 'A');
        cout<<v3<<endl;
        cout<<v3.get_size()<<endl;
        
        
        v3.insert_at_rank(0, 'B');
        cout<<v3[0]<<endl;
        cout<<v3[1]<<endl;
        cout<<v3[2]<<endl;
        cout<<v3[3]<<endl;
        cout<<v3<<endl;
        cout<<v3.get_size()<<endl;
        
        
        
        v3.insert_at_rank(2,'D');
        cout<<v3[0]<<endl;
        cout<<v3[1]<<endl;
        cout<<v3[2]<<endl;
        cout<<v3[3]<<endl;
        cout<<v3<<endl;
        cout<<v3.get_size()<<endl;
        
        v3.insert_at_rank(0, 'Y');
        cout<<v3[0]<<endl;
        cout<<v3[1]<<endl;
        cout<<v3[2]<<endl;
        cout<<v3[3]<<endl;
        cout<<v3<<endl;
        
        v3.remove_at_rank(2);
        cout<<v3<<endl;
        
        
        v3.replace_at_rank(2, 'F');
        cout<<v3[0]<<endl;
        cout<<v3[1]<<endl;
        cout<<v3[2]<<endl;
        cout<<v3[3]<<endl;
        cout<<v3<<endl;
        cout<<v3.get_size()<<endl;
        
        
        My_vec<char> v4=My_vec<char>(v3);
        cout<<v4<<endl;
        v4.replace_at_rank(2, 'Q');
        cout<<v4<<endl;
        
        
        My_vec<char> v5;
        v5.insert_at_rank(0, 'K');
        cout<<v5<<endl;
        cout<<v5.get_size()<<endl;
        
        
        v5=v4;
        cout<<v5<<endl;
        
        cout<<find_max_index(v5, v5.get_size())<<endl;
        
        sort_max(v5);
        cout<<v5<<endl;
        
        
        v5.replace_at_rank(14, 'X');
        cout<<v5<<endl;
        
        
        
        //---------------------------------------------------------------------------------------------
        // testing for type double with My_vec object v6, v7, v8
        //---------------------------------------------------------------------------------------------

        
        
        
        My_vec<double> v6;
        v6.insert_at_rank(0, 0.7);
        cout<<v6<<endl; //1
        cout<<v6.get_size()<<endl; //1
        
        
        v6.insert_at_rank(0, 1.3);
        cout<<v6[0]<<endl;  //2
        cout<<v6[1]<<endl;  //1
        cout<<v6[2]<<endl;  //0
        cout<<v6[3]<<endl; //0
        cout<<v6<<endl;  //2 1
        cout<<v6.get_size()<<endl; //2
        
        
        
        v6.insert_at_rank(2,2.3);
        cout<<v6[0]<<endl; //2
        cout<<v6[1]<<endl;  //1
        cout<<v6[2]<<endl;  //3
        cout<<v6[3]<<endl; //0
        cout<<v6<<endl;
        cout<<v6.get_size()<<endl; //3
        
        v6.insert_at_rank(0, 66.666);
        cout<<v6[0]<<endl; //90
        cout<<v6[1]<<endl;  //2
        cout<<v6[2]<<endl;  //1
        cout<<v6[3]<<endl;  //3
        cout<<v6<<endl;//90 2 1 3
        // remove a character at the rank 2 from the vector v
        v6.remove_at_rank(2);  //90 2 3
        cout<<v6<<endl;
        
        
        v6.replace_at_rank(2, 5.0);
        cout<<v6[0]<<endl;
        cout<<v6[1]<<endl;
        cout<<v6[2]<<endl;
        cout<<v6[3]<<endl;
        cout<<v6<<endl;
        cout<<v6.get_size()<<endl;
        
        
        My_vec<double> v7=My_vec<double>(v6);
        cout<<v7<<endl;
        v7.replace_at_rank(2, 23);
        cout<<v7<<endl;
        
        
        My_vec<double> v8;
        v8.insert_at_rank(0, 14.9);
        cout<<v8<<endl;
        cout<<v8.get_size()<<endl;
        
        
        v8=v7;
        cout<<v8<<endl;
        
        cout<<find_max_index(v8, v8.get_size())<<endl;  //0
        
        sort_max(v8);
        cout<<v8<<endl;  //90 23 2
        
        
        v8.replace_at_rank(14, 20);
        cout<<v8<<endl;


        
    }
    
    catch(exception &error){
        cerr << "Error: " << error.what() << endl;
    }
}
