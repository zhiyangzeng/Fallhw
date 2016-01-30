/**
Name: main.cpp
Function: Tests all functionality of the My_vec class.
Author: Benke Qu
Created on: 9/11/15-9/12/15
**/
#include <iostream>
#include <stdexcept>
#include <string>
#include "My_vec.h"

#define print_info(expr) cout << #expr << " --> " << expr << endl;

#define print_exception(expr) cout << "Exception: " << expr << endl;



using namespace std;

int main() {
	
		cout << endl << endl;
		cout << "*****************************" << endl;
		cout << "1. CONSTRUCTOR and DESTRUCTOR" << endl;
		cout << "*****************************" << endl;
		
		
		cout << "--------------------- 1.1 Test default constructor and copy constructor -------------------" << endl;
		cout << "//default constructor: check if he initialized the three member variables." << endl;
        cout << "//copy constructor: use case v1(A, B, C). My_vec v2(v1). v2 should be (A, B, C)" << endl;
		try{
			cout << "//His or Her result: " << endl;
			My_vec v1;
			v1.insert_at_rank(0, 'C');
			v1.insert_at_rank(0, 'B');
			v1.insert_at_rank(0, 'A');
			
			My_vec v2(v1);
			print_info(v2);
		}catch(exception &error){
			print_exception(error.what());
		}
		cout << endl;
		
		
		cout << "--------------------- 1.2 Destructor and overloading operator= -------------------" << endl;
		cout << "//destructor: the body should be \"delete [] ptr;\" instead of \"delete ptr;\"" << endl;
		cout << "//overloading operator= : use case v1(A, B, C). My_vec v2 = v1. v2 should be (A, B, C)" << endl;
		try{
			cout << "//His or Her result: " << endl;
			My_vec v1;
			v1.insert_at_rank(0, 'C');
			v1.insert_at_rank(0, 'B');
			v1.insert_at_rank(0, 'A');
			
			My_vec v2 = v1;
			print_info(v2);
		}catch(exception &error){
			print_exception(error.what());
		}
		cout << endl << endl;
		
		cout << "*******************" << endl;
		cout << "2. MEMBER FUNCTIONS" << endl;
		cout << "*******************" << endl;
		
		
		cout << "--------------------- 2.1 elem_at_rank -------------------" << endl;
		cout << "//use case v3(A, B, C)" << endl;
		try{
			My_vec v3;
			v3.insert_at_rank(0, 'C');
			v3.insert_at_rank(0, 'B');
			v3.insert_at_rank(0, 'A');
			
			try{
				cout << "//elem_at_rank(0) should be A" << endl;
				cout << "//His or Her result: " << endl;
				print_info(v3.elem_at_rank(0));			
			}catch(exception &error){
				print_exception(error.what());
			}
			cout << endl;
			try{
				cout << "//elem_at_rank(-1) should prompt error message indicating index out of range" << endl;
				cout << "//His or Her result: " << endl;
				print_info(v3.elem_at_rank(-1));
			}catch(exception &error){
				print_exception(error.what());
			}
			cout << endl;
			try{
				cout << "//elem_at_rank(3) should prompt error message indicating index out of range" << endl;
				cout << "//His or Her result: " << endl;
				print_info(v3.elem_at_rank(3));
			}catch(exception &error){
				print_exception(error.what());
			}
			cout << endl;
		}catch(exception &e){
			print_exception("Cannot create use case. His insertion code is buggy!");
		}
		
		
		cout << "--------------------- 2.2 insert_at_rank -------------------" << endl;
		cout << "//use case v4(A, B, C)" << endl;
		try{
			My_vec v4;
			v4.insert_at_rank(0, 'C');
			v4.insert_at_rank(0, 'B');
			v4.insert_at_rank(0, 'A');
			try{
				cout << "//After insert_at_rank(0, 'E'), v4 should be (E, A, B, C), v4.get_size()-->4" << endl;
				cout << "//His or Her result: " << endl;
				v4.insert_at_rank(0, 'E');
				print_info(v4);	
				print_info(v4.get_size());
			}catch(exception &error){
				print_exception(error.what());
			}
			cout << endl;
			try{
				cout << "//insert_at_rank(-1, 'F') should prompt error message indicating index out of range" << endl;
				cout << "//His or Her result: " << endl;
				v4.insert_at_rank(-1, 'F');
				print_info(v4);			
			}catch(exception &error){
				print_exception(error.what());
			}
			cout << endl;
			try{
				My_vec v4;
				v4.insert_at_rank(0, 'C');
				v4.insert_at_rank(0, 'B');
				v4.insert_at_rank(0, 'A');
				int outOfRange = v4.get_capacity();
				cout << "//insert_at_rank(" << outOfRange <<", 'E') should prompt error message indicating index out of range" << endl;
				cout << "//His or Her result: " << endl;
				v4.insert_at_rank(outOfRange, 'E');
				print_info(v4);		
			}catch(exception &error){
				print_exception(error.what());
			}
			cout << endl;
		}catch(exception &e){
			print_exception("Cannot create use case. His insertion code is buggy!");
		}
		
		cout << "--------------------- 2.3 replace_at_rank -------------------" << endl;
		cout << "//use case v5(A, B, C)" << endl;
		try{
			My_vec v5;
			v5.insert_at_rank(0, 'C');
			v5.insert_at_rank(0, 'B');
			v5.insert_at_rank(0, 'A');
			try{
				cout << "//After replace_at_rank(0, 'I'), v should be (I, B, C)" << endl;
				cout << "//His or Her result: " << endl;
				v5.replace_at_rank(0, 'I');
				print_info(v5);	
			}catch(exception &error){
				print_exception(error.what());
			}
			cout << endl;
			try{
				cout << "//insert_at_rank(-1, 'T') should prompt error message indicating index out of range" << endl;
				cout << "//His or Her result: " << endl;
				v5.replace_at_rank(-1, 'T');
				print_info(v5);			
			}catch(exception &error){
				print_exception(error.what());
			}
			cout << endl;
			try{
				cout << "//replace_at_rank(" << v5.get_capacity()+1 <<", 'E') should prompt error message indicating index out of range" << endl;
				cout << "//His or Her result: " << endl;
				v5.replace_at_rank(v5.get_capacity()+1, 'E');
				print_info(v5);		
			}catch(exception &error){
				print_exception(error.what());
			}
			cout << endl;
		}catch(exception &e){
			print_exception("Cannot create use case. His insertion code is buggy!");
		}
		
		cout << "--------------------- 2.4 remove_at_rank -------------------" << endl;
		cout << "//use case v6(A, B, C)" << endl;
		try{
			My_vec v6;
			v6.insert_at_rank(0, 'C');
			v6.insert_at_rank(0, 'B');
			v6.insert_at_rank(0, 'A');
			try{
				cout << "//After remove_at_rank(0), v6 should be (B, C) and v6.get_size()-->2" << endl;
				cout << "//His or Her result: " << endl;
				v6.remove_at_rank(0);
				print_info(v6);
				print_info(v6.get_size());
			}catch(exception &error){
				print_exception(error.what());
			}
			cout << endl;
			try{
				cout << "//remove_at_rank(-1) should prompt error message indicating index out of range" << endl;
				cout << "//His or Her result: " << endl;
				v6.remove_at_rank(-1);
				print_info(v6);			
			}catch(exception &error){
				print_exception(error.what());
			}
			cout << endl;
			try{
				cout << "//remove_at_rank(" << v6.get_size() <<", 'E') should prompt error message indicating index out of range" << endl;
				cout << "//His or Her result: " << endl;
				v6.remove_at_rank(v6.get_size());
				print_info(v6);		
			}catch(exception &error){
				print_exception(error.what());
			}
			cout << endl;
		}catch(exception &e){
			print_exception("Cannot create use case. His insertion code is buggy!");
		}
		
		
		cout << "--------------------- 2.5 overloading operator[] -------------------" << endl;
		cout << "//use case v7(A, B, C)" << endl;
		try{
			My_vec v7;
			v7.insert_at_rank(0, 'C');
			v7.insert_at_rank(0, 'B');
			v7.insert_at_rank(0, 'A');
			
			try{
				cout << "//v7[0] should be A" << endl;
				cout << "//His or Her result: " << endl;
				print_info(v7[0]);
			}catch(exception &error){
				print_exception(error.what());
			}
			cout << endl;
			try{
				cout << "//v7[-1] should prompt error message indicating index out of range" << endl;
				cout << "//His or Her result: " << endl;
				print_info(v7[-1]);
			}catch(exception &error){
				print_exception(error.what());
			}
			cout << endl;
			try{
				cout << "//v7[3] should  prompt error message indicating index out of range" << endl;
				cout << "//His or Her result: " << endl;
				print_info(v7[3]);
			}catch(exception &error){
				print_exception(error.what());
			}
			cout << endl;
		}catch(exception &e){
			print_exception("Cannot create use case. His insertion code is buggy!");
		}
		cout << endl;
		
		cout << "***********************" << endl;
		cout << "3. NON-MEMBER FUNCTIONS" << endl;
		cout << "***********************" << endl;
		cout << "---------------------3.1 Overloading operator<<---------------------" << endl;
		cout << "//use case v8(A, B, C): cout << v8 should output (A, B, C)" << endl;
		try{
			My_vec v8;
			v8.insert_at_rank(0, 'C');
			v8.insert_at_rank(0, 'B');
			v8.insert_at_rank(0, 'A');
			try{
				cout << "//His or Her result: " << endl;
				cout << v8 << endl;
			}catch(exception &error){
				print_exception(error.what());
			}
		}catch(exception &error){
			print_exception("Cannot create use case. His insertion code is buggy!");
		}
		cout << endl;
		
		cout << "---------------------3.2 find_max_index---------------------" << endl;
		cout << "//use case: v9(A, B, E, C)" << endl;
		try{
			My_vec v9;
			v9.insert_at_rank(0, 'C');
			v9.insert_at_rank(0, 'E');
			v9.insert_at_rank(0, 'B');
			v9.insert_at_rank(0, 'A');
				
			try{			
				cout << "//find_max_index(v9, 4) should return 2" << endl;
				cout << "//His or Her result: " << endl;
				print_info(find_max_index(v9, 4));
				
			}catch(exception &error){
				print_exception(error.what())
			}
			cout << endl;
			
			try{
				cout << "//use case: empty_verctor" << endl;
				cout << "//find_max_index(empty_vector) should prompt error or return invalid index when the argument vector is empty" << endl;
				cout << "//His or Her result: " << endl;
				My_vec empty_vector;
				//print_info(empty_vector);
				print_info(find_max_index(empty_vector, empty_vector.get_size()));
				
			}catch(exception &error){
				print_exception(error.what())
			}
			cout << endl;
			
			try{
				cout << "//find_max_index(v9,-1) should prompt error or return invalid index when the argument size is less than or equal to zero" << endl;
				//print_info(v);
				cout << "//His or Her result: " << endl;
				print_info(find_max_index(v9,-1));
							
			}catch(exception &error){
				print_exception(error.what())
			}
			
			cout << endl;
			try{
				cout << "//find_max_index(v9, 10) should return 2" << endl;
				cout << "//His or Her result: " << endl;
				//print_info(v);
				print_info(find_max_index(v9, 10));
				
			}catch(exception &error){
				print_exception(error.what())
			}
			
			cout << endl;
		}catch(exception &error){
			print_exception("Cannot create use case. His insertion code is buggy!");
		}
		cout << endl;
		
		cout << "---------------------3.3 sort_max---------------------" << endl;
		try{
			cout << "//use case: v10(B, E, C, A)" << endl;
			My_vec v10;
			v10.insert_at_rank(0, 'A');
			v10.insert_at_rank(0, 'C');
			v10.insert_at_rank(0, 'E');
			v10.insert_at_rank(0, 'B');
			try{
				
				cout << "//After sort_max(v10), v10 should be (A, B, C, E)" << endl;
				cout << "//His or Her result: " << endl;
				sort_max(v10);
				print_info(v10);
				
			}catch(exception &error){
				print_exception(error.what())
			}
		}catch(exception &error){
			print_exception("Cannot create use case. His insertion code is buggy!");
		}
		cout << endl;
		
		try{
			cout << "//use case: v11(A)" << endl;
			My_vec v11;
			v11.insert_at_rank(0, 'A');
			
			try{
				
				cout << "//After sort_max(v11), v11 should be (A)" << endl;
				cout << "//His or Her result: " << endl;
				sort_max(v11);
				print_info(v11);
				
			}catch(exception &error){
				print_exception(error.what())
			}
		}catch(exception &error){
			print_exception("Cannot create use case. His insertion code is buggy!");
		}
		cout << endl;
		
		try{
			cout << "use case: empty_vector()" << endl;
			cout << "After sort_max(empty_vector), empty_vector should be empty" << endl;
			
			My_vec empty_vector;
			
			sort_max(empty_vector);
			print_info(empty_vector);
			
		}catch(exception &error){
			print_exception(error.what())
		}
		cout << endl << endl;
		cout << "Test is done. Please fill the lab quiz form according to the above result and your analysis on his source codes." << endl;
    return 0;
}