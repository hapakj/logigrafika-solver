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
		GridView(Puzzle* puzzle, ViewType type, size_t id)
			: m_puzzle(puzzle)
			, m_type(type)
			, m_id(id)
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
			if (m_type == ViewType::Row)
			{
				return m_puzzle->m_grid[m_id][id];
			}
			else
			{
				return m_puzzle->m_grid[id][m_id];
			}
		}

		Puzzle* m_puzzle{ nullptr };
		ViewType m_type;
		size_t m_id;
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

	const std::vector<int32_t>& GetRowValues(size_t id) const
	{
		return m_rows[id];
	}

	const std::vector<int32_t>& GetColumnValues(size_t id) const
	{
		return m_columns[id];
	}

	GridView GetRowView(size_t id)
	{
		return GridView(this, ViewType::Row, id);
	}

	GridView GetColumnView(size_t id)
	{
		return GridView(this, ViewType::Column, id);
	}

	static bool IsGridEqual(const Puzzle& p1, const Puzzle& p2);

private:
	std::vector<std::vector<int32_t>> m_rows;
	std::vector<std::vector<int32_t>> m_columns;

	std::vector<std::vector<FieldState>> m_grid;
};

