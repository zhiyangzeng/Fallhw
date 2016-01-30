#include <cstdlib>
#include <iostream>
#include <stdexcept>

using namespace std;

template <typename T>
class DoublyLinkedList; // class declaration

//using namespace std
// extend range_error from <stdexcept>
struct EmptyDLinkedListException : range_error {
  explicit EmptyDLinkedListException(char const* msg=NULL): range_error(msg) {}
};
// list node

template <typename T>
class DListNode {
private: 
  T obj;
  DListNode<T> *prev, *next; //check
  friend class DoublyLinkedList<T>;
public:
  DListNode<T>(T e=T(), DListNode<T> *p = NULL, DListNode<T> *n = NULL)
    : obj(e), prev(p), next(n) {}
  T getElem() const { return obj; }
  DListNode<T> * getNext() const { return next; }
  DListNode<T> * getPrev() const { return prev; }
  
};

// doubly linked list
template <typename T>
class DoublyLinkedList {
protected: DListNode<T> header, trailer;
public:
  DoublyLinkedList<T>() : header(T()), trailer(T()) // constructor
  { header.next = &trailer; trailer.prev = &header; }
  DoublyLinkedList<T>(const DoublyLinkedList<T>& dll); // copy constructor
  ~DoublyLinkedList<T>(); // destructor
  DoublyLinkedList<T>& operator=(const DoublyLinkedList<T>& dll); // assignment operator
  // return the pointer to the first node
  DListNode<T> *getFirst() const { return header.next; } 
  // return the pointer to the trailer
  const DListNode<T> *getAfterLast() const { return &trailer; }
  // return if the list is empty
  bool isEmpty() const { return header.next == &trailer; }
  T first() const; // return the first object
  T last() const; // return the last object
  void insertFirst(T newobj); // insert to the first of the list
  T removeFirst(); // remove the first node
  void insertLast(T newobj); // insert to the last of the list
  T removeLast(); // remove the last node
  DListNode<T>* insertOrderly (const T& obj);  //const T&
};
// output operator
template <typename T>
ostream& operator<<(ostream& out, const DoublyLinkedList<T>& dll);


	
template <typename T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList<T>& dll)
{
  // Initialize the list
  header.next = &trailer; trailer.prev = &header;
  
  DListNode<T> *current = dll.getFirst();
  while(current != dll.getAfterLast())
	{
	  insertFirst(current->getElem());
	  current=current->getNext();
	}
  
}

template <typename T>
DListNode<T>* DoublyLinkedList<T>::insertOrderly (const T& obj){ //O(n)
	
	
	DListNode<T> *current = getFirst();
	if (isEmpty()){
		insertFirst(obj);
		return getFirst();
		
	}
	if (obj<(current->getElem())){
		insertFirst(obj);
		return current;
	} else {
		while (!(obj<(current->getElem()))){
			if (current==trailer.prev){ //if at last element stop
				insertLast(obj);
				return current;
			} 
			current=current->getNext(); //stop at element just bigger than obj
		}
	//insert before current
		DListNode<T> *node = new DListNode<T>(obj, current->prev, current);
		current->prev->next=node;
		current->prev=node;
		return node;
		
	}
	
}
// assignment operator
template <typename T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(const DoublyLinkedList<T>& dll)
{
	
	while (!isEmpty()){
		removeFirst();
	} 
  
    header.next = &trailer; trailer.prev = &header;
    DListNode<T> *current = dll.getFirst();
    while(current != dll.getAfterLast())
	{
  	  insertFirst(current->getElem());
	  current=current->getNext();
    }
	return *this;
}
// insert the object to the first of the linked list
template <typename T>
void DoublyLinkedList<T>::insertFirst(T newobj)
{ 
  DListNode<T> *newNode = new DListNode<T>(newobj, &header, header.next);
  header.next->prev = newNode;
  header.next = newNode;
}
// insert the object to the last of the linked list
template <typename T>
void DoublyLinkedList<T>::insertLast(T newobj)
{
  DListNode<T> *newNode = new DListNode<T>(newobj, trailer.prev,&trailer); //@trailer?
  trailer.prev->next = newNode;
  trailer.prev = newNode;
}
// remove the first object of the list
template <typename T>
T DoublyLinkedList<T>::removeFirst()
{ 
  if (isEmpty())
    throw EmptyDLinkedListException("Empty Doubly Linked List");
  DListNode<T> *node = header.next;
  node->next->prev = &header;
  header.next = node->next;
  T obj = node->obj;
  delete node;
  return obj;
}
// remove the last object of the list
template <typename T>
T DoublyLinkedList<T>::removeLast()
{
  if (isEmpty())
    throw EmptyDLinkedListException("Empty Doubly Linked List");
  DListNode<T> *node = trailer.prev;
  node->prev->next = &trailer;
  trailer.prev = node->prev;
  T obj = node->obj;
  delete node;
  return obj;
}
// destructor
template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList<T>()
{
  DListNode<T> *prev_node, *node = header.next;
  while (node != &trailer) {
    prev_node = node;
    node = node->next;
    delete prev_node;
  }
  header.next = &trailer;
  trailer.prev = &header;
}
// return the first object
template <typename T>
T DoublyLinkedList<T>::first() const
{ 
  if (isEmpty())
    throw EmptyDLinkedListException("Empty Doubly Linked List");
  return header.next->obj;
}
// return the last object
template <typename T>
T DoublyLinkedList<T>::last() const
{
  if (isEmpty())
    throw EmptyDLinkedListException("Empty Doubly Linked List");
  return trailer.prev->obj;
}
// return the list length
template <typename T>
int DoublyLinkedListLength(DoublyLinkedList<T>& dll) {
  DListNode<T> *current = dll.getFirst();
  int count = 0;
  while(current != dll.getAfterLast()) {
    count++;
    current = current->getNext(); //iterate
  }
  return count;
}
// output operator
template <typename T>
ostream& operator<<(ostream& out, const DoublyLinkedList<T>& dll) {
  
    DListNode<T> *current = dll.getFirst();

    while(current != dll.getAfterLast())
	 {
  	  cout<<current->getElem()<<" ";
	  current=current->getNext();
    }
	out<<endl;
  
  return out;
}
