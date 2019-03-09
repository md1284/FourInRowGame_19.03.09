//
//  PuzzleHole.h
//  MinMaxAlgorithm
//
//  Created by Hamad Almarri on 12/14/2013.
//

#ifndef __MinMaxAlgorithm__PuzzleHole__
#define __MinMaxAlgorithm__PuzzleHole__

#include <iostream>

// puzzle holes colors
namespace PUZZLE_HOLE_COLORS {
	enum PUZZLE_HOLE_COLORS {NO_COLOR, RED, BLACK};
};


class PuzzleHole {
public:
	// constructor
	PuzzleHole();
	
	// copy constructor
	PuzzleHole(const PuzzleHole &B);
	
	// deconstructor
	~PuzzleHole();
	
	// IsEmpty returns true if hole has no color
	bool IsEmpty() const;
	
	// IsRed returns true if hole has RED color
	bool IsRed() const;
	
	// IsBlack returns true if hole has BLACK color
	bool IsBlack() const;
	
	// SetColor sets a color for the hole
	void SetColor(const PUZZLE_HOLE_COLORS::PUZZLE_HOLE_COLORS &color);
	
	
	// GetColor returns what color is this hole
	PUZZLE_HOLE_COLORS::PUZZLE_HOLE_COLORS GetColor() const;
	
	
	std::string ToString() const;
	
private:
	// the color of the hole
	PUZZLE_HOLE_COLORS::PUZZLE_HOLE_COLORS color;
};


#endif /* defined(__MinMaxAlgorithm__PuzzleHole__) */
