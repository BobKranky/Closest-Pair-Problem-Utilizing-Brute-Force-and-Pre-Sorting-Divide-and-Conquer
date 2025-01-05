// Hasan Raza
//CPSC 3620 Project Create output files.

#include <iostream>
#include <fstream>
#include <filesystem>
#include <stdio.h>  
#include <stdlib.h> 
#include "../include/shared.h"
#include "../include/create.h"

const std::vector<int> acceptedNs{100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 1500, 2000, 2500, 3000,
                                   4000, 5000, 6000, 7000, 8000, 9000, 100000};
int Nsize = acceptedNs.size();

void generateNPoints()
{
    for (int y = 0; y < Nsize; y++)
    {

        std::filesystem::path base_path = std::filesystem::current_path() / "textfiles";
        std::filesystem::path filename = base_path / ("output" + std::to_string(acceptedNs.at(y)) + ".txt");

        std::cout << "File will be saved to: " << filename << std::endl;

        // Seed the random number generator
        std::srand(std::time(NULL) + y);

        // Open the file for writing
        std::ofstream outFile(filename);

        if (!(outFile))
        {
            std::cerr << "Error: Could not open file " << filename << " for writing." << std::endl;
            return;
        }

        // Generate N random points
        for (int i = 0; i < acceptedNs.at(y); ++i)
        {
            // Generate random x and y values
            int x = (std::rand() % 20001) - 10000; // Random x coordinate (-10000 to 10000)
            int y = (std::rand() % 20001) - 10000; // Random y coordinate (-10000 to 10000)

            // Write the point to the file
            outFile << x << " " << y << "\n";
        }

        outFile.close();
        std::cout << "Successfully generated " << acceptedNs.at(y) << " points and saved to " << filename << std::endl;
    }
}

int main()
{
    generateNPoints();
}