#pragma once
#include "concepts.hpp"

namespace cxutils
{
    template<Iterable ItA, Iterable ItB>
    class Ziperator {
    private:
        ItA itA;
        ItB itB;
        using IteratorA = decltype(itA.begin());
        using IteratorB = decltype(itB.begin());

        using DerefA = decltype(*itA.begin());
        using DerefB = decltype(*itB.begin());
        IteratorA iter_a;
        IteratorB iter_b;

        IteratorA iter_a_end;
        IteratorB iter_b_end;

        struct Zipped {
            DerefA a;
            DerefB b;
        };

    public:
        Ziperator(ItA itA, ItB itB) noexcept : itA(itA), itB(itB), iter_a(itA.begin()), iter_b(itB.begin()),
                                             iter_a_end(itA.end()), iter_b_end(itB.end()) {}
        const Ziperator &begin() const { return *this; }
        const Ziperator &end() const { return *this; }

        bool operator!=(const Ziperator &) const { return iter_a != iter_a_end && iter_b != iter_b_end; }

        void operator++() {
            ++iter_a;
            ++iter_b;
        }

        auto operator*() const -> Zipped { return {*iter_a, *iter_b}; }
    };

    template<Iterable ItA, Iterable ItB>
    auto zip(ItA &&iterA, ItB &&iterB) {
        return Ziperator<ItA, ItB>(iterA, iterB);
    }
} // namespace cxutils
