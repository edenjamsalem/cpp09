#include "../includes/PmergeMe.hpp"

int safe_strtoi(const char* str)
{
    std::istringstream iss(str);
    int value;
    char leftover;

    if (!(iss >> value) || value < 0) {
        throw std::invalid_argument("Invalid input: contains non-positive integer.");
    }
    if (iss >> leftover) {
        throw std::invalid_argument("Invalid input: contains extra characters.");
    }
    return value;
}
