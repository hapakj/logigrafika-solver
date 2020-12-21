#pragma once

#include <vector>
#include <string>

class Puzzle
{
public:
	enum class FieldState
	{
		Unknown = 0,
		Marked,
		Empty
	};

	static Puzzle LoadFromFile(const std::string &path);

	bool Validate(std::string& issues);
	void Print(std::ostream &ostream);

private:
	std::vector<std::vector<int32_t>> m_rows;
	std::vector<std::vector<int32_t>> m_columns;

	std::vector<std::vector<FieldState>> m_grid;
};

