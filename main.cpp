#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <Windows.h>
#include "FourInRowPuzzle.h"
#include "Graph.h"
#include "GraphNode.h"
#include "MinMaxAlgorithm.h"
#include "MCTS.h"

#define PLAYER1 PUZZLE_HOLE_COLORS::RED	// human
#define PLAYER2 PUZZLE_HOLE_COLORS::BLACK	// AI

using namespace std;

void TestSizes() {
	cout << "sizeof(PuzzleHole): " << sizeof(PuzzleHole) << " Bytes" << endl;
	cout << "sizeof(FourInRowPuzzle): " << sizeof(FourInRowPuzzle) << " Bytes" << endl;
	cout << "sizeof(MinMaxAlgorithm): " << sizeof(MinMaxAlgorithm) << " Bytes" << endl;
	cout << "sizeof(GraphNode<int>): " << sizeof(GraphNode<int>) << " Bytes" << endl;
	cout << "sizeof(Graph<int>): " << sizeof(Graph<int>) << " Bytes" << endl;
}

void TestFourInRowPuzzle() {
	FourInRowPuzzle p;
	PUZZLE_HOLE_COLORS::PUZZLE_HOLE_COLORS currentColor;
	unsigned short column = 0;
	unsigned short maxDepth;
	bool algo = false;
	
	srand(time(NULL));
	
	// initial setting
	//cout << "0: using MinMax, 1: using MCTS ";
	//cin >> algo;
	
	//if(algo == false) {
	//	cout << "enter max depth: ";
	//	cin >> maxDepth;
		
	//	MinMaxAlgorithm AI;
	//	AI.SetMaxDepth(maxDepth);
	//}
	MCTS AI;
	
	bool first = false;
	//cout << "0: you play first, 1: AI play first: ";
	//cin >> first;
	first = 1;
	currentColor = (first == 0 ? PLAYER1 : PLAYER2);
	
	while(!p.IsFull() && !p.IsDone()) {
		cout << p.ToString() << endl;
		
		if(currentColor == PLAYER1) {
			cout << "your turn, type a column number: ";
			cin >> column;
		}
		else if(currentColor == PLAYER2) {
			AI.SetPuzzle(p);
			cout << "AI is thinking ... " << endl;
			clock_t sclock, eclock;
			sclock = clock();
			
			// algorithm
			column = AI.GetNextPlay();
			
			eclock = clock();
			cout << "Done !\n\n"; 
			cout << ((double)(eclock - sclock) / CLOCKS_PER_SEC) << " second. Clear!!\n\n";
			cout << "AI select " << column << "." << endl;
		}

		p.AddToken(currentColor, column);
		currentColor = (currentColor == PLAYER1 ? PLAYER2 : PLAYER1);
	}
	
	cout << p.ToString() << endl;
	if (p.IsDone()) {
		if (p.GetWinner() == PUZZLE_HOLE_COLORS::RED)
			cout << "you won!\n";
		else if (p.GetWinner() == PUZZLE_HOLE_COLORS::BLACK)
			cout << "AI won!\n";
	} else {
		cout << "No body won!\n";
	}
}

int main() {

	TestFourInRowPuzzle();
	TestSizes();
	
	system("pause");
    return 0;
}

