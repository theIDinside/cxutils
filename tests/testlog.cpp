//
// Created by Simon Farre: 2021-02-28.
// Github: https://github.com/theIDinside
//

#include <cxutils/logging.hpp>

#include <vector>
#include <iostream>
#include <numeric>

int sum_vector(const std::vector<int>& v) {
  return std::accumulate(v.begin(), v.end(), 0, [](auto acc, auto el) { return acc + el; });
}

namespace cl = cxutils::log;

int main() {
  std::vector<int> ints{};
  ints.resize(1024*1024);

  // some hackery required for templated functions. Which is unfortunate.
  using fnType = decltype(std::fill<std::vector<int>::iterator, int>);
  // For me, this is one of the bad things about generics in C++.
  // Why can't it just figure this shit out for me?:
  auto fill_time = cl::time_and_log<cl::usec, fnType>(std::fill, ints.begin(), ints.end(), -1);
  std::cout << "filling the vector took " << fill_time << "ns" << std::endl;
  auto sum_time = cl::time_and_log(sum_vector, ints);
  std::cout << "summing the vector took " << sum_time << "ns" << std::endl;

}