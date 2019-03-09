#ifndef ____Puzzle__Graph__cpp
#define ____Puzzle__Graph__cpp
#include "Graph.h"

template <typename T>
Graph<T>::Graph() {

	// zero up the counter
	this->graphNodesCount = 0;
}

template <typename T>
Graph<T>::Graph(const Graph &graphB) {
	
}

template <typename T>
Graph<T>::~Graph() {
	
	// delete all graph nodes in the graph
	for (typename vector<GraphNode<T>*>::iterator it = GraphNodeList.begin(); it != GraphNodeList.end(); it++)
		delete (*it);
	
	this->GraphNodeList.clear();
}

template <typename T>
void Graph<T>::Add(GraphNode<T> *aGraphNode) {
	aGraphNode->parent = NULL;
	this->GraphNodeList.push_back(aGraphNode);
	this->graphNodesCount++;
}

template <typename T>
void Graph<T>::AddEdge(GraphNode<T> *A, GraphNode<T> *B) {
	B->parent = A;
	B->depth = A->depth + 1;
	
	A->Edges->push_back(B);
}

template <typename T>
GraphNode<T>* Graph<T>::GetFirstGraphNode() {
	return this->GraphNodeList.front();
}

template <typename T>
unsigned long long int Graph<T>::GetGraphNodesCount() const {
	return this->graphNodesCount;
}














#endif
