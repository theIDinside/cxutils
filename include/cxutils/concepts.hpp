#pragma once
#include <algorithm>
#include <type_traits>

template<typename Container>
concept Iterable = requires(Container c) {
    std::begin(c);
    std::end(c);
    c.begin();
    c.end();
    c.size();
    // this is, so we can remove & and && from the type. so,
    // std::array<char, 4>& -> std::array<char, 4> since that is what we care for
    typename std::decay_t<Container>::iterator;
    typename std::decay_t<Container>::const_iterator;
    typename std::decay_t<Container>::reference;
    typename std::decay_t<Container>::const_reference;
    typename std::decay_t<Container>::value_type;
};

template <Iterable I>
using IteratorOf          = std::conditional_t<std::is_const_v<I>, typename std::decay_t<I>::const_iterator, typename std::decay_t<I>::iterator>;
template <Iterable I>
using ElementReferenceOf  = std::conditional_t<std::is_const_v<I>, typename std::decay_t<I>::const_reference, typename std::decay_t<I>::reference>;
template <Iterable I>
using ElementValueTypeOf = typename std::decay_t<I>::value_type;