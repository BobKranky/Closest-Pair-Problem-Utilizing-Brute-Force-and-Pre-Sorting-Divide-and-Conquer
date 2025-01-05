// Hasan Raza
// CPSC 3620 Project Divide and Conquer Closest Pair

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
#include "../include/divideconquer.h"

bool acceptedDiv = false;

double minDist = 30000; // The minimum distance is initialized to be higher than any possible distance

double minXfirstpoint = 0; // X coordinate of the first point in in the closest pair
double minYfirstpoint = 0; // Y coordinate of the first point in in the closest pair

double minXsecondpoint = 0; // X coordinate of the second point in in the closest pair
double minYsecondpoint = 0; // Y coordinate of the second point in in the closest pair

// This algorithm requires two sorted vectors of points. 
// The first vector, xpoints, and ypoints are sorted by the X coordinate while maintaining the intergrity of each point.
std::vector<int> xpoints;   // Holds the sorted X coordinates
std::vector<int> ypoints;   // Holds the unsorted Y coordinates


int low = 0;    // The low and high values, used in partitioning during quicksort
int high = 0;

double localX1;
double localY1;
double localX2;
double localY2;

struct Result // Structure to store the closest pair AND the distance between them.
{
    double minDist; // Minimum distance

    double x1;      // X value of first point in closest pair
    double y1;      // Y value of first point in closest pair

    double x2;      // X value of second point in closest pair
    double y2;      // Y value of second point in closest pair
};

int partition(std::vector<int> &sortingVector, std::vector<int> &unsortedVector, int low, int high)
{
    // Choose the pivot as the end value in the vector, during the first loop, high = N - 1
    int pivot = sortingVector[high];

    // Initialize index for the smaller element
    // This index (i) will mark the boundary between elements smaller than the pivot
    // and elements larger than or equal to the pivot
    int i = low - 1;

    // Iterate through sortingVector[low..high-1] to partition elements
    // Elements smaller than the pivot are moved to left
    for (int j = low; j <= high - 1; j++)
    {
        if (sortingVector[j] < pivot)  // Checks if element is smaller than pivot
        {
            i++;            
            // Swap the current element with the element at index i
            // Does this to both xpoint and y points to maintain coordinate integrity
            std::swap(sortingVector[i], sortingVector[j]);
            std::swap(unsortedVector[i], unsortedVector[j]);
        }
    }

    // Place the pivot element in its correct sorted position
    std::swap(sortingVector[i + 1], sortingVector[high]);
    std::swap(unsortedVector[i + 1], unsortedVector[high]);

    // Return the final index of the pivot
    return i + 1;
}

// The QuickSort function implementation to sort the points by either the X or the Y while maintaining point integrity.
void quickSort(std::vector<int> &sortingVector, std::vector<int> &unsortedVector, int low, int high)
{
    if (low < high)
    {
        int pi = partition(sortingVector, unsortedVector, low, high);
        quickSort(sortingVector, unsortedVector, low, pi - 1);  // Recursion calls for smaller elements
        quickSort(sortingVector, unsortedVector, pi + 1, high); // and greater or equals elements
    }
}

Result closestPairDivAndConquer(int low, int high)
{
    // Base case: If there are 3 or fewer points, use brute force
    if (high - low <= 3)
    {
        double localMinDist = 30000;
        for (int i = low; i < high; i++)
        {
            for (int j = i + 1; j < high && (xpoints[j] - ypoints[i]) < minDist; j++)
            {
                double xdist = xpoints.at(j) - xpoints.at(i);
                double ydist = ypoints.at(j) - ypoints.at(i);

                double distance = std::sqrt(std::pow((xdist), 2) + std::pow((ydist), 2));

                if (distance < localMinDist)
                {

                    localMinDist = distance;
                    localX1 = xpoints.at(i);
                    localY1 = ypoints.at(i);
                    localX2 = xpoints.at(j);
                    localY2 = ypoints.at(j);

                    if (localMinDist < minDist)
                    {
                        minDist = localMinDist;
                        localX1 = xpoints.at(i);
                        localY1 = ypoints.at(i);

                        localX2 = xpoints.at(j);
                        localY2 = ypoints.at(j);
                    }
                }
            }
        }
        return {localMinDist, localX1, localY1, localX2, localY2};
    }

    int mid = (low + high) / 2;
    int midX = xpoints[mid];

    Result leftResult = closestPairDivAndConquer(low, mid);
    Result rightResult = closestPairDivAndConquer(mid + 1, high);

    double minDist = std::min(leftResult.minDist, rightResult.minDist);
    // saves minDist to the smallest distance of the two halves of the problem

    // Saves the points that resulted in the smallest minDist
    double x1 = leftResult.minDist < rightResult.minDist ? leftResult.x1 : rightResult.x1;
    double y1 = leftResult.minDist < rightResult.minDist ? leftResult.y1 : rightResult.y1;
    double x2 = leftResult.minDist < rightResult.minDist ? leftResult.x2 : rightResult.x2;
    double y2 = leftResult.minDist < rightResult.minDist ? leftResult.y2 : rightResult.y2;

    std::vector<int> stripX;
    std::vector<int> stripY;

    for (int i = low; i <= high; i++)
    {
        if (std::abs(xpoints[i] - midX) < minDist)
        {
            stripX.push_back(xpoints[i]);
            stripY.push_back(ypoints[i]);
        }
    }

    int w = stripY.size();
    // Sort the strip points by their y-coordinates
    quickSort(stripY, stripX, 0, w - 1);

    // Check for points near the middle line that could have a smaller distance

    for (int i = 0; i < w; i++)
    {
        for (int j = i + 1; j < w && (stripY[j] - stripY[i]) < minDist; j++)
        {

            double xdist = stripX.at(j) - stripX.at(i);
            double ydist = stripY.at(j) - stripY.at(i);

            double dist = std::sqrt(std::pow((xdist), 2) + std::pow((ydist), 2));

            if (dist < minDist)
            {
                minDist = dist;
                x1 = stripX.at(i);
                y1 = stripY.at(i);
                x2 = stripX.at(j);
                y2 = stripY.at(j);
            }
        }
    }
    return {minDist, x1, y1, x2, y2};
}

void sortAndDivide(int N)
{
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

    inFile.close();

    high = N - 1;

    auto startsort = std::chrono::high_resolution_clock::now();     // Start clock
    quickSort(xpoints, ypoints, low, high);                         // Sorts the xpoints from smallest to largest, takes O(N log N)
    auto endsort = std::chrono::high_resolution_clock::now();       // End clock as soon as loop has concluded

    std::chrono::duration<double> durationsort = endsort - startsort;   // Calculates duration of quicksort
    
    std::cout << std::endl;
    std::cout <<"--------------------------------- " << std::endl;
    std::cout << "Beginning Divide and Conquer with " << N << " points..." << std::endl;

    auto start = std::chrono::high_resolution_clock::now(); // Start clock

    Result output = closestPairDivAndConquer(low, high);    // Saves the minimum distance and the closest pair to output

    auto end = std::chrono::high_resolution_clock::now();   // End clock as soon as loop has concluded

    std::chrono::duration<double> duration = end - start;   // Calculates duration

    double minDist = output.minDist;

    // Saves the closest pair points to the result of the left or right side
    double minXfirstpoint = output.x1;
    double minYfirstpoint = output.y1;
    double minXsecondpoint = output.x2;
    double minYsecondpoint = output.y2;

    std::cout << "Ending Divide and Conquer.... " << std::endl;
    std::cout << std::endl;

    std::cout << "The closest pair is points (" << minXfirstpoint << ", " << minYfirstpoint << ") and ";
    std::cout << "(" << minXsecondpoint << ", " << minYsecondpoint << ")" << std::endl;
    std::cout << "The minimum distance is " << minDist << std::endl;
    std::cout << "The time taken to sort the points using quicksort before divide and conquer: " << durationsort.count() << " seconds" << std::endl;
    std::cout << "Time taken to find the minimum distance using divide and conquer: " << duration.count() << " seconds" << std::endl;
    std::cout << "Total time taken using quicksort and divide and conquer: " << duration.count() + durationsort.count() << " seconds" << std::endl;

}

void divideConquerValidInputCheck()
{
    std::cout << std::endl; // Blank line before output
    std::cout << "Please enter the N you would like to use. Please note that only the accepted Ns are viable." << std::endl;
    std::cout << "The accepted values are: " << "100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 1500, 2000, 2500, 3000, 4000, 5000, 6000, 7000, 8000, 9000, and 100000" << std::endl;
    std::cout << "Input 0 if you would like to run divide and conquer on all values of points."<< std::endl;

    int N;
    std::cout << std::endl;
    std::cout << "Enter N... ";
    std::cout << std::endl;
    std::cin >> N;
    acceptedDiv = false;
    int tries = 0;

    while (acceptedDiv == false)
    {
        for (int i = 0; i < 21; i++)
        {
            if (N == acceptedNs[i] || N == 0)
            {

                std::cout << "Inputted N is accepted." << std::endl;
                std::cout << std::endl;
                acceptedDiv = true;
                break;
            }
        }
        if (acceptedDiv == false && tries < 3)
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
            acceptedDiv = true;
            std::cout << "Inputted N is NOT accepted, N is not a permitted value." << std::endl;
            break;
        }
    }
    if (tries < 3 && N != 0)
    {
        sortAndDivide(N);
    }
    else if (tries < 3 && N == 0)   // Runs divide and conquer on all accepted values of N
    {
        for(int y = 0; y < Nsize; y++)
        {
            sortAndDivide(acceptedNs[y]);

            // Clears points vectors
            xpoints.clear();
            ypoints.clear();

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
