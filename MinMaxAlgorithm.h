#ifndef __MinMaxAlgorithm__MinMaxAlgorithm__
#define __MinMaxAlgorithm__MinMaxAlgorithm__

#include <iostream>
#include <stack>
#include "FourInRowPuzzle.h"
#include "Graph.h"

#define PLAYER1 PUZZLE_HOLE_COLORS::RED
#define PLAYER2 PUZZLE_HOLE_COLORS::BLACK

#define WIN_VALUE 32767
#define LOSS_VALUE -32767
#define NOT_ASSIGNED -32768

//#define DEBUGINING


class MinMaxAlgorithm {
public:
	
	// constructor
	MinMaxAlgorithm();
	
	// SetPuzzle to be solved
	void SetPuzzle(const FourInRowPuzzle &aPuzzle);
	
	// setting the max depth for DFS
	void SetMaxDepth(const unsigned short maxDepth);
	
	
	// get the next suggested play
	unsigned short GetNextPlay();
	
	// get how many graph nodes have been created
	unsigned long long int GetGraphNodesCount() const;
	
private:
	
	// the depth first search algorithm
	unsigned short DepthFirstSearch();
	
	// apply move
	void ApplyMove();
	
	// revert back the move
	void RevertBackMove();
	
	void GetTopFromStackAndApplyMove();
	
	void PopOutOfStackAndRevertMove();
	
	// is need to develop children based on Alpha-Beta check
	bool IsNeedToDevelopChildren();
	
	// develop children
	void DevelopChildren();
	
	// GetMaxChildValue
	short GetMaxChildValue(GraphNode<int> *&aGraphNode);
	
	// GetMinChildValue
	short GetMinChildValue(GraphNode<int> *&aGraphNode);
	
	
	// calculate minMaxValue for leaf nodes
	void CalculateMinMaxValue();
	
	// count up the sequentials in the game
	short CountSequentials();
	
	// CountSequentials Helper function
	short CountSequentials(const PUZZLE_HOLE_COLORS::PUZZLE_HOLE_COLORS &color);
	
	
	short CountCenterColumn();
	
	
	// original puzzle for comparision
	FourInRowPuzzle originalPuzzle;
	
	// a FourInRowPuzzle instance
	FourInRowPuzzle aPuzzle;
	
	// maximum depth for DFS
	unsigned short maxDepth;
	
	// graph ADT
	Graph<int> *aGraph;
	
	// graph node
	GraphNode<int> *aGraphNode;
	
	// stack
	stack< GraphNode<int>* > aStack;

};

#endif /* defined(__MinMaxAlgorithm__MinMaxAlgorithm__) */

