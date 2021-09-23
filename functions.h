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
    double exec(const char* cmd);
    double round_up(double value, int decimal_places);
    std::string to_format(const int number);
};

#endif // FUNCTIONS_H
