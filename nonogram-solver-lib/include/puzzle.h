#pragma once

#include <vector>
#include <string>

class Puzzle
{
public:
	static Puzzle LoadFromFile(const std::string &path);

private:
	std::vector<std::vector<int32_t>> m_rows;
	std::vector<std::vector<int32_t>> m_columns;
};

