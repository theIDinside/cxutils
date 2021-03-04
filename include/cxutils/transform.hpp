//
// Created by Simon Farre: 2021-02-25.
// Github: https://github.com/theIDinside
//

#pragma once
/// Sys headers
#include <type_traits>
#include <vector>
#include <iterator>
/// Library headers
#include "concepts.hpp"

namespace cxutils {

template <typename MapFn, typename Container>
using MappedToType = typename std::invoke_result<MapFn, typename std::decay_t<Container>::reference>::type;

/// Utility function, wrapping around the absolutely god-awful std::transform. Now we just pass the container, and the map fn
template <Iterable I, typename MapFn>
constexpr inline auto transform(const I& container, MapFn&& fn) {
  std::vector<MappedToType<MapFn, I>> result_container;
  result_container.reserve(container.size());
  std::transform(container.begin(), container.end(), std::back_inserter(result_container), fn);
  return result_container;
}

template <Iterable I, typename MapFn>
constexpr inline auto transform(I&& container, MapFn&& fn) {
  std::vector<MappedToType<MapFn, I>> result_container;
  result_container.reserve(container.size());
  std::transform(container.begin(), container.end(), std::back_inserter(result_container), fn);
  return result_container;
}
} // namespace cxutils
