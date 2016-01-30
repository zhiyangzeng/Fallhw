#include "BinarySearchTree.h"
#include <iostream>
#include <fstream>

using namespace std;

int main() {
	bool keepgoing=true;
	while (keepgoing) {
		ifstream in;
		string treename="";
		cout<<"select the tree you want to build or enter quit. 1-12 (p/l/r):  ";
		cin>>treename;
		if (treename=="quit"){
			keepgoing=false;
		break;
		}
		string treeid="test//"+treename;
		in.open(treeid); //test//4p
		if(!in){
			cout<<"Unable to open file";
			exit(1);
		}
		BinarySearchTree tree;
		int input=0;
		try {
	
			while (in>>input){   //eof: reads last line+eof, bad
				cout<<"input is "<<input<<endl;
				tree.insert(input);
			}
		
		PrintTreeNode pt;
		cout<<"start printing in order\n";
		tree.getRoot()->inOrderTraversal(pt); 
		cout<<endl;
	
		cout<<"start printing pre order\n";
		tree.getRoot()->preOrderTraversal(pt); 
		cout<<endl;
	
		cout<<"start printing post order\n";
		tree.getRoot()->postOrderTraversal(pt); //getroot>
		cout<<endl;
		int size=tree.size();
		cout<<"Total cost is: "<<pt.total_cost<<endl;
		cout<<"Total size is: "<<size<<endl;
		cout<<"Average cost is: "<<pt.total_cost/size<<endl;
		pt.reset();
		//remove a node
		
		cout<<"remove a node:  ";
		int remove_node;
		cin>>remove_node;
		tree.remove(remove_node);
		cout<<"start printing in order after removal\n";
		tree.getRoot()->inOrderTraversal(pt); 
		cout<<endl;
		
	
		if (tree.size()<16) tree.getRoot()->printTree(tree.getRoot(), treename);
		in.close();
	}
	catch (string s)
	{
		cout<<s<<endl;
	}
	}
	
	return 0;
}