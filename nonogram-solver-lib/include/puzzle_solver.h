#pragma once

#include "puzzle.h"

#include <sstream>
#include <iostream>

class PuzzleSolver
{
public:
	PuzzleSolver(Puzzle puzzle)
		: m_puzzle(puzzle)
		, m_log(&std::cout)
	{
	}

	bool Solve();

	std::ostream& log()
	{
		return *m_log;
	}

	void SetLog(std::ostream& log)
	{
		m_log = &log;
	}

private:
	void MarkerRule(const std::vector<int32_t> &values, Puzzle::GridView &grid_view);
	void ZeroValueRule(const std::vector<int32_t>& values, Puzzle::GridView& grid_view);

	Puzzle m_puzzle;

	std::ostream* m_log;
};

