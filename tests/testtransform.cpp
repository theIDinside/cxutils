// NB!!!!! This is _not_ how you would include these files normally.
#include <cxutils/transform.hpp>
#include <iostream>
#include <optional>
#include <string>
#include <vector>

struct KVP {
  size_t key;
  int value;
  std::string manager_name_copy;
};

int main() {
  using StrOpt = std::optional<std::string>;
  constexpr auto print_container = [](const auto &container,
                                      StrOpt &&begin_message, auto &&printFn,
                                      const auto sep) {
    if (begin_message) {
      std::cout << *begin_message << ":\n";
    }
    const auto size = container.size();
    size_t i = 0;
    for (const auto &e : container) {
      i++;
      printFn(e);
      if (i != size) [[likely]] {
        std::cout << sep;
      } else {
        std::cout << std::endl;
      }
    }
  };

  std::vector<int> ints_vec{1, 2, 3, 4, 5};

  auto int_ptrs =
      cxutils::transform(ints_vec, [](auto &elem) { return &elem; });

  print_container(
      int_ptrs, "References to data", [](auto e) { std::cout << *e; }, ", ");

  auto str_ints = cxutils::transform(
      ints_vec, [](auto i) { return "Str-result: " + std::to_string(i); });

  print_container(
      str_ints, "integer values transformed to strings",
      [](auto &e) { std::cout << e; }, "\n");

  static int ID = 0;

  std::string NameRef = "Foobar";

  auto kvps = cxutils::transform(ints_vec, [NameRef](const auto &el) {
    return KVP{.key = std::hash<int>{}(ID++),
               .value = el,
               .manager_name_copy = NameRef};
  });

  print_container(
      kvps, "key value pairs",
      [](auto &kvp) {
        const auto &[key, value, manager] = kvp;
        std::cout << "k: " << key << " - v: " << value;
      },
      "\n");
}