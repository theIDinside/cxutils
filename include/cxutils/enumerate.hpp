#pragma once
#include "concepts.hpp"

namespace cxutils
{
    template<Iterable It>
    class Enumerator {
    private:
        It it;
        using Iterator = decltype(it.begin());
        using Deref = decltype(*it.begin());

        std::size_t index;
        Iterator curr;
        const Iterator sentinel;

        struct Enumerated {
            std::size_t idx;
            Deref ref;
        };

    public:
        Enumerator(It iterable) noexcept : it(iterable), index(0),
                                           curr(std::begin(iterable)),
                                           sentinel(std::end(iterable)) {}

        const Enumerator &begin() const { return *this; }
        const Enumerator &end() const { return *this; }

        bool operator!=(const Enumerator &) const { return curr != sentinel; }

        void operator++() {
            ++curr;
            ++index;
        }

        auto operator*() const -> Enumerated { return {index, *curr}; }
    };

    template<Iterable It>
    auto enumerate(It &&iter) {
        return Enumerator<It>(iter);
    }
} // namespace cxutils