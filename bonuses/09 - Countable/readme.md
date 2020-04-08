# Countable

## Problem

Implement a class Countable, that when inherited, provides the derived class with 2 new static methods:
* living: returns the amount of living objects of the derived type
* created: returns the amount of objects of the derived type that have been created

## Example usage

```c++
struct Test : /* inherit Countable here */ {};
struct Test2 : /* ... */ {};

int main()
{
    Test x;
    Test y = x;
    auto z = new Test;
    std::cout << "Living: " << Test::living() << std::endl;
    std::cout << "Created " << Test::created() << std::endl;
    delete z;
    std::cout << "Living: " << Test::living() << std::endl;
    std::cout << "Created " << Test::created() << std::endl;
    Test2 a;
    std::cout << "Living Test2: " << Test2::living() << std::endl;
    std::cout << "Created Test2: " << Test2::created() << std::endl;
    return 0;
}

/* Output
Living: 3
Created 3
Living: 2
Created 3
Living Test2: 1
Created Test2: 1
*/
```
