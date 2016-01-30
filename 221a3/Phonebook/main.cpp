#include "Record.h"
#include "TemplateDoublyLinkedList.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int loadfile(vector<DoublyLinkedList<Record>>& , string);
void printbook(vector<DoublyLinkedList<Record>>&);
int search(vector<DoublyLinkedList<Record>>&);
int vectorsearch(vector<Record>, vector<Record>&, string, int);
	
int main () {
	//search Wiseman, Mary. UIN: 224376947
	vector<DoublyLinkedList<Record>> phonebook (26);
	loadfile(phonebook, "PhoneBook.txt");
	//printbook(phonebook);
	//search(phonebook);
	int input;
	cout<<"Enter 1 to search for a student, enter 2 to print the entire record, enter 3 to display options, enter any other number to quit:   ";
	cin>>input;
	while (input==1|input==2|input==3){
		if (input==1){
			search(phonebook);
		}
		if (input==2){
			printbook(phonebook);
		}
		if (input==3){
			cout<<"Enter 1 to search for a student, enter 2 to print the entire record, enter 3 to display options, enter any other number to quit\n";
		}
		cout<<"Enter option 1~3 again or any other number to quit program:  ";
		cin>>input;
	}
	return 0;
}

int loadfile(vector<DoublyLinkedList<Record>>& phonebook, string filename){
	ifstream in(filename);
	if(!in.good())
	{
		cout<<"File not found.\n";
		return 1;
	}
	string lname, fname, uin, num;
	while (!in.eof()){
		in>>lname>>fname>>uin>>num;
		Record r(lname, fname, uin, num);
		phonebook[0+(tolower(lname.at(0))-'a')].insertOrderly(r);   //vector[x].insertOrderly(Record)
		in.get();//skips empty line
	}
	in.close();
	return 0;
	
}

void printbook(vector<DoublyLinkedList<Record>>& phonebook){
	for (int i=0; i<26; ++i){
		if(!phonebook[i].isEmpty())
			cout<<phonebook[i]<<endl;
	}
}
int vectorsearch(vector<Record> found, vector<Record>& vec, string s, int choice){ //takes a found vector, modifies a new record by searching for s by either first name(choice 1) or UIN(choice 2) and return that vector for further task
	if (choice==1){//search last name
		for (int i =0; i<found.size();i++){
			string temp=found[i].get_first_name();
			transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
			if (temp==s){
				vec.push_back(found[i]);
			}}} 
	else if (choice ==2){
		for (int i =0; i<found.size();i++){
			if (found[i].get_uin()==s){
				vec.push_back(found[i]);
			}}} 
	else {
		cout<<"Invalid choice\n"<<endl;
		return -1;
	}
	//after generating new vec
	if (vec.empty()){ //no first name found
		cout<<"No record found\n";
		return -1;
	} 
	else if (vec.size()==1){ //1 first name found
		return 0;
	}
	else if (vec.size()>1){ //more than 1 first name found
		return 1;
	} else {cout<<"Something is wrong\n";return -1; }
}

int search(vector<DoublyLinkedList<Record>>& phonebook){
	string lname;
	cout<<"Input student last name    ";
	cin>>lname;
	//search LL for that
	int loc= 0+(tolower(lname.at(0))-'a');
	DListNode<Record> *current = phonebook[loc].getFirst();
	vector<Record> found;
	transform(lname.begin(), lname.end(), lname.begin(), ::tolower);
	while (current!=phonebook[loc].getAfterLast()){
		string temp=current->getElem().get_last_name();
		transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
		if (temp==lname){
			found.push_back(current->getElem());
		}
		current=current->getNext();
    }
	if (found.empty()){ //no last name found
		cout<<"Name not found.\n";
		return -1;
	} 
	else if (found.size()==1){ //1 record found
		cout<<"Student found.\n";
		cout<<found[0]<<endl;
		return 0;
	}
	else if (found.size()>1){
		cout<<"More than one student with the same last name found. Please enter first name to search:   ";
		string fname;
		cin>>fname;
		transform(fname.begin(), fname.end(), fname.begin(), ::tolower);
		vector<Record> foundf;
		int result=vectorsearch(found,foundf,fname,1);
		if (result==-1) {return -1;}
		else if (result==0){
			cout<<"Student found.\n";
			cout<<foundf[0]<<endl;
			return 0;}
		else if (result==1){
			cout<<"More than one student with the same last and first name found. Please enter UIN to search:   ";
			string uin;
			cin>>uin;
			vector<Record> foundu;
			result=vectorsearch(foundf,foundu,uin,2);
			if (result==-1) {return -1;}
			else if (result==0 || result==1){ //same Last name, First name, UIN, just print the first duplicate
				cout<<"Student found.\n";
				cout<<foundu[0]<<endl;
				return 0;
			} else {cout<<"Something is wrong\n";return -1; }}} 
	
	else {cout<<"Something is wrong\n";return -1; }}





