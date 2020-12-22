#include "puzzle.h"
#include "puzzle_solver.h"

#include <filesystem>
#include <iostream>
#include <fstream>


int main(int argc, char** argv)
{
    std::string working_directory = ".";
    if (argc > 1)
    {
        working_directory = argv[1];
    }

    std::vector<std::filesystem::path> puzzle_pathes;
    for (const auto& dir_it : std::filesystem::directory_iterator(working_directory))
    {
        if (!dir_it.is_directory())
        {
            continue;
        }

        puzzle_pathes.push_back(dir_it.path());
    }

    for (const auto& path : puzzle_pathes)
    {
        std::cout << "Load puzzle: " << path.string() << std::endl;

        auto puzzle = Puzzle::LoadFromFile((path / "puzzle.in").string());

        std::string issues;
        if (!puzzle.Validate(issues))
        {
            std::cout << "Puzzle invalid: " << std::endl << issues << std::endl;
            continue;
        }

        PuzzleSolver solver(puzzle);

        std::ofstream log(path / "log.txt");
        solver.SetLog(log);

        solver.Solve();

        log.close();

        std::cout << std::endl;
    }

    return 0;
}

