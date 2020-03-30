# Bonus 01 - Registry

## Registry

Implement a class registry that keeps track of inserted integers.

## Properties

- The registry should contain a maximum of 100 elements (so we don't deal with the heap for now)
- Every element should be associated with an **unique** id (whole number)
- Elements must be sorted by id
- Method insert that inserts an integer into the registry and returns its id (assert that there is enough space)
- Method erase that removes an element with given id by marking it invalid and returns whether such id existed in the registry
- Method size that returns the number of valid elements in the registry
- If no more than half of the elements in the array are valid, compact the registry by removing the invalid ones

## Example

```
// Not actual code
// ids don't have to be these

insert 1 -> id 0
insert 2 -> id 1
insert 3 -> id 2

Registry: 1 2 3

remove 0
Registry: x 2 3

remove 1
Registry: 3

insert 4 -> id 3
insert 5 -> id 4

Registry 3 4 5

remove 3
Registry: 3 x 5

size -> 2
```

## Notes

- Consider the different invariants that the class must have. Maybe write down some as comments
- Use STL Algorithms when possible
- Make it work well, not just work.
