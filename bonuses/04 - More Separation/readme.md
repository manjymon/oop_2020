# 04 - More Separation

## Problem

We demonstrated how to decrease compilation times by separating classes into interfaces and implementation. One problem is that the header file contains both the interface and some implementation details (member variables and private helper methods) that are going to be changed more often (thus "breaking the contract"). One way to avoid that problem is to put all of these details in a separate implementation class.

## Task

Given the header noisy.hpp

```c++
class Noisy
{
 public:
    Noisy();
    explicit Noisy(int);
    Noisy(const Noisy&);
    Noisy& operator=(const Noisy&);
    ~Noisy();
    void swap(Noisy&);

    bool should_shout() const { return true; }
    void shout() const;
 private:
    class Implementation;
    // <Somehow declare an implementation member here>
};

```

- Implement every method of Noisy in a separate .cpp file
- The only modification you can (and should) do to the header file is to add an instance of the Implementation class as a data member (somehow)
- Consider what problem would arise if we were to change the size / layout of Implementation's data members

## Noisy's API

- Noisy should countain an integer
- Every special member function of Noisy should output its name and the contained (or copied) integer e.g. "DTOR 6"
- shout should output something in the console but **only** if should_shout returns true (in this toy example, should shout always returns true but you are not allowed to skip the check)
- The entire logic of shout should be in the Implementation class (to simulate a more complex example), the method in Noisy should only act as a *connection*.
