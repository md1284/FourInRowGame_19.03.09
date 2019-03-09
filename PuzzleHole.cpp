#include "PuzzleHole.h"

PuzzleHole::PuzzleHole() {
	this->color = PUZZLE_HOLE_COLORS::NO_COLOR;
}

PuzzleHole::PuzzleHole(const PuzzleHole &B) {
	this->color = B.color;
}

PuzzleHole::~PuzzleHole() {
	
}

bool PuzzleHole::IsEmpty() const {
	return (this->color == PUZZLE_HOLE_COLORS::NO_COLOR);
}

bool PuzzleHole::IsRed() const {
	return (this->color == PUZZLE_HOLE_COLORS::RED);
}

bool PuzzleHole::IsBlack() const {
	return (this->color == PUZZLE_HOLE_COLORS::BLACK);
}

void PuzzleHole::SetColor(const PUZZLE_HOLE_COLORS::PUZZLE_HOLE_COLORS &color) {
	this->color = color;
}

PUZZLE_HOLE_COLORS::PUZZLE_HOLE_COLORS PuzzleHole::GetColor() const {
	return this->color;
}

std::string PuzzleHole::ToString() const {
	std::string aString = "";
	
	if (IsEmpty())
		aString = '_';
	else if (IsRed())
		aString = 'o';
	else if (IsBlack())
		aString = 'x';
	
	return aString;
}








