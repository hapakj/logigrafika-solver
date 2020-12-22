#include "puzzle_solver.h"

#include <iostream>
#include <functional>
#include <optional>
#include <iomanip>


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

	auto last_state = m_puzzle;

	uint32_t iteration_count = 0;

	for (;;)
	{
		std::cout << (iteration_count + 1) << ". iteration" << std::endl;

		apply_rule([&](auto values, auto gridview) { MarkerRule(values, gridview); });

		if (Puzzle::IsGridEqual(m_puzzle, last_state))
		{
			std::cout << "No change" << std::endl;
			break;
		}

		m_puzzle.Print(std::cout);

		last_state = m_puzzle;
		iteration_count++;
	}

	std::cout << std::setprecision(2) << std::fixed << "Completion ratio: " << m_puzzle.GetCompletionRatio() * 100.0 << "%" << std::endl;

	return true;
}


void PuzzleSolver::MarkerRule(const std::vector<int32_t>& values, Puzzle::GridView& grid_view)
{
	struct SectionRange
	{
		size_t begin{ 0 }, end{ 0 };
	};

	std::vector<SectionRange> section_ranges;

	{
		std::optional<SectionRange> section;

		for (size_t id = 0; id < grid_view.size(); id++)
		{
			if ((grid_view[id] != Puzzle::FieldState::Empty) && !section)
			{
				section.emplace();
				section->begin = id;
			}

			const size_t next_id = id + 1;

			if (section && ((next_id == grid_view.size()) || (grid_view[next_id] == Puzzle::FieldState::Empty))) 
			{
				section->end = next_id;
				section_ranges.push_back(*section);
				section.reset();
			}
		}
	}

	for (const auto section_range : section_ranges)
	{
		struct SectionView
		{
		public:
			SectionView(Puzzle::GridView& grid_view, const SectionRange& section_range)
				: m_grid_view(grid_view)
				, m_section_range(section_range)
			{
			}

			auto size()
			{
				return m_section_range.end - m_section_range.begin;
			}

			auto& operator[](size_t id)
			{
				return m_grid_view[m_section_range.begin + id];
			}

		private:
			Puzzle::GridView& m_grid_view;
			SectionRange m_section_range;
		};


		struct SectionValueView
		{
		public:
			SectionValueView(const std::vector<int32_t>& values, size_t start, size_t end)
				: m_values(values)
				, m_start(start)
				, m_end(end)
			{
			}

			auto begin()
			{
				return m_values.begin() + m_start;
			}

			auto end()
			{
				return m_values.begin() + m_end;
			}

			auto size()
			{
				return m_end - m_start;
			}

			auto& operator[](size_t id)
			{
				return m_values[m_start + id];
			}

		private:
			const std::vector<int32_t>& m_values;
			size_t m_start{ 0 }, m_end{ 0 };
		};


		size_t start_value_id{ 0 };
		{
			size_t s = 0;
			size_t i = 0;
			for (; i < values.size(); i++)
			{
				s += values[i] + 1;
				if (s > section_range.begin)
				{
					break;
				}
			}
			start_value_id = i;
		}


		size_t end_value_id{ 0 };
		{
			size_t s = grid_view.size();
			size_t i = values.size() - 1;
			for (; i > 0; i--)
			{
				s -= values[i] + 1;
				if (s < section_range.end)
				{
					break;
				}
			}
			end_value_id = i + 1;
		}

		if (end_value_id < start_value_id)
		{
			continue;
		}

		SectionView section_view(grid_view, section_range);
		SectionValueView section_values(values, start_value_id, end_value_id);

		for (size_t i = 0; i < section_values.size(); i++)
		{
			const auto section_value = section_values[i];

			uint32_t left_padding{ 0 };
			for (size_t j = 0; j < i; j++)
			{
				left_padding += section_values[j] + 1;
			}

			uint32_t right_padding{ 0 };
			for (size_t j = i + 1; j < section_values.size(); j++)
			{
				right_padding += section_values[j] + 1;
			}

			auto right_end = left_padding + section_value;
			auto left_begin = section_view.size() - (right_padding + section_value);

			for (size_t j = left_begin; j < right_end; j++)
			{
				section_view[j] = Puzzle::FieldState::Marked;
			}
		}
	}
}

