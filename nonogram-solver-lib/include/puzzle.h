#pragma once

#include <vector>
#include <string>
#include <stdexcept>

class Puzzle
{
public:
	enum class ViewType
	{
		Row = 0,
		Column
	};

	enum class FieldState
	{
		Unknown = 0,
		Marked,
		Empty
	};

	class GridView
	{
	public:
		GridView(Puzzle* puzzle, ViewType type, size_t id, bool reversed)
			: m_puzzle(puzzle)
			, m_type(type)
			, m_id(id)
			, m_reversed(reversed)
		{
		}

		FieldState at(size_t id)
		{
			return (*this)[id];
		}

		void set(size_t id, FieldState state)
		{
			auto prev_value = (*this)[id];

			bool ok = (prev_value == FieldState::Unknown) || (prev_value == state);
			if (!ok)
			{
				throw std::runtime_error("Change field state");
			}

			(*this)[id] = state;
		}

		size_t size() const
		{
			if (m_type == ViewType::Row)
			{
				return m_puzzle->m_columns.size();
			}
			else
			{
				return m_puzzle->m_rows.size();
			}
		}

	private:

		FieldState& operator[](size_t id)
		{
			auto actual_id = m_reversed ? (size() - id - 1) : id;

			if (m_type == ViewType::Row)
			{
				return m_puzzle->m_grid[m_id][actual_id];
			}
			else
			{
				return m_puzzle->m_grid[actual_id][m_id];
			}
		}

		Puzzle* m_puzzle{ nullptr };
		ViewType m_type{ ViewType::Row };
		size_t m_id{ 0 };
		bool m_reversed{ false };
	};


	class ValueView
	{
	public:
		ValueView(const Puzzle* puzzle, ViewType type, size_t id, bool reversed)
			: m_puzzle(puzzle)
			, m_type(type)
			, m_id(id)
			, m_reversed( reversed )
		{
		}

		auto size() const
		{
			if (m_type == ViewType::Row)
			{
				return m_puzzle->m_rows[m_id].size();
			}
			else
			{
				return m_puzzle->m_columns[m_id].size();
			}
		}

		auto operator[](size_t id) const
		{
			if (m_type == ViewType::Row)
			{
				const auto& row = m_puzzle->m_rows[m_id];

				if (!m_reversed)
				{
					return row[id];
				}
				else
				{
					return *(row.crbegin() + id);
				}
			}
			else
			{
				const auto& column = m_puzzle->m_columns[m_id];

				if (!m_reversed)
				{
					return column[id];
				}
				else
				{
					return *(column.crbegin() + id);
				}
			}
		}

	private:
		const Puzzle* m_puzzle{ nullptr };
		ViewType m_type{ ViewType::Row };
		size_t m_id{ 0 };
		bool m_reversed{ false };
	};


	static Puzzle LoadFromFile(const std::string &path);

	bool Validate(std::string& issues);
	void Print(std::ostream &ostream);
	double GetCompletionRatio() const;

	size_t GetRowCount() const
	{
		return m_rows.size();
	}

	size_t GetColumnCount() const
	{
		return m_columns.size();
	}

	const ValueView GetRowValueView(size_t id, bool reversed) const
	{
		return ValueView(this, ViewType::Row, id, reversed);
	}

	const ValueView GetColumnValueView(size_t id, bool reversed) const
	{
		return ValueView(this, ViewType::Column, id, reversed);
	}

	GridView GetRowView(size_t id, bool reversed)
	{
		return GridView(this, ViewType::Row, id, reversed);
	}

	GridView GetColumnView(size_t id, bool reversed)
	{
		return GridView(this, ViewType::Column, id, reversed);
	}

	static bool IsGridEqual(const Puzzle& p1, const Puzzle& p2);

private:
	std::vector<std::vector<int32_t>> m_rows;
	std::vector<std::vector<int32_t>> m_columns;

	std::vector<std::vector<FieldState>> m_grid;
};


#define DEBUG_GRIDVIEW(VALUES, GRIDVIEW)             \
	std::vector<int32_t> gridview_values;            \
	std::vector<Puzzle::FieldState> gridview_states; \
	for (size_t i = 0; i < VALUES.size(); i++)       \
	{                                                \
		gridview_values.push_back(VALUES[i]);        \
	}                                                \
	for (size_t i = 0; i < GRIDVIEW.size(); i++)     \
	{                                                \
		gridview_states.push_back(GRIDVIEW.at(i));   \
	}

