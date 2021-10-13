#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <stdexcept>
#include <stdio.h>
#include <string>
#include <cmath>
#include <sstream>
#include <iomanip>

class functions
{
public:
    double round_up(double value, int decimal_places);
    std::string to_format(const int number);
    std::string ReplaceAll(std::string str, const std::string& from, const std::string& to);
};

#endif // FUNCTIONS_H
