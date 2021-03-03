#pragma once
#include "concepts.hpp"

namespace cxutils {

/// The fully variadic template version of Zip, taking anywhere between [2<=6]
/// containers to iterate over.
template <Iterable... Its> class Zip {
private:
  std::tuple<IteratorOf<Its>...> it_begins;
  std::tuple<IteratorOf<Its>...> it_ends;

  using Zipped = std::tuple<ElementReferenceOf<Its>...>;

  constexpr static auto size_ = sizeof...(Its);

public:
  constexpr explicit Zip(Its &&...its) noexcept : it_begins{std::make_tuple(its.begin()...)}, it_ends{std::make_tuple(its.end()...)} {
    static_assert(size() >= 2 && size() <= 6,
                  "Zip only supports 2 to 6 containers to iterate over. This "
                  "is arbitrary. But so is life. So f##k you.");
  }
  constexpr auto begin() const { return *this; }
  constexpr auto end() const { return *this; }

  /// Constexpr magic. This boils away. Or at least I think it does.
  /// Perhaps? Yes. Yes? Yes. Maybe.
  constexpr bool operator!=(const Zip<Its...> &) const {
    static_assert(size() >= 2 && size() <= 6,
                  "The ziperator currently only supports [2<=6] iterators. "
                  "Because I am hacking this together");
    if constexpr (size_ == 2) {
      const auto &[a_b, b_b] = it_begins;
      const auto &[a_e, b_e] = it_ends;
      return a_b != a_e && b_b != b_e;
    } else if constexpr (size_ == 3) {
      const auto &[a_b, b_b, c_b] = it_begins;
      const auto &[a_e, b_e, c_e] = it_ends;
      return a_b != a_e && b_b != b_e && c_b != c_e;
    } else if constexpr (size_ == 4) {
      const auto &[a_b, b_b, c_b, d_b] = it_begins;
      const auto &[a_e, b_e, c_e, d_e] = it_ends;
      return a_b != a_e && b_b != b_e && c_b != c_e && d_b != d_e;
    } else if constexpr (size_ == 5) {
      const auto &[a_b, b_b, c_b, d_b, e_b] = it_begins;
      const auto &[a_e, b_e, c_e, d_e, e_e] = it_ends;
      return a_b != a_e && b_b != b_e && c_b != c_e && d_b != d_e && e_b != e_e;
    } else if constexpr (size_ == 6) {
      const auto &[a_b, b_b, c_b, d_b, e_b, f_b] = it_begins;
      const auto &[a_e, b_e, c_e, d_e, e_e, f_e] = it_ends;
      return a_b != a_e && b_b != b_e && c_b != c_e && d_b != d_e &&
             e_b != e_e && f_b != f_e;
    }
  }

  constexpr Zip &operator++() {
    static_assert(size() >= 2 && size() <= 6,
                  "The ziperator currently only supports [2<=6] iterators. "
                  "Because I am hacking this together");
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
    }
    return *this;
  }

  constexpr auto operator*() const -> Zipped {
    static_assert(size() >= 2 && size() <= 6,
                  "The ziperator currently only supports [2<=6] container "
                  "iterators. Live with it");
    if constexpr (size_ == 2) {
      auto &[a, b] = it_begins;
      return {*a, *b};
    } else if constexpr (size_ == 3) {
      auto &[a, b, c] = it_begins;
      return {*a, *b, *c};
    } else if constexpr (size_ == 4) {
      auto &[a, b, c, d] = it_begins;
      return {*a, *b, *c, *d};
    } else if constexpr (size_ == 5) {
      auto &[a, b, c, d, e] = it_begins;
      return {*a, *b, *c, *d, *e};
    } else if constexpr (size_ == 6) {
      auto &[a, b, c, d, e, f] = it_begins;
      return {*a, *b, *c, *d, *e, *f};
    }
  }

  static constexpr auto size() { return size_; }
};

/// Interface via which we use the Zip-iterator.
template <Iterable... Its> constexpr auto zip(Its &&...its) {
  return Zip<Its...>{std::forward<Its>(its)...};
}

} // namespace cxutils
