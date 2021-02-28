//
// Created by Simon Farre: 2021-02-25.
// Github: https://github.com/theIDinside
//
#include <array>
#include <vector>
#include <iostream>
#include <string>

#include <cxutils/zip.hpp>


int main() {
  std::array<char, 8> A{'h', 'l', 'o', ' ', 'o',
                        'l', '!', '_'}; // last _ char to show that zip(..) ends
  // as soon as one container runs out
  std::array<char, 7> B{'e', 'l', ',', 'w', 'r', 'd', '!'};

  // zip-iterating over A and B
  for (auto &&[a, b] : cxutils::zip_two(A, B)) {
    std::cout << a << b;
  }
  // output: "hello, world!!"
  std::cout << std::endl;

  std::array<char, 6> A2{'h', 'l', 'o', ' ', 'o', 'l'};
  std::array<char, 7> B2{
      'e', 'l', ',', 'w',
      'r', 'd', '!'}; // last ! char to show that zip(..) ends as soon as one
  // container runs out of elements

  for (auto &&[a, b] : cxutils::zip_two(A2, B2)) {
    std::cout << a << b;
  }
  // output: "hello, world"
  std::cout << std::endl;
  std::vector<int> i{1, 2, 3};
  std::vector<double> d{3.1, 2.2, 1.3};

  // zip-iterating over two containers with different "Container::value_type"s
  for (auto &&[a, b] : cxutils::zip_two(i, d)) {
    std::cout << a << ", " << b << std::endl;
  }

  // mutating the containers A and B:
  for (auto &&[a, b] : cxutils::zip_two(A, B)) {
    a = std::toupper(a);
    b = std::toupper(b);
  }
  // after uppercase
  for (auto &&[a, b] : cxutils::zip_two(A, B)) {
    std::cout << a << b;
  }

  std::vector<int> ca{1, 2, 3};
  std::vector<int> cb{4, 5, 6};
  std::vector<int> cc{7, 8, 9};

  for(auto&& [a, b, c] : cxutils::zip_three(ca, cb, cc)) {
    std::cout << "a: " << a << ", b: " << b << ", c: " << c << "\n";
    a *= 10;
    b *= 20;
    c *= 30;
  }
  std::cout << "after mutation:\n";
  for(auto&& [a, b, c] : cxutils::zip_three(ca, cb, cc)) {
    std::cout << "a: " << a << ", b: " << b << ", c: " << c << "\n";
  }
}