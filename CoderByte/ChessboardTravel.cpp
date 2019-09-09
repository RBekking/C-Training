#include <iostream>
#include <string>
#include <set>
#include <chrono>
#include <algorithm>
#include <memory>
#include "utility.h"

std::pair<uint32_t, uint32_t> get_deltas(std::string coordinates)
{
  size_t left_parenthesis = 0;
  size_t right_parenthesis = 0;

  left_parenthesis = coordinates.find_first_of("(", right_parenthesis);
  right_parenthesis = coordinates.find_first_of(")", left_parenthesis);
  auto startpoint = coordinates.substr(left_parenthesis + 1, (right_parenthesis - left_parenthesis) - 1);

  left_parenthesis = coordinates.find_first_of("(", right_parenthesis);
  right_parenthesis = coordinates.find_first_of(")", left_parenthesis);
  auto endpoint = coordinates.substr(left_parenthesis + 1, (right_parenthesis - left_parenthesis) - 1);

  auto seperator = startpoint.find_first_not_of(utility::NUMERALS);
  auto start_x = startpoint.substr(0, seperator);
  auto start_y = startpoint.substr(seperator);

  seperator = endpoint.find_first_not_of(utility::NUMERALS);
  auto end_x = endpoint.substr(0, seperator);
  auto end_y = endpoint.substr(seperator);

  return std::pair<int, int>( abs(std::stoi(end_x) - std::stoi(start_x)), abs(std::stoi(end_y) - std::stoi(start_y)) );
}

class table 
{
  public:
    table(const uint32_t width, const uint32_t height);
    virtual ~table();
    void display() const;
    uint32_t element(const uint32_t x, const uint32_t y) const;
  private:
    uint32_t width_;
    uint32_t height_;
    uint32_t** array_2d_;
};

table::table(const uint32_t width, const uint32_t height) : width_(width), height_(height) 
{
  array_2d_ = new uint32_t*[width];
  for (uint32_t x = 0; x < width; ++x) {
    array_2d_[x] = new uint32_t[height];
    array_2d_[x][0] = 1;
  }
  for (uint32_t y = 0; y < height; ++y) {
    array_2d_[0][y] = 1;
  }

  for (uint32_t x = 1; x < width; ++x) {
    for (uint32_t y = 1; y < height; ++y) {
      array_2d_[x][y] = array_2d_[x - 1][y] + array_2d_[x][y - 1];
    }
  }
}

table::~table()
{
  for (int i = 0; i < width_; ++i) {
    delete [] array_2d_[i];
  }
  delete [] array_2d_;
}

void table::display() const
{
  for (int y = height_-1; y >=0 ; --y) {
    for (int x = 0; x < width_; ++x) {
      std::cout << array_2d_[x][y] << " ";
    }
    std::cout << std::endl;
  }
}

uint32_t table::element(const uint32_t x, const uint32_t y) const
{
  uint32_t value = 0;

  if ((x < width_) && (y < height_)) {
    value = array_2d_[x][y];
  }

  return value;
}

std::string Challenge(std::string coordinates)
{
  std::string paths = "";
  auto d = get_deltas(coordinates);
  int steps = d.first + d.second;

  WHATS( d.first, d.second)
  if (d.first > d.second)  {
    d.first ^= d.second ^= d.first ^= d.second;
  }

  table board_table(d.first + 1, d.second + 1);
  board_table.display();

  if (1 == d.first) { // 2 by x is easy
    paths = std::to_string(steps);
  }
  else {
    paths = std::to_string(board_table.element(d.first, d.second));
  }

  return paths;
}

int main() 
{
  std::string input;
  std::getline(std::cin, input);
  auto result = Challenge(input);
  std::cout << "output: " << result << std::endl;
  return 0;
} 


  