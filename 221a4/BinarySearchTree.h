#ifndef BINARYTREE_H_
#define BINARYTREE_H_

#include "BinaryNode.h"

using namespace std;

class BinarySearchTree { //uses the class BinaryNode
private:
	
BinaryNode* root;//some private functions will be here
BinaryNode* insert(int x,BinaryNode *t) throw(string);
BinaryNode* findMin(BinaryNode *t) throw(string);
BinaryNode* find(int x, BinaryNode *t) throw(string);
BinaryNode* removeMin(BinaryNode *t) throw(string);
BinaryNode* remove(int x, BinaryNode *t)throw(string);

public:

BinarySearchTree( ) { root = NULL; }
~BinarySearchTree( ) { deleteTree(root); root = NULL; }
int size() {return (root==NULL) ? 0 : root->size(root);}
int height() {return (root==NULL) ?0 : root->height(root);}
bool isEmpty(){ return root == NULL; }
void deleteTree(BinaryNode *root);
void insert(int x) throw(string){ root = insert(x, root);}
void remove(int x) throw(string){ root = remove(x, root);}
BinaryNode* find(int x) throw(string){ return find(x, root);}
BinaryNode* getRoot() throw(string){ 
	if (root==NULL) throw string("Error: empty tree.");
	
	else return root; }
};

#endif