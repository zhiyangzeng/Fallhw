#pragma once

#include "TemplateDoublyLinkedList.h"
#include <cstddef>
#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;

// Disjoint Set
template <typename T>
class DisjointSet {
private:
	vector<DListNode<T>*> nodeLocator;  //store by node by key
	//only update nodesize for representative
public:
	~DisjointSet();
	DisjointSet(int n);
	vector<DListNode<T>*> getNodeLocator() const;
	DListNode<T>* MakeSet(int key, T node);
	DListNode<T>* Union(DListNode<T> nodeI, DListNode<T> nodeJ);
	DListNode<T>* FindSet(DListNode<T> node);
	DListNode<T>* FindSet(int nodeKey);
	vector<bool> visible;
};

template <typename T>
DisjointSet<T>::DisjointSet(int n){
	if (n<0) throw runtime_error("Error: cannot declare negative disjoint set");
	nodeLocator.resize(n);
	visible.resize(n);
	for(int i=0; i<n; i++){
		visible[i]=true;
	}
}

template <typename T>
DisjointSet<T>::~DisjointSet<T>(){
	//DListNode<T>* temp;
	for (int i=0; i<getNodeLocator().size(); i++) {
		delete[] nodeLocator[i];
	}
}

template <typename T>
ostream& operator<<(ostream& out, const DisjointSet<T>& ds) {
	for (int i=0; i<ds.getNodeLocator().size(); i++){	
		DListNode<T>* temp=ds.getNodeLocator()[i];
		if (ds.visible[i]!=false){
		cout<<"{";
		while (temp!=NULL){
			cout<<temp->getElem();
			temp=temp->getNext();
		}
		cout<<"}"<<endl;
		}
	}
	return out;
}

template <typename T>
vector<DListNode<T>*> DisjointSet<T>::getNodeLocator() const {
	return nodeLocator;
}

template <typename T>
DListNode<T>* DisjointSet<T>::MakeSet(int key, T node){
	//if (key>nodeLocator.size() || key<=0) throw runtime_error("Error: nodeLocator index out of bounds");
	
	DListNode<T>* n = new DListNode<T>(key, node);
	n->setRepresentative(n);
	n->setTrailer(n);
	
	if (nodeLocator.size() > key)
	{
		nodeLocator[key] = n;
	}
	else
	{
		nodeLocator.resize(2*key);
		nodeLocator[key] = n;
	}
}

template <typename T>
DListNode<T>* DisjointSet<T>::Union(DListNode<T> nodeI, DListNode<T> nodeJ){
	DListNode<T>* rep;
	DListNode<T>* temp;
	if (nodeI.getRepresentative()->getListSize()>= nodeJ.getRepresentative()->getListSize()){ //Append J to I, 3op
		rep=&nodeI;  
		temp = &nodeJ;
	} else { //APPEND I to J
		rep=&nodeJ;
		temp = &nodeI;
	}
		rep=rep->getRepresentative();  //2op
		temp=temp->getRepresentative();  //2op
		if (rep==temp) throw runtime_error("Error: cannot merge the same set"); //1op
		int location=temp->getKey(); //2op
		//link long tail with short head
		temp->setPrevious(rep->getTrailer()); //link temp to original setRep trailer.    2op
		rep->getTrailer()->setNext(temp); //link last of setRep to first of setTemp      2op
		rep->setTrailer(temp->getTrailer()); //set trailer of new rep to last of temp    2op
		temp->setTrailer(temp); //no longer representative, no trailer           1op
		while (temp!=NULL){//shorter list point to new rep              n2*(1+2+2)op
			temp->setRepresentative(rep);   
			rep->setListSize(rep->getListSize()+1);  //size++
			temp=temp->getNext();
		}
		visible[location-1]=false; //no longer print out the shorter list on vector       1op
		//nodeLocator.erase(nodeLocator.begin()+location-1-(get_osize()-nodeLocator.size()));
		return rep;  //1op
}

template <typename T>
DListNode<T>* DisjointSet<T>::FindSet(DListNode<T> node){
	//if (&node==NULL || node.getRepresentative()==NULL) 
	if (node.getRepresentative()!=NULL) {
		return node.getRepresentative();
	} else {
		throw runtime_error("Error: invalid node");
	}
	
}

template <typename T>
DListNode<T>* DisjointSet<T>::FindSet(int nodeKey){
	//if (nodeKey>nodeLocator.size() || nodeKey<=0) throw runtime_error("Error: key value is not valid");
	if (nodeLocator[nodeKey] != NULL)
	{
		return nodeLocator[nodeKey]->getRepresentative();
	}
	
}