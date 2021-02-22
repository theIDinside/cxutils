#pragma once
#include "concepts.hpp"

namespace cxutils {

template <Iterable I> using CleanType = std::decay_t<I>;

template <Iterable ItA, Iterable ItB, Iterable ItC> class ZipThree {
private:
  using IteratorA = typename CleanType<ItA>::iterator;
  using IteratorB = typename CleanType<ItB>::iterator;
  using IteratorC = typename CleanType<ItC>::iterator;

  using DerefA = typename CleanType<ItA>::reference;
  using DerefB = typename CleanType<ItB>::reference;
  using DerefC = typename CleanType<ItC>::reference;

  IteratorA iter_a;
  IteratorB iter_b;
  IteratorC iter_c;

  IteratorA iter_a_end;
  IteratorB iter_b_end;
  IteratorC iter_c_end;

  struct Zipped {
    DerefA a;
    DerefB b;
    DerefC c;
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

// used to make for instance std::array<char, 4>& -> std::array<char, 4>

template <Iterable ItA, Iterable ItB> class ZipTwo {
private:
  using IteratorA = typename CleanType<ItA>::iterator;
  using IteratorB = typename CleanType<ItB>::iterator;

  using DerefA = typename CleanType<ItA>::reference;
  using DerefB = typename CleanType<ItB>::reference;

  IteratorA iter_a;
  IteratorB iter_b;

  IteratorA iter_a_end;
  IteratorB iter_b_end;

  struct Zipped {
    DerefA a;
    DerefB b;
  };

public:
  using range_difference_t = std::size_t;
  constexpr ZipTwo(ItA itA, ItB itB) noexcept
      : iter_a(itA.begin()), iter_b(itB.begin()), iter_a_end(itA.end()),
        iter_b_end(itB.end()) {}
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
};

template <Iterable ItA, Iterable ItB>
constexpr auto zip_two(ItA &&iterA, ItB &&iterB) {
  return ZipTwo<ItA, ItB>{iterA, iterB};
}

} // namespace cxutils
