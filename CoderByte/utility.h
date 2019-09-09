#ifndef UTILITY_H_
#define UTILITY_H_

#include <iostream>
#include <math.h>
#include <chrono>
#include <string>

namespace utility
{
extern const std::string NUMERALS;
extern const std::string LETTERS;
extern const std::string ALPHANUMERICS;

// For watching variables
#define WHAT(x) std::cout << #x << " is " << x << std::endl;
#define WHATS(x, y) std::cout << #x << "," << #y << " are " << x << "," << y << std::endl;

// return most significant digit FAST
inline int num_digits(uint64_t N) 
{
  return floor(log10(N)) + 1;
}

// safe array size (if you pass a pointer it will not compile)
#define arraysize(array) (sizeof(array) / sizeof(*array))

// To measure the run time of a piece of code (you might want to loop 10 000 times over the code to
// get significant delays and divide the result by that same number)
uint64_t micros();
uint64_t millis();
#define MEASURE_INIT uint64_t utility_measure_start_;\
                     uint64_t utility_measure_elapsed_;\
                     uint64_t utility_measure_divider_;
#define MEASURE_START(x) DO_MEASURE_START( x) 
#define DO_MEASURE_START( x) utility_measure_start_ = utility::micros();\
                             utility_measure_divider_ = static_cast<uint64_t>(x);
#define MEASURE_END utility_measure_elapsed_ = utility::micros() - utility_measure_start_;\
                    std::cout << "Elapsed time: " << utility_measure_elapsed_ / utility_measure_divider_ << " usec\n";
}

#endif /* #ifndef UTILITY_H_ */
