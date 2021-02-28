#pragma once
#include "concepts.hpp"
#include <iterator>

namespace cxutils
{
    template<Iterable It>
    class Enumerator {
    private:
        It it;

        std::size_t index;
        IteratorOf<It> curr;
        const IteratorOf<It> sentinel;

        struct Enumerated {
            std::size_t idx;
            ElementReferenceOf<It> ref;
        };

    public:
        using reference = Enumerated&;
        using value_type = Enumerated;
        using iterator = IteratorOf<It>;

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
        auto size() const { return it.size(); }
    };

    template<Iterable It>
    auto enumerate(It &&iter) {
        return Enumerator<It>(iter);
    }
} // namespace cxutils