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

template <Iterable... Its> class Zip {
private:
  std::tuple<IteratorOf<Its>...> it_begins;
  std::tuple<IteratorOf<Its>...> it_ends;

  using Zipped = std::tuple<ElementReferenceOf<Its>...>;

  constexpr static auto size_ = sizeof...(Its);

public:
  using range_difference_t = std::size_t;
  constexpr Zip(
      Its &&...its) // : it_begins(its.begin()...), it_ends(its.end()...)
      noexcept {
    ((std::cout << (its.size()) << ","), ...);
    std::cout << std::endl;
    init_begin_iters((its.begin())...);
    init_end_iters((its.end())...);
  }
  constexpr auto begin() const { return *this; }
  constexpr auto end() const { return *this; }

  template <typename... Iterators>
  constexpr auto init_begin_iters(Iterators &&...iters) {
#ifdef DEBUG
    std::cout << "begin Iters inited: " << sizeof...(iters) << std::endl;
    ((std::cout << (*iters) << ","), ...);
#endif
    it_begins = std::make_tuple(std::forward<Iterators>(iters)...);
  }

  template <typename... Iterators>
  constexpr auto init_end_iters(Iterators &&...iters) {
#ifdef DEBUG
    std::cout << "end Iters inited: " << sizeof...(iters) << std::endl;
#endif
    it_ends = std::make_tuple(std::forward<Iterators>(iters)...);
  }

  constexpr bool operator!=(const Zip<Its...> &) const {
    if constexpr (size_ == 2) {
      auto [a_b, b_b] = it_begins;
      auto [a_e, b_e] = it_ends;
      return a_b != a_e && b_b != b_e;
    } else if constexpr (size_ == 3) {
      auto [a_b, b_b, c_b] = it_begins;
      auto [a_e, b_e, c_e] = it_ends;
      return a_b != a_e && b_b != b_e && c_b != c_e;
    } else if constexpr (size_ == 4) {
      auto [a_b, b_b, c_b, d_b] = it_begins;
      auto [a_e, b_e, c_e, d_e] = it_ends;
      return a_b != a_e && b_b != b_e && c_b != c_e && d_b != d_e;
    } else if constexpr (size_ == 5) {
      auto [a_b, b_b, c_b, d_b, e_b] = it_begins;
      auto [a_e, b_e, c_e, d_e, e_e] = it_ends;
      return a_b != a_e && b_b != b_e && c_b != c_e && d_b != d_e && e_b != e_e;
    } else if constexpr (size_ == 6) {
      auto [a_b, b_b, c_b, d_b, e_b, f_b] = it_begins;
      auto [a_e, b_e, c_e, d_e, e_e, f_e] = it_ends;
      return a_b != a_e && b_b != b_e && c_b != c_e && d_b != d_e &&
             e_b != e_e && f_b != f_e;
    } else {
      static_assert(false, "The ziperator currently only supports 4 iterators. "
                           "Because I am hacking this together");
    }
  }

  constexpr Zip &operator++() {
    if constexpr (size_ == 2) {
      auto &[a, b] = it_begins;
      a++;
      b++;
    } else if constexpr (size_ == 3) {
      auto &[a, b, c] = it_begins;
      a++;
      b++;
      c++;
    } else if constexpr (size_ == 4) {
      auto &[a, b, c, d] = it_begins;
      a++;
      b++;
      c++;
      d++;
    } else if constexpr (size_ == 5) {
      auto &[a, b, c, d, e] = it_begins;
      a++;
      b++;
      c++;
      d++;
      e++;
    } else if constexpr (size_ == 6) {
      auto &[a, b, c, d, e, f] = it_begins;
      a++;
      b++;
      c++;
      d++;
      e++;
      f++;
    } else {
      static_assert(false, "The ziperator currently only supports 4 iterators. "
                           "Because I am hacking this together");
    }
    return *this;
  }

  constexpr auto operator*() const -> Zipped {
    if constexpr (size_ == 2) {
      auto &[a, b] = it_begins;
      return {*a, *b};
    } else if constexpr (size_ == 3) {
      auto [a, b, c] = it_begins;
      return {*a, *b, *c};
    } else if constexpr (size_ == 4) {
      auto [a, b, c, d] = it_begins;
      return {*a, *b, *c, *d};
    } else if constexpr (size_ == 5) {
      auto [a, b, c, d, e] = it_begins;
      return {*a, *b, *c, *d, *e};
    } else if constexpr (size_ == 6) {
      auto [a, b, c, d, e, f] = it_begins;
      return {*a, *b, *c, *d, *e, *f};
    } else {
      static_assert(
          false,
          "The ziperator currently only supports 6 iterators. Live with it");
    }
  }

  constexpr auto size() const { return size_; }
};

template <Iterable... Its> constexpr auto zip(Its &&...its) {
  return Zip<Its...>{std::forward<Its>(its)...};
}

} // namespace cxutils
