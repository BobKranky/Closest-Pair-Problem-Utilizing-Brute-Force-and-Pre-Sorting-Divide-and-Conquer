// Hasan Raza
// CPSC 3620 Project
// This file holds shared code needed for both the brute force and divide and conquer

#include <iostream>
#include <vector>
#include <filesystem>
#include "../include/shared.h"

// Valid values of N
const std::vector<int> acceptedNs{100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 1500, 2000, 2500, 3000,
                                   4000, 5000, 6000, 7000, 8000, 9000, 100000};

int Nsize = acceptedNs.size();

std::string selectTextFile(int N)   // Selects the correct text file based on N
{
    std::filesystem::path base_path = std::filesystem::current_path() / "textfiles";
    std::filesystem::path filename = base_path / ("output" + std::to_string(N) + ".txt");
    return filename.string();
}
