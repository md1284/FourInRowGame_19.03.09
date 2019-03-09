#include "FourInRowPuzzle.h"
#include <iostream>


FourInRowPuzzle::FourInRowPuzzle() {
	this->numberOfPlays = 0;
	this->winner = PUZZLE_HOLE_COLORS::NO_COLOR;
}

FourInRowPuzzle::FourInRowPuzzle(const FourInRowPuzzle &B) {
	this->operator=(B);
}

FourInRowPuzzle::~FourInRowPuzzle() {
}

bool FourInRowPuzzle::IsEmpty() const {
	// check bottom row only
	for (short column = 0; column < FOUR_IN_ROW_PUZZLE_WIDTH; column++)
		if (!this->holes[0][column].IsEmpty())
			return false;
	
	return true;
}

bool FourInRowPuzzle::IsFull() const {
	
	// check higher row only
	for (short column = 0; column < FOUR_IN_ROW_PUZZLE_WIDTH; column++)
		if (this->holes[FOUR_IN_ROW_PUZZLE_HIEGHT - 1][column].IsEmpty())
			return false;
	
	return true;
}

bool FourInRowPuzzle::IsColumnFull(const unsigned short &column) const {
	return (!this->holes[FOUR_IN_ROW_PUZZLE_HIEGHT - 1][column].IsEmpty());
}

void FourInRowPuzzle::AddToken(PUZZLE_HOLE_COLORS::PUZZLE_HOLE_COLORS token, const unsigned short &column) {
	// if column is full, throw error
	if (IsColumnFull(column)) {
		throw FullColumn();
	}
	
	// to indecate at what level the token should be added
	unsigned short row = 0;
	
	// increment untill find empty hole
	while (!this->holes[row][column].IsEmpty())
		row++;
	
	// set this hole with token color
	this->holes[row][column].SetColor(token);
	
	// increment number of plays
	this->numberOfPlays++;
	
}

void FourInRowPuzzle::RemoveToken(const unsigned short &column) {
	// to indecate at what level the token should be removed
	unsigned short row = FOUR_IN_ROW_PUZZLE_HIEGHT - 1;
	
	// decrement untill find non empty hole
	while (this->holes[row][column].IsEmpty())
		row--;
	
	// set this hole with no color
	this->holes[row][column].SetColor(PUZZLE_HOLE_COLORS::NO_COLOR);
	
	// decrement number of plays
	this->numberOfPlays--;
}

bool FourInRowPuzzle::IsDone() {
	
	// to get the current color
	PUZZLE_HOLE_COLORS::PUZZLE_HOLE_COLORS currentColor;
	
	// go through all holes
	for (short row = 0; row < FOUR_IN_ROW_PUZZLE_HIEGHT; row++) {
		for (short column = 0; column < FOUR_IN_ROW_PUZZLE_WIDTH; column++) {
			
			// get currentcolor
			currentColor = this->holes[row][column].GetColor();
			
			
			// if blank hole just continue to the next
			if (currentColor == PUZZLE_HOLE_COLORS::NO_COLOR)
				continue;
			
			
			// check vertically to Upper tokens
			if (row + 3 < FOUR_IN_ROW_PUZZLE_HIEGHT) {
				if (this->holes[row + 1][column].GetColor() == currentColor &&
					this->holes[row + 2][column].GetColor() == currentColor &&
					this->holes[row + 3][column].GetColor() == currentColor) {
					
					// set the winner
					this->winner = currentColor;
					return true;
				}
			}
			
			// check horizontally to right tokens
			if (column + 3 < FOUR_IN_ROW_PUZZLE_WIDTH) {
				if (this->holes[row][column + 1].GetColor() == currentColor &&
					this->holes[row][column + 2].GetColor() == currentColor &&
					this->holes[row][column + 3].GetColor() == currentColor) {
					
					// set the winner
					this->winner = currentColor;
					return true;
				}
			}

			
			// check diagonally Up-Left
			if (row + 3 < FOUR_IN_ROW_PUZZLE_HIEGHT && column - 3 >= 0) {
				if (this->holes[row + 1][column - 1].GetColor() == currentColor &&
					this->holes[row + 2][column - 2].GetColor() == currentColor &&
					this->holes[row + 3][column - 3].GetColor() == currentColor) {
					
					// set the winner
					this->winner = currentColor;
					return true;
				}
			}
			
			// check diagonally Up-Right
			if (row + 3 < FOUR_IN_ROW_PUZZLE_HIEGHT && column + 3 < FOUR_IN_ROW_PUZZLE_WIDTH) {
				if (this->holes[row + 1][column + 1].GetColor() == currentColor &&
					this->holes[row + 2][column + 2].GetColor() == currentColor &&
					this->holes[row + 3][column + 3].GetColor() == currentColor) {
					
					// set the winner
					this->winner = currentColor;
					return true;
				}
			}
			
		}
	}
	
	this->winner = PUZZLE_HOLE_COLORS::NO_COLOR;
	return false;
}

PUZZLE_HOLE_COLORS::PUZZLE_HOLE_COLORS FourInRowPuzzle::GetWinner() const {
	return this->winner;
}

std::string FourInRowPuzzle::ToString() const {
	// the string to be returned
	std::string aString = "";
	
	for (short row = FOUR_IN_ROW_PUZZLE_HIEGHT - 1; row >= 0; row--) {
		for (short column = 0; column < FOUR_IN_ROW_PUZZLE_WIDTH; column++) {
			aString += this->holes[row][column].ToString();
		}
		aString += "\n";
	}
	
	aString += "0123456\n";
	
	return aString;
}



FourInRowPuzzle& FourInRowPuzzle::operator=(const FourInRowPuzzle &B) {
	// go through all holes
	for (short row = 0; row < FOUR_IN_ROW_PUZZLE_HIEGHT; row++)
		for (short column = 0; column < FOUR_IN_ROW_PUZZLE_WIDTH; column++)
			this->holes[row][column].SetColor(B.holes[row][column].GetColor());
	
	return *this;
}








