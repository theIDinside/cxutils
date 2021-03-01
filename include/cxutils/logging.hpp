//
// Created by Simon Farre: 2021-02-28.
// Github: https://github.com/theIDinside
//

#pragma once
#include <chrono>
#include <type_traits>

namespace cxutils::log {

using hiResClock = std::chrono::high_resolution_clock;

using nsec = std::chrono::nanoseconds;
using usec = std::chrono::microseconds;
using msec = std::chrono::milliseconds;
using sec = std::chrono::seconds;

template <typename T, typename U>
using is = std::is_same<T, U>;

template <typename D>
concept AcceptedDuration = (is<D, nsec>::value || is<D, usec>::value || is<D, msec>::value || is<D, sec>::value);

/// Simple utility for measuring execution time of Fn, with parameters FnArgs.
/// Default duration is microseconds, but can be varied from ns -> s.
/// Constrained by the concept AcceptedDuration to only accept this interval of
/// duration types.
template <AcceptedDuration Duration = usec, typename Fn,
          typename... FnParameters>
constexpr auto time_and_log(Fn &&f, FnParameters &&...fn_args) {
  auto begin = hiResClock::now();
  f(std::forward<FnParameters>(fn_args)...);
  auto end = hiResClock::now();
  auto dur = std::chrono::duration_cast<Duration>(end - begin).count();
  return dur;
}
} // namespace cxutils::log