#ifndef DIVIDECONQUER_H
#define DIVIDECONQUER_H

#include <string>
#include <vector>

// List of accepted N values

extern bool acceptedDiv;

// Function declarations

void sortAndDivide(int N);
void closestPairDivAndConquer();
void divideConquerValidInputCheck();
void quickSort(std::vector<int>& sortedVector, std::vector<int>& unsortedVector,int low, int high);
int partition(std::vector<int>& sortedVector, std::vector<int>& unsortedVector,int low, int high);

#endif // DIVIDECONQUER_H