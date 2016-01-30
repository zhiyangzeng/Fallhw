#include "Graph.h"
#include "TemplateDoublyLinkedList.h"
#include <iostream>

using namespace std;

void Graph::buildGraph() {
  if((n<0) || (e<0)){
    throw GraphException("either row or column is negative!");
  }
  
  for (int i=0; i<n; i++){
	  DListNode<Vertex>* v= new DListNode<Vertex>(i, Vertex(i));
	  AdjacencyList.push_back(v);
  }
}

void Graph::insertEdge(int i, int j, double w) {
  if(curEdges >= e){
    throw GraphException("edge number is not correct!");
  }
  Edge* e=new Edge(i,j,w);
  EdgeList.push_back(e);
  
  DListNode<Vertex>* vi=AdjacencyList[i]->insert_after(j, Vertex(j));
  DListNode<Vertex>* vj=AdjacencyList[j]->insert_after(i, Vertex(i));
  
  vi->getElem().setEdge(e);
  vj->getElem().setEdge(e);
  
  curEdges++; 
  return;
}

double Graph::getWeight(int i, int j) {
	DListNode<Vertex>* temp=AdjacencyList[i];
	while (temp!=NULL) {
		if (temp->getElem().index==j) {
			if (temp->getElem().edge==NULL) {
				return 0;
			} else {
				return temp->getElem().edge->weight;
			}
	}
		temp=temp->getNext();
	}
	return 0;
}


  