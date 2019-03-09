#ifndef __MinMaxAlgorithm__FourInRowPuzzle__
#define __MinMaxAlgorithm__FourInRowPuzzle__

#include <iostream>
#include "PuzzleHole.h"

// define the hieght and the width of the puzzle
#define FOUR_IN_ROW_PUZZLE_HIEGHT 6
#define FOUR_IN_ROW_PUZZLE_WIDTH 7


// declaration of MinMaxAlgorithm
class MinMaxAlgorithm;


// error classes //
class FullColumn {};

class FourInRowPuzzle {
	// making MinMaxAglorithm class as friend class
	friend class MinMaxAlgorithm;
	
public:
	
	// constructor
	FourInRowPuzzle();
	
	// copy constructor
	FourInRowPuzzle(const FourInRowPuzzle &B);
	
	// deconstructor
	~FourInRowPuzzle();
	
	
	// IsEmpty returns true if no token has been played
	bool IsEmpty() const;

	
	// IsFull returns true if no more place for new token to be played
	bool IsFull() const;
	
	
	// IsColumnFull returns true if the column is full
	bool IsColumnFull(const unsigned short &column) const;
	
	
	// Add a token
	void AddToken(PUZZLE_HOLE_COLORS::PUZZLE_HOLE_COLORS token, const unsigned short &column);
	
	
	// remove a token
	void RemoveToken(const unsigned short &column);
	
	
	// when someone won
	bool IsDone();
	
	
	// get the winner color
	PUZZLE_HOLE_COLORS::PUZZLE_HOLE_COLORS GetWinner() const;
	
	
	// returns string
	std::string ToString() const;
	
	// operators
	FourInRowPuzzle& operator=(const FourInRowPuzzle &B);
	
private:
	PuzzleHole holes[FOUR_IN_ROW_PUZZLE_HIEGHT][FOUR_IN_ROW_PUZZLE_WIDTH];
	unsigned short numberOfPlays;
	
	PUZZLE_HOLE_COLORS::PUZZLE_HOLE_COLORS winner;
};








#endif /* defined(__MinMaxAlgorithm__FourInRowPuzzle__) */
