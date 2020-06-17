# Clonable

## Problem

Implement 2 classes Clonable and ClonableBase, that when inherited, provide the derived classes with a virtual clone functions that returns a copy of the object wrapped in a unique_ptr:
* ClonableBase should be used for the base class and Clonable for the others
* Assume that the deriving class provides its own copy constructor
* Try to make it work with longer inheritance chains
* Try to sure you return the correct type

## Example usage

```c++
struct Base: /* inherit ClonableBase here */
{
    virtual void foo() const { std::cout << "Base\n"; }
};

struct Derived1: /* inherit Clonable and Base here */
{
    void foo() const override { std::cout << "Derived\n"; }
};

struct Derived2: /* Inherit clonable and derived 1 here*/
{};

int main()
{
    std::unique_ptr<Base> dptr{std::make_unique<Derived1>()};
    dptr->foo();
    dptr = std::make_unique<Derived2>();
    dptr->foo();

    std::unique_ptr<Base> bptr{std::make_unique<Base>()};
    bptr->foo();
    bptr = dptr->clone();
    bptr->foo();
}


/* Output
Derived
Derived
Base
Derived
*/
```
