// NB!!!!! This is _not_ how you would include these files normally.
#include <iostream>
#include <vector>
#include <string>

#include <cxutils/transform.hpp>

struct KVP {
  size_t key;
  int value;
};

int main() {

  std::vector<int> ints_vec{1,2,3,4,5};
  auto str_ints = cxutils::transform(ints_vec, [](auto i) {
    return "Str-result: " + std::to_string(i);
  });
  std::cout << "integer values transformed to strings:\n";
  for(const auto& si : str_ints) {
    std::cout << si << std::endl;
  }
  static int ID = 0;

  auto kvps = cxutils::transform(ints_vec, [](const auto& el) {
    return KVP{std::hash<int>{}(ID++), el };
  });

  for(const auto& [key, value] : kvps) {
    std::cout << "k: " << key << " - v: " << value << std::endl;
  }

}