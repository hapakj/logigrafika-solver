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

    puzzle.m_grid.resize(puzzle.m_rows.size());
    for (auto& row : puzzle.m_grid)
    {
        row.resize(puzzle.m_columns.size());
        std::fill(row.begin(), row.end(), FieldState::Unknown);
    }

	return puzzle;
}


void Puzzle::Print(std::ostream &ostream)
{
#if WIN32
    const std::string marked = { char(219), char(219), char(0) };
#else
    const std::string marked = "##";
#endif
    const std::string unknown = "  ";
    const std::string empty = "..";

    constexpr bool extended = false;

    const auto print_horintal_border = [&]()
    {
        ostream << "+--";
        for (size_t i = 0; i < m_columns.size() - 1; i++)
        {
            ostream << (extended ? "---" : "--");
        }
        ostream << '+' << std::endl;
    };

    const auto print_row = [&](const std::vector<FieldState> &row)
    {
        ostream << "|";

        for (const auto v : row)
        {
            switch (v)
            {
            case FieldState::Empty:
                ostream << empty;
                break;

            case FieldState::Marked:
                ostream << marked;
                break;

            case FieldState::Unknown:
                ostream << unknown;
                break;
            };

            ostream << (extended ? "|" : "");
        }

        ostream << (extended ? "" : "|") << std::endl;
    };

    print_horintal_border();
    for (const auto& row : m_grid)
    {
        print_row(row);
        if (extended)
        {
            print_horintal_border();
        }
    }
    if (!extended)
    {
        print_horintal_border();
    }
}


bool Puzzle::Validate(std::string& issues)
{
    bool valid = true;
    std::stringstream issues_stream;

    auto values_valid = [&](std::vector<int32_t> values, uint32_t grid_size)
    {
        uint32_t s{ 0 };
        for (auto v : values)
        {
            s += v;
        }

        s += uint32_t(values.size()) - 1;

        return s <= grid_size;
    };

    for (size_t i = 0; i < m_rows.size(); i++)
    {
        if (!values_valid(m_rows[i], uint32_t(m_columns.size())))
        {
            issues_stream << "Row " << (i + 1) << " is invalid" << std::endl;
            valid = false;
        }
    }

    for (size_t i = 0; i < m_columns.size(); i++)
    {
        if (!values_valid(m_columns[i], uint32_t(m_rows.size())))
        {
            issues_stream << "Column " << (i + 1) << " is invalid" << std::endl;
            valid = false;
        }
    }

    issues = issues_stream.str();
    return valid;
}


bool Puzzle::IsGridEqual(const Puzzle& p1, const Puzzle& p2)
{
    if (p1.m_grid.size() != p2.m_grid.size())
    {
        return false;
    }

    for (size_t i = 0; i < p1.m_grid.size(); i++)
    {
        auto r1 = p1.m_grid[i];
        auto r2 = p2.m_grid[i];

        if (r1.size() != r2.size())
        {
            return false;
        }

        for (size_t j = 0; j < r1.size(); j++)
        {
            if (r1[j] != r2[j])
            {
                return false;
            }
        }
    }

    return true;
}


double Puzzle::GetCompletionRatio() const
{
    size_t filled_field_count = 0;
    for (const auto& r : m_grid)
    {
        for (const auto& f : r)
        {
            if (f != FieldState::Unknown)
            {
                filled_field_count++;
            }
        }
    }

    return double(filled_field_count) / (double(m_rows.size()) * double(m_columns.size()));
}

