#pragma once
#include "concepts.hpp"

namespace cxutils {

class InvalidZip {};

/// An Iterator adapter over 2-6 containers. Mutation of elements are possible
template <Iterable... Its> class Zip {
private:
  std::tuple<IteratorOf<Its>...> it_begins;
  std::tuple<IteratorOf<Its>...> it_ends;

  using Zipped = std::tuple<ElementReferenceOf<Its>...>;

  constexpr static auto size_ = sizeof...(Its);

public:
  constexpr explicit Zip(Its && ...its) noexcept : it_begins{std::make_tuple(its.begin()...)}, it_ends{std::make_tuple(its.end()...)} {
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

/// A Const Iterator adapter over 2-6 containers
template <Iterable... Its> class ConstZip {
private:
  std::tuple<ConstIteratorOf<Its>...> it_begins;
  std::tuple<ConstIteratorOf<Its>...> it_ends;

  using Zipped = std::tuple<ConstElementReferenceOf<Its>...>;

  constexpr static auto size_ = sizeof...(Its);

public:
  constexpr explicit ConstZip(const Its &...its) noexcept
      : it_begins{std::make_tuple(its.cbegin()...)}, it_ends{std::make_tuple(
                                                         its.cend()...)} {
    static_assert(size() >= 2 && size() <= 6,
                  "ConstZip only supports 2 to 6 containers to iterate over. This "
                  "is arbitrary. But so is life. So f##k you.");
  }

  constexpr auto begin() const { return *this; }
  constexpr auto end() const { return *this; }

  /// Constexpr magic. This boils away. Or at least I think it does.
  /// Perhaps? Yes. Yes? Yes. Maybe.
  constexpr bool operator!=(const ConstZip<Its...> &) const {
    static_assert(size() >= 2 && size() <= 6,
                  "The const-ziperator currently only supports [2<=6] iterators. "
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

  constexpr ConstZip &operator++() {
    static_assert(size() >= 2 && size() <= 6,
                  "The const-ziperator currently only supports [2<=6] iterators. "
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
                  "The const-ziperator currently only supports [2<=6] container "
                  "iterators. Live with it");
    if constexpr (size_ == 2) {
      const auto &[a, b] = it_begins;
      return {*a, *b};
    } else if constexpr (size_ == 3) {
      const auto &[a, b, c] = it_begins;
      return {*a, *b, *c};
    } else if constexpr (size_ == 4) {
      const auto &[a, b, c, d] = it_begins;
      return {*a, *b, *c, *d};
    } else if constexpr (size_ == 5) {
      const auto &[a, b, c, d, e] = it_begins;
      return {*a, *b, *c, *d, *e};
    } else if constexpr (size_ == 6) {
      const auto &[a, b, c, d, e, f] = it_begins;
      return {*a, *b, *c, *d, *e, *f};
    }
  }

  static constexpr auto size() { return size_; }
};

/// Interface via which we use the Zip-iterator.
template <Iterable... Its> inline constexpr auto zip(Its &&...its) {
  if constexpr((std::is_const<typename std::remove_reference<Its>::type>::value && ...)) {
    static_assert(!(std::is_const<Its>::value && ...), "All containers are const");
    return ConstZip<Its...>{its...};
  } else if constexpr((!std::is_const<typename std::remove_reference<Its>::type>::value && ...)){
    static_assert((!std::is_const<typename std::remove_reference<Its>::type>::value && ...), "All containers are non-const");
    return Zip<Its...>{std::forward<Its>(its)...};
  } else {
    static_assert(!(std::is_const<typename std::remove_reference<Its>::type>::value ^ ...), "All containers must either be of const type, or non-const type. You can't mix them");
    return InvalidZip{};
  }
}

/// Overloaded call to zip, to handle cases where the containers iterated over are immutable (const)

/// Force the iteration to be over const references to the containers elements
template <Iterable... Its> inline constexpr auto czip(Its &&...its) {
  return ConstZip<const Its&...>{its...};
}


} // namespace cxutils
