#include "BinarySearchTree.h"
#include "BinaryNode.h"
#include <string>

using namespace std;

int costcount=0;
BinaryNode *BinarySearchTree::find(int x, BinaryNode *t) throw(string)
{
while (t != NULL) {
if (x < t->getElem()) t = t->getLeft();
else if (x > t->getElem()) t = t->getRight(); 
else return t; // found
}
   throw string("Error: item not found");
}

void BinarySearchTree::deleteTree(BinaryNode *root) { // postorder traversal
if (root == NULL) return; // nothing to delete 
   if (root->getLeft() != NULL)
      deleteTree(root->getLeft());
   if (root->right != NULL)
      deleteTree(root->getRight());
   delete root;
}

BinaryNode *BinarySearchTree::findMin(BinaryNode *t) throw(string)
{
   if (t == NULL) {
	   throw string("Error: empty tree.");
   }
   while (t->getLeft() != NULL) t = t->getLeft();
   return t;
}

BinaryNode *BinarySearchTree::insert(int x,
   BinaryNode *t) throw(string)
{
   if (t == NULL) {
	   t = new BinaryNode(x);
	   costcount++;
	   t->setCost(costcount);
	   costcount=0;
   }
   else if (x < t->getElem()){
	   costcount++;
      t->setLeft(insert(x, t->getLeft()));
  }
   else if (x > t->getElem()){
	   costcount++;
	  t->setRight(insert(x, t->getRight()));
  }
   else
      throw string("Error: Duplicate Item.");
   return t;
}

BinaryNode* BinarySearchTree::removeMin(BinaryNode *t) throw(string) // private function
{
   if (t == NULL) {
	   throw string("Error: Item not Found.");
   }
   if (t->getLeft() != NULL) t->setLeft(removeMin(t->getLeft()));
   else {
      BinaryNode *node = t;
      t = t->getRight();
      delete node;
	}
	return t; 
}
//edit
BinaryNode* BinarySearchTree::remove(int x, BinaryNode *t) throw(string) // private function
{
   if (t == NULL) {
	   throw string("Error: item not found.");  
   }
if (x < t->getElem()) t->setLeft(remove(x, t->getLeft()));
else if (x > t->getElem()) t->setRight(remove(x, t->getRight()));
else if (t->getLeft() != NULL && t->getRight() != NULL) // item x is found; t has two children 
{
	t->setElem(findMin(t->getRight())->getElem());
	t->setRight(removeMin(t->getRight()));
} 
else 
{
	BinaryNode *node = t;
	t = (t->getLeft() != NULL) ? t->getLeft() : t->getRight();
	delete node;
}

return t;
}


