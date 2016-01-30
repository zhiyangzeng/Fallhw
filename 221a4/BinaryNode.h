#ifndef BINARYNODE_H_
#define BINARYNODE_H_

#include <iostream>
#include <cstddef>
#include <string>
#include <queue>
#include <fstream>

using namespace std;

class TreeOperation {
    public:
       virtual void processNode(int elem, int cost) = 0;
	   
 };
 
 
class PrintTreeNode : public TreeOperation {
	
	
	public:
		int total_cost=0;
    	void processNode(int element,int cost) {
       	  cout << element<<"["<<cost<<"]"<<"  ";
		  total_cost+=cost;
    	}
		void reset() {total_cost=0;}
		
 };

class BinaryNode {
private:
	friend class BinarySearchTree;
	int element;
	int cost;
	BinaryNode *left, *right;	
public:
//cons
	BinaryNode (int e=0, int c=0, BinaryNode *l=NULL, BinaryNode *r=NULL):
	element (e), cost (c), left(l),right(r){}

	BinaryNode *getLeft() {return left;}
	BinaryNode *getRight() {return right;}
	int getElem() {return element;}
	int getCost() { return cost; }
	void setCost(int y) { cost = y; }
	void setElem(int x) { element = x; }
	void setRight(BinaryNode *n) { right = n; }
	void setLeft(BinaryNode *n) { left = n; }
	int size (BinaryNode *t);
	int height(BinaryNode *t);
	BinaryNode *copy();
	
	void preOrderTraversal(TreeOperation& op) {
	   op.processNode(element, cost);
	   if (left != NULL) left->preOrderTraversal(op);
	   if (right != NULL) right->preOrderTraversal(op);
	}

	void inOrderTraversal(TreeOperation& op) {
	   if (left != NULL) left->inOrderTraversal(op);
	   op.processNode(element,cost);
	   if (right != NULL) right->inOrderTraversal(op);
	}

	void postOrderTraversal(TreeOperation& op) {
	   if (left != NULL) left->postOrderTraversal(op);
	   if (right != NULL) right->postOrderTraversal(op);
	   op.processNode(element,cost);
	}
	
	void printTree(BinaryNode* root, string name)
	{ 
	ofstream out;
    queue <BinaryNode*> printfile;
	name=name+".txt";
	out.open(name); 
	int level = 0;

	if (root) printfile.push(root); 		

	while (!printfile.empty()) 
	{ 

		BinaryNode* current = printfile.front(); 
		printfile.pop(); 

		if(level < current->cost) out << endl;
		out << current->element << " ";

		level = current->cost;

		if (current->left)  printfile.push(current->left);
		else if (current->left == NULL) out << "X ";
				
		if (current->right) printfile.push(current->right); 
		else if (current->right == NULL)  out << "X ";

	}
	out.close(); 
 }

};

#endif
