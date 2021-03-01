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

  for (auto [a, b] : cxutils::zip_two(A2, B2)) {
    std::cout << a << b;
  }
  // output: "hello, world"
  std::cout << std::endl;
  std::vector<int> i{11, 22, 33};
  std::vector<double> d{3.1, 2.2, 1.3};

  std::vector<int> ca{1, 2, 3};
  std::vector<int> cb{4, 5, 6, 7};
  std::vector<int> cc{7, 8, 9, 10, 11};


  for(auto&& [a, b, c] : cxutils::zip_three(ca, cb, cc)) {
    std::cout << "a: " << a << ", b: " << b << ", c: " << c << "\n";
    a *= 10;
    b *= 20;
    c *= 30;
  }

  std::cout << "using my variadic template version, statically dispatching to ZipTwo and ZipThree...:" << std::endl;
  for(auto&& [a, b, c] : cxutils::zip(ca, cb, cc)) {
    std::cout << "a: " << a << ", b: " << b << ", c: " << c << "\n";
  }


  std::cout << "using my fully variadic template version:" << std::endl;
  for(auto&& [a, b, c, d] : cxutils::zip(ca, cb, cc, i)) {
    std::cout << "a: " << a
              << ", b: " << b
              << ", c: " << c
              << ", d: " << d
        << "\n";
    a += b;
    b += c;
    c += d;
  }

  std::cout << "after mutation. d is the only non-mutated element:\n";
  for(auto [a, b, c, d] : cxutils::zip(ca, cb, cc, i)) {
    std::cout << "a: " << a << ", b: " << b << ", c: " << c << ", d: " << d << "\n";
  }


}