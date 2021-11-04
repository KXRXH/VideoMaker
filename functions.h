#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

#include <cmath>
#include <cstdio>
#include <iostream>
#include <string>

/**
 * @brief Returns the two-digit representation of a number.
 *
 * @param number
 * @return std::string
 */
inline std::string to_format(const int number) {
  char ch[3];
  if (number < 10) {
    std::sprintf(ch, "0%d", number);
  } else {
    std::sprintf(ch, "%d", number);
  }
  std::string str_out(ch);
  return str_out;
}
//-------------------------------------------------------------------------------------------------------//
/**
 * @brief Return rounded double object.
 * 
 * @param value 
 * @param decimal_places 
 * @return double 
 */
inline double round_up(double value, const int decimal_places) {
  const double multiplier = std::pow(10.0, decimal_places);
  return std::ceil(value * multiplier) / multiplier;
}
//-------------------------------------------------------------------------------------------------------//
/**
 * @brief Returns std::string in which all <from> elements replaced with <to> elements.
 * 
 * @param str 
 * @param from 
 * @param to 
 * @return std::string 
 */
inline std::string ReplaceAll(std::string str, const std::string &from,
                       const std::string &to) {
  size_t start_pos = 0;
  while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
    str.replace(start_pos, from.length(), to);
    start_pos +=
        to.length(); // Handles case where 'to' is a substring of 'from'
  }
  return str;
}
//-------------------------------------------------------------------------------------------------------//
/**
 * @brief Formatting <struct Duration> members [hour, min, sec] to [24, 60, 60] format respectively.
 * 
 * @tparam T 
 * @param structure 
 */
template <typename T> void timeFormat(T &structure) {
  structure.min += structure.sec / 60;
  structure.sec %= 60;
  //--------------------------------//
  structure.hour += structure.min / 60;
  structure.min %= 60;
}

#endif // __FUNCTIONS_H__
