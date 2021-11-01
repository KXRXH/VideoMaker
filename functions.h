#pragma once

#include <stdexcept>
#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <assert.h>
#include <iomanip>

// format number like: "2" -> "02"
std::string to_format(const int number)
{
    std::stringstream ss;
    ss << std::setw(2) << std::setfill('0') << number;
    return ss.str();
}
//-------------------------------------------------------------------------------------------------------//
// round up
double round_up(double value,  const int decimal_places)
{
    const double multiplier = std::pow(10.0, decimal_places);
    return std::ceil(value * multiplier) / multiplier;
}
//-------------------------------------------------------------------------------------------------------//
// replace funciton
std::string ReplaceAll(std::string str, const std::string& from, const std::string& to)
{
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
    }
    return str;
}
//-------------------------------------------------------------------------------------------------------//
// Formating time
template<typename T>
void timeFormat(T& structure)
{
    structure.min += structure.sec / 60;
    structure.sec %= 60;
//--------------------------------//
    structure.hour += structure.min / 60;
    structure.min %= 60;
}
