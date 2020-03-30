# Stack Adapter

## Stack

Stack is a FILO (first in last out) data structure that holds a collection of elements and provides the following member functions

- constructor that thakes a container and turns it into a stack
- push: That takes an element and puts it on top of the stack
- pop: That removes the top element of the stack
- top: returns a reference to the top of the stack
- size: return numbers of elements in the stack
- empty: return whether the stack is empty
- swap: swap contents of 2 stacks

And also the following non-member functions
- All comparision operators (compare lexicographically starting from the bottom)
- Specialized swap function

## Problem

Write a header file stack.hpp that implements a stack that takes a container and limits the possible operations to the above

- The class should be templated on type of element and type of container
- The default container should be std::deque
- The class should work with std::deque, std::list and std::vector
- Use whatever common subset of the 3 interfaces that you deem suitable (e.g. all 3 have a size method)
- You don't need to know what deque and list are or how they are implemented - just the interface
- BONUS: The class should provide (and use) the following types
-- container_type: type of container
-- value_type: type of element in the stack
-- reference: type of reference to the elements in the stack provided by top()
-- const_reference: same as above
-- size_type: type of the size of the container
-- Note that some of these types are provided by the underlying container
- BONUS BONUS (black magic): Make sure that it only compiles when the type of the elements in the stack is the same as the type of the elements in the container (this is not the standard behaviour)

## Example

See main.cpp
