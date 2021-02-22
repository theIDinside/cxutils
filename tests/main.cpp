// NB!!!!! This is _not_ how you would include these files normally.
#include "../include/cxutils/enumerate.hpp"
#include "../include/cxutils/zip.hpp"

#include <algorithm>
#include <array>
#include <cctype>
#include <iostream>
#include <ranges>
#include <vector>
#include <tuple>
#include <type_traits>
#include <initializer_list>


/// Notice that using my utils, when iterating you shall not write for(auto&
/// ...), as this will be a compiler error Because in C++ we have no (as far as
/// I know, and I am *certainly* no expert) decent way of saying (someRefType1,
/// someRefType2) meaning, for(auto& ...) will try to get a reference to the
/// pair we return from zip, holding the references to the container elements.
/// So this instantly becomes counter-intuitive if one is writing C++, since we
/// are used to say "for(auto& ...)" if we want to mutate the elements Now, we
/// should instead write for(auto ...) or for(auto&& ). Notice that for(auto...)
/// shouldn't make any copies of the elements, so it's all reference based. I
/// hope. Lol

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

  std::vector<int> ints{3, 2, 1};

  // enumerating over ints
  for (auto &&[index, el] : cxutils::enumerate(ints)) {
    std::cout << "index: " << index << ", value: " << el << std::endl;
  }
  // output:
  // index: 0, value: 3
  // index: 1, value: 2
  // index: 2, value: 1

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
  // output:
  // 1, 3.1
  // 2, 2.2
  // 3, 1.3

  // mutating the containers A and B:
  for (auto &&[a, b] : cxutils::zip_two(A, B)) {
    a = std::toupper(a);
    b = std::toupper(b);
  }
  // after uppercase
  for (auto &&[a, b] : cxutils::zip_two(A, B)) {
    std::cout << a << b;
  }
  // output: "HELLO, WORLD!!"
  std::cout << std::endl;
  {
    std::vector<int> A2{1, 2, 3};
    std::vector<int> B2{4, 5, 6};

    for (auto &&[a, b] : cxutils::zip_two(A2, B2)) {
      a += b;
      b = a;
    }
    for (auto &&[a, b] : cxutils::zip_two(A2, B2)) {
      std::cout << a << ", " << b << std::endl;
    }
    auto f = cxutils::zip_two(A2, B2);
    std::cout << std::endl;
  }

  {
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
}