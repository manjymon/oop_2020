# structs

## 1 Mismatch

```c++
struct IteratorPair
{
    int * first{};
    int * second{};
};

IteratorPair mismatch(int * first_1, int * last_1, int * first_2, int * last_2)
```

Given 2 ranges, return pointers to the first mismatching pair of elements from the 2 ranges.

### Example

```c++
int arr1[]{1, 2, 3, 4, 5, 6};
int arr2[]{1, 2, 3, 40};

mismatch(arr1, std::end(arr1),
         arr2, std::end(arr2)); // Returns pointers to the 4 and the 40
```

## Studs (very important name)

Given the struct Stud

```c++
struct Stud
{
    int id{};
    char name[30];
};
```

Implement the following functions

```c++
void sort_studs(Stud* first, Stud* last); // Sort range of students by id
```

```c++
void print_studs(const Stud* first, const Stud* last); // Print ids and names of range of studs in the console
```

### Not-a-Bonus (way too trivial for a bonus but feel free to send solutions)

```c++
void input_studs(Stud* first, Stud* last);
// Input range of studs from console
// Handle cstring input correctly
```

```c++
void serialize_studs(const Stud* first, const Stud* last, const char* file_name);
// Serialize range of Studs into a binary file with the given name
// Assume nothing wrong goes with the stream
```

```c++
Stud get_stud_from_stream(/* correct type */ bin_stream, unsigned index);
// Return Stud at given index from binary stream
// Assume nothing wrong goes with the stream
```
