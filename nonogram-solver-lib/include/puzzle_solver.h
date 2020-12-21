#pragma once

#include "puzzle.h"

class PuzzleSolver
{
public:
	PuzzleSolver(Puzzle puzzle)
		: m_puzzle(puzzle)
	{
	}

	bool Solve();

private:
	void MarkerRule(const std::vector<int32_t> &values, Puzzle::GridView &grid_view);

	Puzzle m_puzzle;
};

