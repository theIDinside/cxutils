# C++ utils

The utility functions enumerate(...) and zip(...) returns a reference to the elements in the containers.
However, since I'm not a master-expert at c++, and since I think C++ has some flaws, to iterate over the
references, you don't do for(const auto& ...) nor for(auto& ..) because that & refers to the returned
object holding the {index, value} pair, or the {value, value} pair, not the actual values they hold. 
This is confusing, but I think this boils down to C++ more than anything else. 

Therefore, using these functions require you to use either for(auto ...) or for(auto&& ). And as it stands
right now, they can't be const.

Use at your own will, risk or peril. I am not an expert. But if this inspired you to, to either make something great
or just to mock my atrocious c++ programming knowledge, let me know! 

## Logging
With the function time_and_log in logging.hpp, timing the execution of a function, becomes easy:
```cpp
using IntVec = std::vector<int>;
using IntVecRef = const IntVec&;

int sum_vector(IntVecRef v); // defined somewhere, sums all elements
IntVec get_vec(); // defined somewhere, gives us a vector of ints
int collect_sums_of_vectors(IntVecRef a, IntVecRef b, IntVecRef c); // defined some where. Sums all vectors

namespace cl = cxutils::log;
auto main() {
    const auto intVector = get_vec();
    const auto time_to_sum_vector = cl::time_and_log(sum_vector, intVector);
    
    const auto a = get_vec(); 
    const auto b = get_vec();
    const auto c = get_vec();
    
    const auto time_to_sum_all = cl::time_and_log(collect_sums_of_vectors, a, b, c);
}
```

The function takes template parameters "Duration" , constrained by concept ```AcceptedDuration```, "FnType" which
is the type of the invokable object/function and a variadic set of template parameters, which are the invokable's function
parameters.

When timing a templated function, it becomes rather "cumbersome" in a sense, because C++ will have no way
of figuring out what type the function actually has. Which is unfortunate. Seems to me, a dummy, that the compiler
should be able to deduce it by the parameters we've passed in. For some reason, that's not the case. 

So timing the filling of a vector with the value -1 would look like this:

```cpp
namespace cl = cxutils::log;
IntVec get_vec(); // defined somewhere, gives us a vector of ints
// First we need the type, so we need to fill in the template parameters
using fnType = decltype(std::fill<std::vector<int>::iterator, int>);
const auto v = get_vec();
const auto fill_time = cl::time_and_log<cl::msec, fnType>(std::fill, v.begin(), v.end(), -1);
```

As we can see the first template parameter is cl::msec (millsecond), which is the defaulted template parameter otherwise.

This template is a concept, called AcceptedDuration is either cl::nsec, cl::usec, cl::msec, cl::sec, which are
all type aliases for std::chrono::duration::nano/micro/milli/second.

The second parameter is the type of the templated function we have passed in there. For some weird reason, C++
can't deduce this for me. Which is strange. Seriously, it is strange. I'm a dummy and I think this really should
have been solved.

## Enumerate (Enumerator)

A simple wrapper utility for enumerating, while iterating the objects in a range-based for loop

```cpp
    std::vector<int> ints{1,2,3,4};
    for(auto&& [i, el] : cxutils::enumerate(ints)) {
        std::cout << "index: " << i << ", value: " << el << std::endl;
    }
```

This will print:
index: 0, value: 1
index: 1, value: 2
index: 2, value: 3
index: 3, value: 4

## Zip iterator (ZipTwo)

Zips together two iterators from two containers, and iterates until one of them reaches it's end.

Due to the fact that my template programming skills in C++ is lacking, the header contains zip_two and zip_three, instead of 
some fancy magic that can get called with just zip(...). Which would be preferable. But it is what it is.

Example:
```cpp
    std::vector<int> A{1,2,3};
    std::vector<int> B{4,5,6};

    for(auto&& [a, b] : cxutils::zip_two(A, B)) {
        std::cout << a << ", " << b << std::endl;
    }
```

This will print:
1, 4<br>
2, 5<br>
3, 6<br>

To mutate the elements, you have to do nothing different. So for instance:

```cpp
    std::vector<int> A{1,2,3};
    std::vector<int> B{4,5,6};

    for(auto&& [a, b] : cxutils::zip_two(A, B)) {
        a += b;
        b = a;
    }
    for(auto&& [a, b] : cxutils::zip_two(A, B)) {
        std::cout << a << ", " << b << std::endl;
    }
```

Will print 
5, 5<br>
7, 7<br>
9, 9<br>

Zipping three iterators, work exactly the same, with the call being to ```cxutils::zip_three(a, b, c)```