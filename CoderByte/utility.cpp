#include "utility.h"

namespace utility 
{
const std::string NUMERALS = "0123456789";
const std::string LETTERS = "abcdefghijklmopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
const std::string ALPHANUMERICS = "abcdefghijklmopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

uint64_t micros() 
{
  return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::
      now().time_since_epoch()).count();
}

uint64_t millis() 
{
  return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::
      now().time_since_epoch()).count();
}

} /* namespace utility */
