#ifndef ____Puzzle__GraphNode__
#define ____Puzzle__GraphNode__

#include <iostream>
#include <vector>


using namespace std;

template <typename T>
class GraphNode {
public:
	GraphNode();
	~GraphNode();
	
	T tokenPosition;
	
	short minMaxValue;
	vector< GraphNode<T>* > *Edges;
	GraphNode<int> *parent;
	
	void updateT(int r);
	
	int depth;
	int t;
	int n;
};

#include "GraphNode.cpp"
#endif /* defined(____Puzzle__GraphNode__) */
