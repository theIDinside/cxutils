#pragma once
#include <algorithm>

template<typename Container>
concept Iterable = requires(Container c) {
    std::begin(c);
    std::end(c);
    c.begin();
    c.end();
};