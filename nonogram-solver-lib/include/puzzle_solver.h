#pragma once

#include "puzzle.h"

#include <sstream>
#include <iostream>
#include <optional>

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
	void MarkerRule(const Puzzle::ValueView &values, Puzzle::GridView &grid_view);
	void ZeroValueRule(const Puzzle::ValueView &values, Puzzle::GridView& grid_view);
	void CloseSideRule(const Puzzle::ValueView &values, Puzzle::GridView& grid_view);

	Puzzle m_puzzle;

	std::ostream* m_log;

	std::optional<size_t> m_processed_row_id, m_processed_column_id;
	uint32_t m_iteration_count{ 0 };

	bool IsProcessed(uint32_t iteration_count, std::optional<size_t> row_id, std::optional<size_t> column_id)
	{
		iteration_count--;
		if (row_id)
		{
			(*row_id)--;
		}
		if (column_id)
		{
			(*column_id)--;
		}

		return (m_iteration_count == iteration_count) && (m_processed_row_id == row_id) && (m_processed_column_id == column_id);
	}

	void BrakeAt(uint32_t iteration_count, std::optional<size_t> row_id, std::optional<size_t> column_id)
	{
		if (IsProcessed(iteration_count, row_id, column_id))
		{
			std::cout << "We should brake" << std::endl;
		}
	}
};

