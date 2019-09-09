#include <string>
#include <algorithm>
#include <iostream>
#include <iterator>


std::string &ltrim(std::string &s)
{
  s.erase(s.begin(), 
    std::find_if(s.begin(), s.end(), 
      [](int c) { 
        return !std::isspace(c); 
      } 
    )
  );
  return s;
}

std::string &rtrim(std::string &s)
{
  s.erase(
    std::find_if(s.rbegin(), s.rend(), 
      [](int c) { 
        return !std::isspace(c); 
      } 
    ).base(), s.end()
  );
  return s;
}

std::string &trim(std::string &s) 
{
  ltrim(s);
  rtrim(s);
  return s;
}

class int_to_dutch
{
  public:

    std::string translate_upto_hundred_(const unsigned long long hundreds) const {
      if (hundreds < 20) {
        return unique_numbers_[hundreds];
      }
      else {
        if (hundreds % 10 == 0) {
          return tens_[hundreds / 10];
        }
        else {
          return unique_numbers_[hundreds % 10] + "en" + tens_[hundreds / 10];
        }
      }
    }

    std::string translate_from_hundred_up_(const unsigned long long thousands) const {
      std::string return_str = "";

      if (thousands < 100) {
        return_str = translate_upto_hundred_(thousands);
      } 
      else {
        return_str =  "honderd" + (translate_upto_hundred_(thousands % 100));

        if (thousands >= 200) {
          return_str = unique_numbers_[thousands / 100] + return_str;
        }
      }

      return return_str;
    }

    std::string dutch(const long long number) const {
      bool is_negative = false;
      unsigned long long input = number;
      std::string words = "";

      if (number < 0) {
        is_negative = true;
        input = -number;
      }

      int chunk_count = 0;
      while (input > 0) {
        std::cout << "<" << (input % 1000) << ">" << std::endl;
        if (input % 1000 != 0) { // Only callout the sub-powers on non-round numbers
          if ((chunk_count == 1) && ((input % 1000) < 2)) { // Don't say: eenduizend
            words = powers_[chunk_count] + words;
          }
          else {
            words = translate_from_hundred_up_(input % 1000) + powers_[chunk_count] + words;
          }
        }
        input /= 1000;
        ++chunk_count;
      }

      if (is_negative) {
        words = "minus " + words;
      }

      return trim(words);
    }

  private:

    static constexpr int N_UNIQUE_NUMBERS = 20;
    std::string unique_numbers_[N_UNIQUE_NUMBERS] = {
      "", "een", "twee", "drie", "vier", "vijf", "zes", "zeven", "acht", "negen", "tien", "elf", 
      "twaalf", "dertien", "veertien", "vijftien", "zestien", "zeventien", "achtien", "negentien"
    };

    static constexpr int N_TENS = 10;
    std::string tens_[N_TENS] = {
      "", "", "twintig", "dertig", "veertig", "vijftig", "zestig", "zeventig", "tachtig", "negentig"
    };

    static constexpr int N_POWERS = 4;
    std::string powers_[N_TENS] = {
      "", "duizend ", "miljoen ", "miljard "
    };
};

int main()
{
  int_to_dutch i2nl;
  long long number;

  for (;;) {
    std::cin.clear();
    std::cout << "Voer alstublieft een getal in: ";
    std::cin >> number;
    std::cout << i2nl.dutch(number) << std::endl;
  }

}
