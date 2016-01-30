#include "disjointset.h"
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
/*
vector<Edge*> merge(vector<Edge*> left, vector<Edge*> right)
{
   vector<Edge*> result;
   while ((int)left.size() > 0 || (int)right.size() > 0) {
      if ((int)left.size() > 0 && (int)right.size() > 0) {
         if ((int)left.front()->weight <= (int)right.front()->weight) {
            result.push_back(left.front());
            left.erase(left.begin());
         } 
	 else {
            result.push_back(right.front());
            right.erase(right.begin());
         }
      }  else if ((int)left.size() > 0) {
            for (int i = 0; i < (int)left.size(); i++)
               result.push_back(left[i]);
            break;
      }  else if ((int)right.size() > 0) {
            for (int i = 0; i < (int)right.size(); i++)
               result.push_back(right[i]);
            break;
      }
   }
   return result;
}
*/
/*  
vector<Edge*> Graph::sortEdge(vector<Edge*> EdgeList) {
  //implement your code here
	if (EdgeList.size()<=1) {return EdgeList;}
	vector<Edge*> left, right, result;
	int middle=((int)EdgeList.size()+1)/2;
	for (int i=0; i<middle; i++){
		left.push_back(EdgeList[i]);
	}
	for (int i=middle; i<(int)EdgeList.size(); i++){
		right.push_back(EdgeList[i]);
	}
	left=sortEdge(left);
	right=sortEdge(right);
	result=merge(left,right);
	
	return result;
}
*/
bool sortfunc(Edge* i, Edge* j){
	return (i->weight < j->weight);
}

void Graph::sortEdge(){
	sort(EdgeList.begin(), EdgeList.end(), sortfunc);
}

double Graph::add_weight()
{
  double result = 0;
  for (int w = 0; w <MST.size(); w++) 
  {
	result += MST[w]->weight;
  }
  return result;
}

double Graph::MSTAlgo() {
  sortEdge();
  //make set for each vertex
  DisjointSet<Vertex> Set(n);
  for (int i=0; i<n; i++){
	  Set.MakeSet(i, Vertex(i));
  }
  //traverse each edge and union 
  for (int j=0; j<EdgeList.size(); j++){
	  int u=EdgeList[j]->vertex_i;
	  int v=EdgeList[j]->vertex_j;
	  if (Set.FindSet(u)!=Set.FindSet(v)){
		  MST.push_back(EdgeList[j]);
		  Set.Union(*(Set.FindSet(u)),*(Set.FindSet(v)));
	  }		  	
  }
  return add_weight();
}

  