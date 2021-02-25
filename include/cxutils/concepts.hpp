#pragma once
#include <algorithm>

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
    typename std::decay_t<Container>::reference;
    typename std::decay_t<Container>::value_type;
};