// Hasan Raza
// CPSC 3620 Project Controller

#include "../include/bruteforce.h"
#include "../include/divideconquer.h"
#include "../include/shared.h"
#include <iostream>

int main()
{
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "***BEGINNING PROGRAM***" << std::endl;
    std::cout << std::endl;
    std::cout << "Greetings. Would you like to run the brute force solution or the divide and conquer solution?" << std::endl;

    std::string input;
    int tries = 0;
    bool accepted = false;

    while (accepted == false)
    {
        std::cout << "Enter input, accepted values are 'Brute' and 'Divide', inputting anything else will end the program." << std::endl;
        std::cout << std::endl;
        std::cout << "Enter input... ";
        std::cin >> input;

        if (input == "Brute" || input == "brute" || input == "1" || input == "b")
        {
                accepted = true;
                std::cout << std::endl;
                std::cout << "Running ClosestPointBruteForce Program..." << std::endl;
                bruteForceValidInputCheck(); // Function to validate input and then call brute force
                break;
            }
            else if (input == "Divide" || input == "divide" || input == "2" || input == "div") // Accepts different input
            {
                accepted = true;
                std::cout << std::endl;
                std::cout << "Running ClosestPointDivAndConquer Program..." << std::endl;
                divideConquerValidInputCheck(); // Function to validate input and then call divide and conquer
                break;
            }
            else if (tries == 3) // Ends program if too many failed tries have been detected.
            {
                std::cout << "Inputted string is NOT accepted, " << input << " is not a permitted entry." << std::endl;
                std::cout << "You have ran out of tries. Ending Program." << std::endl;
                std::cout << std::endl;
                std::cout << "***ENDING PROGRAM***" << std::endl;
                std::cout << std::endl;
                std::cout << std::endl;
                break;
            }
            else // Increases tries by 1
            {
                std::cout << "Inputted string is NOT accepted, " << input << " is not a permitted entry." << std::endl;
                std::cout << "You have " << 3 - tries << " tries remaining. ";
                std::cout << "Please try again." << std::endl;
                tries++;
            }
        }
        return 0;
    }