#pragma once
#include "concepts.hpp"

namespace cxutils {

template <Iterable ItA, Iterable ItB, Iterable ItC> class ZipThree {
private:
  IteratorOf<ItA> iter_a;
  IteratorOf<ItB> iter_b;
  IteratorOf<ItC> iter_c;

  IteratorOf<ItA> iter_a_end;
  IteratorOf<ItB> iter_b_end;
  IteratorOf<ItC> iter_c_end;

  struct Zipped {
    ElementReferenceOf<ItA> a;
    ElementReferenceOf<ItB> b;
    ElementReferenceOf<ItC> c;
  };

public:
  constexpr ZipThree(ItA itA, ItB itB, ItC itC) noexcept
      : iter_a(itA.begin()), iter_b(itB.begin()), iter_c(itC.begin()),
        iter_a_end(itA.end()), iter_b_end(itB.end()), iter_c_end(itC.end()) {}
  constexpr auto begin() const { return *this; }
  constexpr auto end() const { return *this; }

  constexpr bool operator!=(const ZipThree &) const {
    return iter_a != iter_a_end && iter_b != iter_b_end && iter_c != iter_c_end;
  }

  constexpr ZipThree &operator++() {
    ++iter_a;
    ++iter_b;
    ++iter_c;
    return *this;
  }

  constexpr auto operator*() const -> Zipped {
    return {*iter_a, *iter_b, *iter_c};
  }
};

template <Iterable ItA, Iterable ItB, Iterable ItC>
constexpr auto zip_three(ItA &&iterA, ItB &&iterB, ItC &&iterC) {
  return ZipThree<ItA, ItB, ItC>{iterA, iterB, iterC};
}

template <Iterable ItA, Iterable ItB, Iterable ItC>
constexpr auto zip_three(const ItA &iterA, const ItB &iterB, const ItC &iterC) {
  return ZipThree<ItA, ItB, ItC>{iterA, iterB, iterC};
}

// used to make for instance std::array<char, 4>& -> std::array<char, 4>

template <Iterable ItA, Iterable ItB> class ZipTwo {
private:
  IteratorOf<ItA> iter_a;
  IteratorOf<ItB> iter_b;

  IteratorOf<ItA> iter_a_end;
  IteratorOf<ItB> iter_b_end;

  struct Zipped {
    ElementReferenceOf<ItA> a;
    ElementReferenceOf<ItB> b;
  };
  std::size_t size_;

public:
  using range_difference_t = std::size_t;
  constexpr ZipTwo(ItA itA, ItB itB) noexcept
      : iter_a(itA.begin()), iter_b(itB.begin()), iter_a_end(itA.end()),
        iter_b_end(itB.end()), size_(std::min(itA.size(), itB.size())) {}
  constexpr auto begin() const { return *this; }
  constexpr auto end() const { return *this; }

  constexpr bool operator!=(const ZipTwo &) const {
    return iter_a != iter_a_end && iter_b != iter_b_end;
  }

  constexpr ZipTwo &operator++() {
    ++iter_a;
    ++iter_b;
    return *this;
  }

  constexpr auto operator*() const -> Zipped { return {*iter_a, *iter_b}; }
  constexpr auto size() const { return size_; }
};

template <Iterable ItA, Iterable ItB>
constexpr auto zip_two(ItA &&iterA, ItB &&iterB) {
  return ZipTwo<ItA, ItB>{iterA, iterB};
}

template <Iterable ItA, Iterable ItB>
constexpr auto zip_two(const ItA &iterA, const ItB &iterB) {
  return ZipTwo<ItA, ItB>{iterA, iterB};
}

} // namespace cxutils
