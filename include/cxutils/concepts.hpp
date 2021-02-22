#pragma once
#include <algorithm>

template<typename Container>
concept Iterable = requires(Container c) {
    std::begin(c);
    std::end(c);
    c.begin();
    c.end();
    typename std::decay_t<Container>::iterator;
    typename std::decay_t<Container>::reference;
};