#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

#include "utility.h"

constexpr uint32_t SEARCH_SPACE = 9999;
constexpr uint32_t KAPREKARS_CONSTANT = 6174;
constexpr uint32_t NUM_DIGITS = 4;
constexpr uint32_t MIN_INPUT = 1;
constexpr uint32_t MAX_INPUT = 9999;

uint32_t getNext(const uint32_t& num) 
{
  constexpr uint32_t DECIMAL = 10;
  uint32_t n = num;
  std::vector<uint32_t> v {};

  for (uint32_t i = 0; i < NUM_DIGITS; ++i) {
    v.push_back(n % DECIMAL);
    n /= DECIMAL;
  }
  
  std::sort(v.begin(), v.end());
  int min = 0;
  int max = 0;
  
  for (uint32_t i = 0; i < NUM_DIGITS; ++i) {
    min *= DECIMAL;
    max *= DECIMAL;
    min += v[i];
    max += v[(NUM_DIGITS - 1) - i];
  }
  n = max - min;
  
  return n;
}

std::string Challenge1(const uint32_t num) 
{
  uint32_t n = num;
  uint32_t iteration_count = 0;

  while ((KAPREKARS_CONSTANT != n) && n) {
    n = getNext(n);
    ++iteration_count;
  }

  return std::to_string(iteration_count);
}

int subtract(const uint32_t a, const uint32_t b)
{
  return (a > b ? a - b : b - a);
}

std::string pad(const std::string& s)
{
  std::string padded_string = s;
  padded_string.resize(NUM_DIGITS);
  for (auto& c : padded_string) {
    if ('\0' == c)
      c = '0';
  }

  return padded_string;
}

std::string Challenge2(int num) 
{
  // code goes here
  int ascending_num;
  int descending_num;
  int iteration_count = 0;
  bool invalid_num = false;

  do {
    std::string ascending = std::to_string(num);
    ascending = pad(ascending);
    std::sort(ascending.begin(), ascending.end());
    std::string descending = ascending;
    std::reverse(descending.begin(), descending.end());
    ascending_num = std::stoi(ascending);
    descending_num = std::stoi(descending);
    if (ascending_num == descending_num) {
      invalid_num = true;
    }
    ++iteration_count;
  } while (
      ascending_num && (!invalid_num) &&
      (KAPREKARS_CONSTANT != (num = subtract(ascending_num, descending_num))) 
  );

  return std::to_string(iteration_count);
}

int main() 
{   
  std::cout << "This program calculates what input to Kaprekars\n"
            << "algorithm leads to the most iterations before\n"
            << "ariving at Kaprekars constant: " << KAPREKARS_CONSTANT << std::endl;

  std::string result_str{};
  uint32_t result_num = 0;
  uint32_t result_input = 0;
  uint32_t highest_iteration = 0;

  MEASURE_INIT
  
  std::cout << "\n* Searching input with highest iteration count using vectors: " << std::endl;
  MEASURE_START(SEARCH_SPACE)
  for (uint32_t i = 0; i < SEARCH_SPACE; ++i) {
    result_str = Challenge1(i);
    result_num = std::stoi(result_str);
    if (highest_iteration < result_num) {
      highest_iteration = result_num;
      result_input = i;
    }
  }
  MEASURE_END
  std::cout << "Input with highest iteration count: " << result_input << " with\n" 
            << highest_iteration << " iterations" << std::endl;

  std::cout << "\n* Searching input with highest iteration count using strings: " << std::endl;
  MEASURE_START(SEARCH_SPACE)
  for (uint32_t i = 0; i < SEARCH_SPACE; ++i) {
    result_str = Challenge2(i);
    result_num = std::stoi(result_str);
    if (highest_iteration < result_num) {
      highest_iteration = result_num;
      result_input = i;
    }
  }
  MEASURE_END
  std::cout << "Input with highest iteration count: " << result_input << " with\n" 
            << highest_iteration << " iterations" << std::endl;
  
  return EXIT_SUCCESS;
} 


  