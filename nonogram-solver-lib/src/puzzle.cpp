#include "puzzle.h"

#include <sstream>
#include <string>
#include <fstream>
#include <algorithm>


Puzzle Puzzle::LoadFromFile(const std::string& path)
{
	Puzzle puzzle;

    std::ifstream puzzle_file(path);

    auto get_non_empty_line = [](std::istream& stream, std::string& line)
    {
        for (;;)
        {
            if (!std::getline(stream, line))
            {
                return false;
            }

            if (std::all_of(line.begin(), line.end(), isspace))
            {
                continue;
            }

            return true;
        }
    };

    // read dimensions
    {
        std::string line;

        if (!get_non_empty_line(puzzle_file, line))
        {
            throw std::runtime_error("Invalid input");
        }

        size_t column_count{ 0 }, row_count{ 0 };

        std::stringstream sstream(line);
        sstream >> row_count >> column_count;

        puzzle.m_rows.resize(row_count);
        puzzle.m_columns.resize(column_count);
    }

    auto read_values = [&](std::vector<std::vector<int32_t>>& values)
    {
        for (size_t i = 0; i < values.size(); i++)
        {
            auto& sub_values = values[i];

            std::string line;

            if (!get_non_empty_line(puzzle_file, line))
            {
                throw std::runtime_error("Invalid input");
            }

            std::stringstream sstream(line);

            int32_t value{};
            while (sstream >> value)
            {
                sub_values.push_back(value);
            }

        }
    };

    read_values(puzzle.m_rows);
    read_values(puzzle.m_columns);

	return puzzle;
}

