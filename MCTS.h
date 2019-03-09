#ifndef __MCTS__
#define __MCTS__

#include <iostream>
#include "FourInRowPuzzle.h"
#include "Graph.h"

#define PLAYER1 PUZZLE_HOLE_COLORS::RED
#define PLAYER2 PUZZLE_HOLE_COLORS::BLACK

class MCTS {
	public:
		MCTS();
		void SetPuzzle(const FourInRowPuzzle &aPuzzle);
		unsigned short GetNextPlay();
		unsigned long long int GetGraphNodesCount()	const;
	
	private:
		void ApplyMove();
		void DevelopChildren();
		void RevertBackMove();
		unsigned short MCTSAlgorithm();
		double UCB1(GraphNode<int> *&aGraphNode);
		int RollOut();
		
		FourInRowPuzzle originalPuzzle;
		FourInRowPuzzle aPuzzle;
		Graph<int> *aGraph;
		GraphNode<int> *aGraphNode;
};

#endif
