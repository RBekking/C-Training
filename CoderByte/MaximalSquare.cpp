#include <iostream>
#include <string>
#include <algorithm>
#include <stdio.h>
#include "utility.h"

std::string MaximalSquare(const std::string str_array[], const size_t size)
{
  const uint32_t WIDTH = str_array[0].length(); 

  uint32_t largest = 0;
  uint32_t d = 0;
  uint32_t smallest = 0;

  for (uint32_t y = 0; y < size; ++y) {
    for (uint32_t x = 0; x < WIDTH; ++x) {
      smallest = (size - y) < (WIDTH - x) ? size - y : WIDTH - x;
      for (d = 0; d < smallest; ++d) {
        for (uint32_t i = 0; i <= d; ++i) {
          WHATS(x, y)
          if (('1' != str_array[y + d - i][x + d]) || ('1' != str_array[y + d][x + d - i])) {
            goto next;
          }
        }
      }
      next: largest = (largest < d ? d : largest);
    }
  }
  return std::to_string(largest * largest);
}

using namespace std;
int main() { 
  std::string A[] =  {"10100", 
                      "10111", 
                      "11111", 
                      "10010"}; 
 
  std::cout << MaximalSquare(A, arraysize(A)) << std::endl;
  return 0;
} 


  
