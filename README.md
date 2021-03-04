# C++ utils

## Usage

### Requirements
- c++20 / c++latest <br> 
  I've deliberately written this in C++20 as it simplifies usage of template "meta" programming, and a bunch 
  of other things. But since I'm entirely a novice in that kind of stuff, the Ziperator for instance
  can _not_ iterate over containers of type ```const container<T>```. Also, when using in a range-for-loop one 
  can't write ```const auto```, just use ```auto``` or ```auto&&```. I would blame C++ for being horrible
  in how one implements iterators, but I'm sure it's due to me being a 'moron' too. With all caveats out of the way, 
  lets get into it.
- cmake version 3.15 (I think), whatever version that has the feature "FetchContent" (or you can clone it manually to
  a subdirectory, and add "add_subdirectory(to_cloned_path)". I prefer the "build system" approach though.)

### CMake settings
The "build system approach", that I spoke of earlier:
In your CMakeLists.txt file, put:

```cmake
include(FetchContent)
FetchContent_Declare(
        cxutils
        GIT_REPOSITORY https://github.com/theIDinside/cxutils.git
        GIT_TAG master
        GIT_PROGRESS TRUE
)
FetchContent_GetProperties(cxutils)
if (NOT cxutils_POPULATED)
    FetchContent_Populate(cxutils)
    add_subdirectory(${cxutils_SOURCE_DIR} ${cxutils_BINARY_DIR})
endif()

# If you are compiling a target called "myproj", just add
target_link_libraries(myproj cxutils)
```
Now you can for instance do;
```cpp
#include <cxutils/zip.hpp>
```

And start using the "library".

Use at your own will, risk or peril. 

## Logging
With the function time_and_log in logging.hpp, timing the execution of a function, becomes easy to remember:
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

## Zip-iterator

#### Usage constraints
- You can't use containers which are const, which means the iterations can never be immutable (you can obviously
  choose not to mutate the elements. But that's just what it is.)


Zips together 2 or more (up to 6) iterators from two containers, and iterates until one of them reaches it's end.

``` cxutils::zip(...)``` now does exist and it can take up to 6 containers. This is done using some extra-ordinary fine
hack and slashing by me, which I am utterly shamelessly, ignorantly proud of with some if constexpr hacking and 
destructuring of std::tuples. Damn that was satisfying, yet horrible and non-extensive looking. Love it still.
This means no more zip_two(a, b) or zip_three(a,b,c) calls, but it's all hiding behind one interface zip(...).

Example:
```cpp
    std::vector<int> A{1,2,3};
    std::vector<int> B{4,5,6};

    for(auto&& [a, b] : cxutils::zip(A, B)) {
        std::cout << a << ", " << b << std::endl;
    }
    // or if we want to for some god ugly unknown reason, we can do this;
    for(auto&& [a, b, a2, b2, a3] : cxutils::zip(A, B, A, B, A)) {
        // please lord why
    }
    /// works with 3 different containers, of different types
    std::list<int> lst{1,2,3,4};
    std::vector<S> vec{S{"a"}, S{"b"}, S{"c"}, S{"d"}};
    std::array<float, 4> arr{1.0f, 2.0f, -3.0f, 3.14f};
    
    for(auto [l, v, a] : cxutils::zip(lst, vec, arr)) {
        // do stuff
    }
    
```

This will print:
1, 4<br>
2, 5<br>
3, 6<br>

Remember. Even if you write auto [a, b], you are _not_ taking the contents of the containers' elements by value.
What you are receiving by my library, is a tuple of references to the elements in the container. This means
that they will be mutable and not protected from you being stupid, and since I'm stupid, let's not compound the
possibilities for disaster here.

To mutate the elements, you have to do nothing different. So for instance:

```cpp
    std::vector<int> A{1,2,3};
    std::vector<int> B{4,5,6};

    for(auto [a, b] : cxutils::zip(A, B)) {
        a += b;
        b = a;
    }
    for(auto [a, b] : cxutils::zip(A, B)) {
        std::cout << a << ", " << b << std::endl;
    }
```

Will print:<br> 
5, 5<br>
7, 7<br>
9, 9<br>


## Cmake utils
In the folder cmake, custom quick go-to utilities for CMake are placed. Currently, it consists of
- CustomFunctions.cmake

In this file, simple function calls are defined for creating a library / project. An example of 
defining an executable using this function would be:

```cmake
set(SOURCES src/main.cpp src/app.cpp src/app.hpp)
SetupExecutable(
        NAME ${PROJECT_NAME}
        CXX20 True
        SOURCES ${SOURCES}
        INCLUDE_DIRS src deps/some_lib/include
        DEPENDENCIES fmt glfw)
```

This basically expands to
```cmake
add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE src)
target_include_directories(${PROJECT_NAME} PRIVATE deps/some_lib/include)
target_link_libraries(${PROJECT_NAME} fmt glfw)
SET_CXX_20(${PROJECT_NAME})
set_target_properties(${PROJECT_NAME} PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED True
        CXX_EXTENSIONS FALSE)
```

Further utilities will be added to this interface later on.