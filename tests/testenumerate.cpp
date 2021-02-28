//
// Created by Simon Farre: 2021-02-25.
// Github: https://github.com/theIDinside
//
#include <cxutils/enumerate.hpp>

#include <iostream>
#include <string>
#include <vector>

struct KVP {
  int k;
  int v;
};

int main() {
  std::vector<int> ints{3, 2, 1};

  // enumerating over ints
  for (auto &&[index, el] : cxutils::enumerate(ints)) {
    std::cout << "index: " << index << ", value: " << el << std::endl;
  }

  auto m = cxutils::enumerate(ints);
  std::cout << std::endl;
  std::vector<std::string> strings{"hello", "world", "goodbye", "world"};

  for (auto &&[index, el] : cxutils::enumerate(strings)) {
    std::cout << "index: " << index << ", value: " << el << std::endl;
  }
}