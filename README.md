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

## Enumerate (Enumerator)

A simple wrapper utility for enumerating, while iterating the objects in a range-based for loop

```cpp
    std::vector<int> ints{1,2,3,4};
    for(auto&& [i, el] : enumerate(ints)) {
        std::cout << "index: " << i << ", value: " << el << std::endl;
    }
```

This will print:
index: 0, value: 1
index: 1, value: 2
index: 2, value: 3
index: 3, value: 4

## Zip iterator (Ziperator)

Zips together two iterators from two containers, and iterates until one of them reaches it's end.

Example:
```cpp
    std::vector<int> A{1,2,3};
    std::vector<int> B{4,5,6};

    for(auto&& [a, b] : zip(A, B)) {
        std::cout << a << ", " << b << std::endl;
    }
```

This will print:
1, 4<br>
2, 5<br>
3, 6<br>


