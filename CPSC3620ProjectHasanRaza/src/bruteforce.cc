// Hasan Raza
// CPSC 3620 Brute Force Closest Point

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <filesystem>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <cmath>
#include "../include/shared.h"
#include "../include/bruteforce.h"

bool accepted = false;

void closestPairBrute(int N)
{
    double minDist = 30000; // The minimum distance is initialized to be higher than any possible distance

    double minXfirstpoint = 0; // X coordinate of the first point in in the closest pair
    double minYfirstpoint = 0; // Y coordinate of the first point in in the closest pair

    double minXsecondpoint = 0; // X coordinate of the second point in in the closest pair
    double minYsecondpoint = 0; // Y coordinate of the second point in in the closest pair

    std::vector<int> xpoints; // Vector to hold the Xpoints
    std::vector<int> ypoints; // Vector to hold the Ypoints

    std::string file = selectTextFile(N);
    std::ifstream inFile(file);

    if (!inFile)
    {
        std::cerr << "Error: Could not open file " << file << " for reading." << std::endl;
        return;
    }

    int x, y; // Variables to store the coordinates
    std::string line;

    // Read each line from the file
    while (std::getline(inFile, line))
    {
        std::stringstream ss(line); // Use stringstream to parse the line

        // Extract x and y values from the line
        ss >> x >> y;

        // If the extraction is successful, print the values
        if (ss)
        {
            xpoints.push_back(x);
            ypoints.push_back(y);
        }
        else
        {
            std::cerr << "Error: Failed to extract points from line: " << line << std::endl;
        }
    }

    // Brute Force Algorithm Begins
    std::cout << std::endl;
    std::cout <<"--------------------------------- " << std::endl;
    std::cout << "Beginning Brute Force with " << N << " points..." << std::endl;
    auto start = std::chrono::high_resolution_clock::now(); // Start clock
    for (int i = 0; i < N; i++)
    {
        for (int j = i + 1; j < N; j++)
        {
            // Calculates distance between the two selected points using pythagorean theorem.
            double xdist = xpoints.at(i) - xpoints.at(j);
            double ydist = ypoints.at(i) - ypoints.at(j);

            double distance = std::sqrt(std::pow((xdist), 2) + std::pow((ydist), 2));

            // If a new minimum distance is found, overide minDist,
            // and the points associated with this new closest pair.

            if (distance < minDist)
            {
                minDist = distance;

                minXfirstpoint = xpoints.at(i);
                minYfirstpoint = ypoints.at(i);

                minXsecondpoint = xpoints.at(j);
                minYsecondpoint = ypoints.at(j);
            }
        }
    }
    auto end = std::chrono::high_resolution_clock::now(); // End clock as soon as loop has concluded
    std::cout << "Ending Brute Force.... " << std::endl;
    std::cout << std::endl;
    // Brute Force Algorithm Ends

    std::chrono::duration<double> duration = end - start; // Calculates duration

    // Prints the time taken, the closest pair, and the distance between them.

    std::cout << "The closest pair is points (" << minXfirstpoint << ", " << minYfirstpoint << ") and ";
    std::cout << "(" << minXsecondpoint << ", " << minYsecondpoint << ")" << std::endl;
    std::cout << "The minimum distance is " << minDist << std::endl;
    std::cout << "Time taken to find the closest pair: " << duration.count() << " seconds" << std::endl;
    inFile.close();
}

void bruteForceValidInputCheck() // Asks the user for N and checks if it is valid before initiating bruteforce algorithm, 3 tries maximum
{
    std::cout << std::endl; // Blank line before output
    std::cout << "Please enter the N you would like to use. Please note that only the accepted Ns are viable." << std::endl;
    std::cout << "The accepted values are: " << "100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 1500, 2000, 2500, 3000, 4000, 5000, 6000, 7000, 8000, 9000, and 100000" << std::endl;
    std::cout << "Input 0 if you would like to run brute force on all values of points." << std::endl;

    int N;
    std::cout << std::endl;
    std::cout << "Enter N... ";
    std::cout << std::endl;
    std::cin >> N;

    accepted = false;
    int tries = 0;

    while (accepted == false)
    {
        for (int i = 0; i < 21; i++)
        {
            if (N == acceptedNs[i] || N == 0)
            {

                std::cout << "Inputted N is accepted." << std::endl;
                std::cout << std::endl;
                accepted = true;
                break;
            }
        }
        if (accepted == false && tries < 3)
        {
            std::cout << "Inputted N is NOT accepted, N is not a permitted value." << std::endl;
            std::cout << "Please try again." << 3 - tries << " remaining. " << std::endl;
            std::cout << std::endl;
            std::cout << "Enter N... ";
            tries++;
            std::cin >> N;
        }
        else if (tries == 3)
        {
            accepted = true;
            std::cout << "Inputted N is NOT accepted, N is not a permitted value." << std::endl;
            break;
        }
    }
    if (tries < 3 && N != 0)
    {
        closestPairBrute(N);
    }
    else if (tries < 3 && N == 0)       // Runs brute force on all accepted values of N
    {
        for (int y = 0; y < Nsize; y++)
        {
            closestPairBrute(acceptedNs[y]);
        }
    }
    else
    {
        std::cout << "You have failed to input an allowed value within the set amount of attempts." << std::endl;
        std::cout << "The program is now ending. Goodbye. " << std::endl;
    }

    std::cout << std::endl;
    std::cout << "***ENDING PROGRAM***" << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
}