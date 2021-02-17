// NB!!!!! This is _not_ how you would include these files normally.
#include "../include/cxutils/enumerate.hpp"
#include "../include/cxutils/zip.hpp"

#include <array>
#include <vector>
#include <iostream>

int main() {
    std::array<char, 8> A{'h', 'l', 'o', ' ', 'o', 'l', '!', '_'}; // last _ char to show that zip(..) ends as soon as one container runs out
    std::array<char, 7> B{'e', 'l', ',', 'w', 'r', 'd', '!'}; 

    for(auto&& [a, b] : cxutils::zip(A, B)) {
        std::cout << a << b;
    }
    std::cout << std::endl;

    std::vector<int> ints{3, 2, 1};

    for(auto&& [index, el] : cxutils::enumerate(ints)) {
        std::cout << "index: " << index << ", value: " << el << std::endl;
    }

}