#include "MinMaxAlgorithm.h"

MinMaxAlgorithm::MinMaxAlgorithm() {
	
	// default is 10
	this->maxDepth = 5;
	
#ifdef DEBUGINING
	this->maxDepth = 3;
#endif
}

void MinMaxAlgorithm::SetPuzzle(const FourInRowPuzzle &aPuzzle) {
	this->aPuzzle = this->originalPuzzle = aPuzzle;
}

void MinMaxAlgorithm::SetMaxDepth(const unsigned short maxDepth) {
	this->maxDepth = maxDepth;
}

unsigned short MinMaxAlgorithm::GetNextPlay() {

	// if Graph is initiated, delete it
//	if (this->aGraph)
//		delete this->aGraph;
	
	// allocate a new graph
	this->aGraph = new Graph<int>;
	
	// call DepthFirstSearch function
	return DepthFirstSearch();
}

unsigned short MinMaxAlgorithm::DepthFirstSearch() {
	
	// create first node
	this->aGraphNode = new GraphNode<int>;
	
	// add it in the graph
	this->aGraph->Add(this->aGraphNode);
	
	// push it to stack
	this->aStack.push(this->aGraphNode);
	
	
	// while stack is not empty
	while (!this->aStack.empty()) {
				
		// get the top graphNode from stack
		this->aGraphNode = this->aStack.top();
		
		
		// if it has no children and
		// not reach the maxDepth and not full, then develop children
		if (this->aGraphNode->Edges->empty() && this->aGraphNode->depth < maxDepth && !this->aPuzzle.IsFull()) {
			
			// apply the move of this current aGraphNode
			ApplyMove();
			
			// check if it's not done yet
			if (!this->aPuzzle.IsDone()) {
				
				// check if need to develop children based on Alpha-Beta Alorithm
				if (IsNeedToDevelopChildren())
					// develop children
					DevelopChildren();
				else
					PopOutOfStackAndRevertMove();
			
			// else if done
			} else {
				// just calculate the minMaxValue
				CalculateMinMaxValue();
				
				PopOutOfStackAndRevertMove();
			}
		}
		
		// else if it has no children and
		// reach the maxDepth (i.e. leaf node), then calculate minMaxValue
		else if (this->aGraphNode->Edges->empty() && this->aGraphNode->depth >= maxDepth) {
			
			// apply the move of this current aGraphNode
			ApplyMove();
			
			// check if it's done
			this->aPuzzle.IsDone();
			
			// calculate minMaxValue
			CalculateMinMaxValue();
			
			PopOutOfStackAndRevertMove();
		}
		
		// else if it has children and Depth is even, get Max child value
		else if (!this->aGraphNode->Edges->empty() && (this->aGraphNode->depth % 2) == 0) {
			
			// get Max child value
			this->aGraphNode->minMaxValue = GetMaxChildValue(this->aGraphNode);
			
			PopOutOfStackAndRevertMove();
		}
		
		// else if it has children and Depth is odd, get Min child value
		else if (!this->aGraphNode->Edges->empty() && (this->aGraphNode->depth % 2) == 1) {
			
			// get Min child value
			this->aGraphNode->minMaxValue = GetMinChildValue(this->aGraphNode);
			
			PopOutOfStackAndRevertMove();
		}
	} // end while
	
	// get the right play from root's children
	for (typename vector< GraphNode<int>* >::iterator it = this->aGraphNode->Edges->begin(); it != this->aGraphNode->Edges->end(); it++)
		if (this->aGraphNode->minMaxValue == (*it)->minMaxValue)
			return (*it)->tokenPosition;
	
	return this->aGraphNode->tokenPosition;
}

void MinMaxAlgorithm::ApplyMove() {
	// check if valid play has been played
	if (this->aGraphNode->tokenPosition < 7) {
		// check if player1 has been played
		if ((this->aGraphNode->depth % 2) == 1)
			this->aPuzzle.AddToken(PLAYER1, this->aGraphNode->tokenPosition);
		// or player2
		else
			this->aPuzzle.AddToken(PLAYER2, this->aGraphNode->tokenPosition);
	}
	
#ifdef DEBUGINING
	cout << this->aPuzzle.ToString() << endl;
#endif
}

void MinMaxAlgorithm::RevertBackMove() {
	// check if valid play has been played
	if (this->aGraphNode->tokenPosition < 7)
		this->aPuzzle.RemoveToken(this->aGraphNode->tokenPosition);
	
#ifdef DEBUGINING
	cout << this->aPuzzle.ToString() << endl;
#endif
}

void MinMaxAlgorithm::GetTopFromStackAndApplyMove() {
	// get the top graphNode from stack
	this->aGraphNode = this->aStack.top();
	
	// apply the move of this current aGraphNode
	ApplyMove();
}

void MinMaxAlgorithm::PopOutOfStackAndRevertMove() {
	// revert back the move
	RevertBackMove();
	
	// pop the graph node
	this->aStack.pop();
}

bool MinMaxAlgorithm::IsNeedToDevelopChildren() {
	short max = NOT_ASSIGNED;
	short min = NOT_ASSIGNED;
	
	// check if parent or parents' parent are NULLS, then return true need to develop children
	if (this->aGraphNode->parent == NULL || this->aGraphNode->parent->parent == NULL)
		return true;
	
	
	// check if the graph node in max level
	if ((this->aGraphNode->depth % 2) == 0) {
		// get min of brothers
		min = GetMinChildValue(this->aGraphNode->parent);
		
		// get max of unculs
		max = GetMaxChildValue(this->aGraphNode->parent->parent);
	}
	// else if it is in min level
	else if ((this->aGraphNode->depth % 2) == 1) {
		// get max of brothers
		max = GetMaxChildValue(this->aGraphNode->parent);
		
		// get min of unculs
		min = GetMinChildValue(this->aGraphNode->parent->parent);
	}
	
	// if max or min still not assigned, then return true need to develop children
	if (max == NOT_ASSIGNED || min == NOT_ASSIGNED)
		return true;
	
	// return false if max is greater than min
	return !(max > min);
}

void MinMaxAlgorithm::DevelopChildren() {
	
	// new graph node child
	GraphNode<int> *graphNodeChild;
	
	// go through all possible next play
	for (short column = 0; column < FOUR_IN_ROW_PUZZLE_WIDTH; column++) {
		// check if column is not full
		if (!this->aPuzzle.IsColumnFull(column)) {
			
			// create new graph node child
			graphNodeChild = new GraphNode<int>;
			
			// set the token to be played
			graphNodeChild->tokenPosition = column;
			
			// add it to graph
			this->aGraph->Add(graphNodeChild);
			
			// add it to the parent edges
			this->aGraph->AddEdge(this->aGraphNode, graphNodeChild);
			
			
			// push it to the stack
			this->aStack.push(graphNodeChild);
		} // end if
	} // end for column
}

short MinMaxAlgorithm::GetMaxChildValue(GraphNode<int> *&aGraphNode) {
	short max = NOT_ASSIGNED;
	
	for (typename vector< GraphNode<int>* >::iterator it = aGraphNode->Edges->begin(); it != aGraphNode->Edges->end(); it++)
		if ( (*it)->minMaxValue != NOT_ASSIGNED && (*it)->minMaxValue > max )
			max = (*it)->minMaxValue;

	return max;
}

short MinMaxAlgorithm::GetMinChildValue(GraphNode<int> *&aGraphNode) {
	short min = NOT_ASSIGNED;
	
	for (typename vector< GraphNode<int>* >::iterator it = aGraphNode->Edges->begin(); it != aGraphNode->Edges->end(); it++)
		if ((*it)->minMaxValue != NOT_ASSIGNED && (min == NOT_ASSIGNED || (*it)->minMaxValue < min) )
			min = (*it)->minMaxValue;
	
	return min;
}

void MinMaxAlgorithm::CalculateMinMaxValue() {
	// check if player1 won
	if (this->aPuzzle.GetWinner() == PLAYER1)
		// set minMaxValue to win value
		this->aGraphNode->minMaxValue = WIN_VALUE;
		
	// check if player2 won
	else if (this->aPuzzle.GetWinner() == PLAYER2)
		// set minMaxValue to loss value
		this->aGraphNode->minMaxValue = LOSS_VALUE;
		
	else
		// count up the sequentials
		this->aGraphNode->minMaxValue = CountSequentials() + CountCenterColumn();
}

short MinMaxAlgorithm::CountSequentials() {
#ifdef DEBUGINING
	cout << this->aPuzzle.ToString() << endl;
#endif
	return (CountSequentials(PLAYER1) - CountSequentials(PLAYER2));
}

short MinMaxAlgorithm::CountSequentials(const PUZZLE_HOLE_COLORS::PUZZLE_HOLE_COLORS &color) {
	// to hold the results
	short result = 0;
	
	// go through all holes
	for (short row = 0; row < FOUR_IN_ROW_PUZZLE_HIEGHT - 1; row++) {
		for (short column = 0; column < FOUR_IN_ROW_PUZZLE_WIDTH; column++) {
			// if this is same color token then count for sequential tokens
			if (this->aPuzzle.holes[row][column].GetColor() == color) {
				
				// check vertically to Upper token
				if (this->aPuzzle.holes[row + 1][column].GetColor() == color)
					result += 2;
				
				// check horizontally to right token
				if (column < FOUR_IN_ROW_PUZZLE_WIDTH - 1 && this->aPuzzle.holes[row][column + 1].GetColor() == color)
					result += 2;
				
				// check diagonally Up-Left
				if (column > 0 && this->aPuzzle.holes[row + 1][column - 1].GetColor() == color)
					result += 2;
				
				// check diagonally Up-Right
				if (column < FOUR_IN_ROW_PUZZLE_WIDTH - 1 && this->aPuzzle.holes[row + 1][column + 1].GetColor() == color)
					result += 2;
			} // if
		} // for column
	} // for row
	
	return result;
}

short MinMaxAlgorithm::CountCenterColumn() {
	short result = 0;
	
	// go through all holes in center column
	for (short row = 0; row < FOUR_IN_ROW_PUZZLE_HIEGHT - 1; row++) {
		if (this->originalPuzzle.holes[row][3].IsEmpty() && this->aPuzzle.holes[row][3].GetColor() == PLAYER1)
			result += 10;
		else if (this->originalPuzzle.holes[row][3].IsEmpty() && this->aPuzzle.holes[row][3].GetColor() == PLAYER2)
			result -= 10;
	}
	
	return result;
}

unsigned long long int MinMaxAlgorithm::GetGraphNodesCount() const {
	return this->aGraph->GetGraphNodesCount();
}






