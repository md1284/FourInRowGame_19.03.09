#ifndef ____Puzzle__Graph__
#define ____Puzzle__Graph__

#include <iostream>
#include "GraphNode.h"
#include <vector>


template <typename T>
class Graph {
public:
	
	// constructor
	Graph();
	
	// copy constructor
	Graph(const Graph &graphB);
	
	~Graph();
	
	void Add(GraphNode<T> *aGraphNode);
	void AddEdge(GraphNode<T> *A, GraphNode<T> *B);
	unsigned long long int GetGraphNodesCount() const;
	GraphNode<T>* GetFirstGraphNode();
	
private:
	vector< GraphNode<T>* > GraphNodeList;
	
	// to count how many graph nodes have been created
	unsigned long long int graphNodesCount;
};


#include "Graph.cpp"
#endif /* defined(____Puzzle__Graph__) */
