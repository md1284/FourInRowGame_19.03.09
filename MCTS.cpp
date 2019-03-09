#include <cmath>
#include <cstdlib>
#include <ctime>
#include "MCTS.h"
#include "FourInRowPuzzle.h"

const int INF = 987654321;

MCTS::MCTS() {
}

void MCTS::SetPuzzle(const FourInRowPuzzle &aPuzzle) {
	this->aPuzzle = this->originalPuzzle = aPuzzle;
}

unsigned short MCTS::GetNextPlay() {
	this->aGraph = new Graph<int>;
	unsigned short column = MCTSAlgorithm();
	
	delete(this->aGraph);
	
	return column;
}

unsigned short MCTS::MCTSAlgorithm() {
	int mxdepth = 0;
	this->aGraphNode = new GraphNode<int>;
	this->aGraph->Add(this->aGraphNode);
	
	for(int i = 0; i<100000; i++) {
		//cout << "i: " << i << endl;
		if(this->aPuzzle.IsFull() || this->aPuzzle.IsDone()) {
			if(this->aGraphNode->depth % 2 == 1)
				this->aGraphNode->updateT(int(1.0 / this->aGraphNode->depth * 100));
			else
				this->aGraphNode->updateT(int(-1.0 / this->aGraphNode->depth * 100));
				
			this->aGraphNode = this->aGraph->GetFirstGraphNode();
			this->aPuzzle = this->originalPuzzle;
			continue;
		}
		else if(this->aGraphNode->Edges->empty()) {
			if(this->aGraphNode->n == 0) {
				//cout << "one" << endl;
				this->aGraphNode->updateT(RollOut());
				this->aGraphNode = this->aGraph->GetFirstGraphNode();
				this->aPuzzle = this->originalPuzzle;
				continue;
			}
			else {
				//cout << "two" << endl;
				DevelopChildren();
				this->aGraphNode = this->aGraphNode->Edges->front();
			}
		}
		else {
			//cout << "three" << endl;
			double mx = (this->aGraphNode->depth % 2 == 1 ? INF : -INF);
			GraphNode<int> *mGraphNode;
			
			for(typename vector<GraphNode<int>* >::iterator it = this->aGraphNode->Edges->begin(); it != this->aGraphNode->Edges->end(); it++) {
				if((*it)->n == 0) {
					mGraphNode = *it;
					break;
				}
				if((*it)->depth % 2 == 1 && mx < UCB1(*it)) {
					mGraphNode = *it;
					mx = UCB1(*it);
				}
				else if((*it)->depth % 2 == 0 && mx > UCB1(*it)) {
					mGraphNode = *it;
					mx = UCB1(*it);
				}
				//cout << "t: " << (*it)->t << " n: " << (*it)->n << " UCB1: " << UCB1(*it) << endl;
			}
		
			this->aGraphNode = mGraphNode;
			if(mxdepth < this->aGraphNode->depth)
				mxdepth = this->aGraphNode->depth;
		}
		ApplyMove();
		//cout << this->aPuzzle.ToString() << endl;
	}
	
	this->aGraphNode = this->aGraph->GetFirstGraphNode();
	double mx = -INF;
	GraphNode<int> *mGraphNode;
	
	for(typename vector<GraphNode<int>* >::iterator it = this->aGraphNode->Edges->begin(); it != this->aGraphNode->Edges->end(); it++) {
		if(mx < UCB1(*it)) {
			mGraphNode = *it;
			mx = UCB1(*it);
		}
		cout << "t: " << (*it)->t << " n: " << (*it)->n << " UCB1: " << UCB1(*it) << endl;
	}
	cout << "AI calculated " << mxdepth <<  "depth.";
	return mGraphNode->tokenPosition;
}

double MCTS::UCB1(GraphNode<int> *&aGraphNode) {
	if(aGraphNode->n == 0)	return INF;
	return (1.0 * aGraphNode->t / aGraphNode->n) + 2 * sqrt(log(aGraphNode->n * 1.0) / aGraphNode->n);
}

int MCTS::RollOut() {
	FourInRowPuzzle bPuzzle;
	PUZZLE_HOLE_COLORS::PUZZLE_HOLE_COLORS currentColor;
	currentColor = (this->aGraphNode->depth % 2 == 0 ? PLAYER1 : PLAYER2);
	
	int per = 0;
	
	for(int i = 0; i<100; i++) {
		bPuzzle = this->aPuzzle;
		
		while(!bPuzzle.IsFull() && !bPuzzle.IsDone()) {
			unsigned short column = rand() % 7;
			if(bPuzzle.IsColumnFull(column))	continue;
			
			bPuzzle.AddToken(currentColor, column);
			currentColor = (currentColor == PLAYER1 ? PLAYER2 : PLAYER1);
		}
		
		if(bPuzzle.IsDone()) {
			if(bPuzzle.GetWinner() == PLAYER1)	per--;
			else if(bPuzzle.GetWinner() == PLAYER2)	per++;
		}
	}
	return per;
}

void MCTS::ApplyMove() {
	if (this->aGraphNode->tokenPosition < 7) {
		if ((this->aGraphNode->depth % 2) == 0)
			this->aPuzzle.AddToken(PLAYER1, this->aGraphNode->tokenPosition);
		else
			this->aPuzzle.AddToken(PLAYER2, this->aGraphNode->tokenPosition);
	}
#ifdef DEBUGINING
	cout << this->aPuzzle.ToString() << endl;
#endif
}

void MCTS::RevertBackMove() {
	// check if valid play has been played
	if (this->aGraphNode->tokenPosition < 7)
		this->aPuzzle.RemoveToken(this->aGraphNode->tokenPosition);
	
#ifdef DEBUGINING
	cout << this->aPuzzle.ToString() << endl;
#endif
}

void MCTS::DevelopChildren() {
	GraphNode<int> *graphNodeChild;
	
	for (short column = 0; column < FOUR_IN_ROW_PUZZLE_WIDTH; column++) {
		if (!this->aPuzzle.IsColumnFull(column)) {
			graphNodeChild = new GraphNode<int>;
			graphNodeChild->tokenPosition = column;
			
			this->aGraph->Add(graphNodeChild);
			this->aGraph->AddEdge(this->aGraphNode, graphNodeChild);
		}
	}
}



