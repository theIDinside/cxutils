//
// Created by Simon Farre: 2021-02-25.
// Github: https://github.com/theIDinside
//
#include <array>
#include <vector>
#include <list>
#include <iostream>
#include <string>
#include <cxutils/zip.hpp>

int main() {
  std::array<char, 8> A{'h', 'l', 'o', ' ', 'o',
                        'l', '!', '_'}; // last _ char to show that zip(..) ends
  // as soon as one container runs out
  std::array<char, 7> B{'e', 'l', ',', 'w', 'r', 'd', '!'};

  const std::array<char, 8> cA{'h', 'l', 'o', ' ', 'o',
                        'l', '!', '_'}; // last _ char to show that zip(..) ends
  // as soon as one container runs out
  const std::array<char, 7> cB{'e', 'l', ',', 'w', 'r', 'd', '!'};


  // zip-iterating over A and B
  for (auto [a, b] : cxutils::zip(A, B)) {
    std::cout << a << b;
    a = static_cast<char>(std::toupper(a));
    b = static_cast<char>(std::toupper(b));
  }



  for (auto [a, b] : cxutils::czip(A, B)) {
    std::cout << a << b;
  }

  std::cout << "iterating after mutation of hello world:\n";
  for (const auto [a, b] : cxutils::zip(A, B)) {
    std::cout << a << b;
  }

  std::cout << std::endl;


  for (auto [a, b] : cxutils::zip(cA, cB)) {
    std::cout << a << b;
  }

  // output: "hello, world!!"
  std::cout << std::endl;

  std::array<char, 6> A2{'h', 'l', 'o', ' ', 'o', 'l'};
  std::array<char, 7> B2{
      'e', 'l', ',', 'w',
      'r', 'd', '!'}; // last ! char to show that zip(..) ends as soon as one
  // container runs out of elements

  for (auto [a, b] : cxutils::zip(A2, B2)) {
    std::cout << a << b;
  }
  // output: "hello, world"
  std::cout << std::endl;
  
  std::vector<int> i{11, 22, 33};
  std::vector<int> ca{1, 2, 3};
  std::list<int> cb{4, 5, 6, 7};
  std::array cc{7, 8, 9, 10, 11};

  std::cout << "using my variadic template version, statically dispatching to ZipTwo and ZipThree...:" << std::endl;
  for(auto [a, b, c] : cxutils::zip(ca, cb, cc)) {
    std::cout << "a: " << a << ", b: " << b << ", c: " << c << "\n";
  }


  std::cout << "using my fully variadic template version:" << std::endl;
  for(auto [a, b, c, d] : cxutils::zip(ca, cb, cc, i)) {
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

  const std::vector<int> const_ca{1, 2, 3};
  const std::list<int> const_cb{4, 5, 6, 7};
  const std::array const_cc{7, 8, 9, 10, 11};

  for(const auto [a, b, c] : cxutils::zip(const_ca, const_cb, const_cc)) {
    std::cout << "const a: " << a
              << ", const b: " << b
              << ", const c: " << c
              << std::endl;
  }



  std::vector<int> c1{1,2,3};
  std::vector<int> c2{11,22,33};
  std::vector<int> c3{111,222,333};

  for(const auto [a, b, c] : cxutils::zip(c1,c2,c3)) {
    std::cout << "a: " << a << ", b: " << b << ", c: " << c << "\n";
  }
}