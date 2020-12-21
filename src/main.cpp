#include "puzzle.h"

#include <filesystem>
#include <iostream>


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

        puzzle_pathes.push_back(dir_it.path() / "puzzle.in");
    }

    for (const auto& path : puzzle_pathes)
    {
        std::cout << "Load puzzle: " << path.string() << std::endl;
        Puzzle::LoadFromFile(path.string());
    }

    return 0;
}

