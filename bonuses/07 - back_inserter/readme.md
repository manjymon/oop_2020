# Back Inserter

## Problem

Using algorithms with normal vector iterators could sometimes get us out of bounds.

```c++
std::vector<int> v;
std::copy(
	std::istream_iterator<int>{std::cin},
	std::istream_iterator<int>{},
	std::begin(v)
); // BAD. vector has 0 capacity and we attempt to write some elements in it

// Resizing it won't work as we don't know how many ints we will receive from the console
```

## Task

Write an output iterator ```back_inserter_iterator``` that takes a container like vector and can safely be used to push elements to the back.

## Example usage

```c++
std::vector<int> v;
std::copy(
	std::istream_iterator<int>{std::cin},
	std::istream_iterator<int>{},
	back_inserter_iterator<std::vector<int>>{v}
); // OK. back_inserter deals with resizing
```
