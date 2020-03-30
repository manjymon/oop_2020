# 06 - Lazy

## Problem

Write a function ```make_lazy``` that takes any callable object (that can be called with zero arguments) and returns an object that will only calculate the value when needed.

## Example

```c++
// Initialize x, don't calculate value yet
auto x = make_lazy(
    [](){
        std::cout << "Imagine this is a sloooooooooow calculation...\n";
        return 10 * 2;
    }
);

std::cout << "No calculation yet\n";

// First use of x, make the calculation
[](int a) {
    std::cout << a << '\n';
}(x);

// Second use of x, don't make the calculation
std::cout << x << '\n';

/* Output:
No calculation yet
Imagine this is a sloooooooooow calculation...
20
20
*/
```

## Getting a function's return type

```c++
// Where F is the type of the function
// C++17
std::invoke_result_t<F>;

// C++14
std::result_of_t<F()>;

// C++11
typename std::result_of<F()>::type;
```
