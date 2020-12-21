#include "puzzle_solver.h"

#include <iostream>
#include <functional>


bool PuzzleSolver::Solve()
{
	auto apply_rule = [&](auto&& rule)
	{
		for (size_t i = 0; i < m_puzzle.GetRowCount(); i++)
		{
			rule(m_puzzle.GetRowValues(i), m_puzzle.GetRowView(i));
		}

		for (size_t i = 0; i < m_puzzle.GetColumnCount(); i++)
		{
			rule(m_puzzle.GetColumnValues(i), m_puzzle.GetColumnView(i));
		}
	};

	apply_rule([&](auto values, auto gridview) { MarkerRule(values, gridview); });

	m_puzzle.Print(std::cout);

	return true;
}


void PuzzleSolver::MarkerRule(const std::vector<int32_t> &/*values*/, Puzzle::GridView &/*grid_view*/)
{
}

