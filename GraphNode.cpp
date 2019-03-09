#ifndef ____Puzzle__GraphNode__cpp
#define ____Puzzle__GraphNode__cpp
#include "GraphNode.h"

template <typename T>
GraphNode<T>::GraphNode() {
	this->Edges = new vector< GraphNode<T>* >;
	this->parent = NULL;
	this->tokenPosition = 7;
	
	this->depth = 0;
	this->t = 0;
	this->n = 0;

	this->minMaxValue = -32768;
}

template <typename T>
GraphNode<T>::~GraphNode() {
	delete this->Edges;
}

template <typename T>
void GraphNode<T>::updateT(int r) {
	this->t += r;
	this->n++;

	GraphNode<int> *cur = this;
	while(cur->parent != NULL) {
		cur = cur->parent;
		cur->t += r;
		cur->n++;
	}
}


#endif
