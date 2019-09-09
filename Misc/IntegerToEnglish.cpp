#include <string>
#include <iostream>
#include <math.h>

class number_to_english 
{
  public:
    void set_number(const unsigned long long number) {
      number_ = number;
    }

    std::string english() const {
      if (number_ >= 1000000000000) {
        return "I can't pronounce that";
      }

      return convert_to_english_(number_);
    }

  private:

    unsigned long long number_ = 0;

    static constexpr unsigned int N_UNIQUES = 20;
    std::string unique_numbers_[N_UNIQUES] {
      "", "one", "two", "three", "four","five",
      "six", "seven", "eight", "nine", "ten",
      "eleven", "twelve", "thirteen", "fourteen", "fifteen",
      "sixteen", "seventeen", "eighteen", "nineteen"
    };

    static constexpr unsigned int N_TENTHS = 10;
    std::string tens_[N_TENTHS] {
      "", "", "twenty", "thirty", "fourty", "fifty", 
      "sixty", "seventy", "eighty", "ninety"
    };

    static constexpr unsigned int N_POWERS_TEN = 4;
    std::string powers_[N_POWERS_TEN] {
      "", "thousand", "million", "billion"
    };

    std::string pad_if_not_empty_(std::string sentence) const {
      if (sentence == "") {
        return "";
      }  
      return " " + sentence;
    }

    std::string translate_hundreds_(const unsigned long long number) const {
      if (number < 20) {
        return unique_numbers_[number];
      }
      unsigned int tens = number / 10;
      unsigned int ones = number % 10;
      return tens_[tens] + unique_numbers_[ones];
    }

    std::string translate_thousands_(const unsigned long long in_number) const {
      long long number = in_number; 

      if (number < 100) {
        return translate_hundreds_(number);
      }
      else {
        return unique_numbers_[number / 100] + " hundred" + pad_if_not_empty_(translate_hundreds_(number % 100));
      }      
    }

    std::string convert_to_english_(const long long in_number) const {
      long long number = in_number;
      std::string return_str = "";
      bool is_negative = false;

      if (number < 0) {
        is_negative = true;
        number = -number;
      }

      int chunk_count = 0;
      while (number > 0) {
        if (number % 1000 != 0) {
          return_str = translate_thousands_(number % 1000) + pad_if_not_empty_(powers_[chunk_count] + pad_if_not_empty_(return_str));
        }
        number /= 1000;
        ++chunk_count;
      }

      if (return_str == "") {
        return_str = "zero";
      } 

      if (is_negative) {
        return_str = "minus " + return_str;
      }

      return return_str;
    }
};

int main()
{
  number_to_english n2e;
  long long number;
  for (;;) {
    std::cout << "please enter a number: ";
    std::cin.clear();
    std::cin >> number;
    n2e.set_number(number);
    std::cout << n2e.english() << std::endl;
  }

}
