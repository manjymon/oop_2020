#include <memory>
#include <iostream>

template <typename Self>
class ClonableBase
{
 public:
    virtual std::unique_ptr<Self> clone() const
    {
        return std::make_unique<Self>(static_cast<const Self&>(*this));
    }
};

template <typename Base, typename Parent, typename Self>
class Clonable: public Parent
{
 public:
    std::unique_ptr<Base> clone() const override
    {
        return std::make_unique<Self>(static_cast<const Self&>(*this));
    }
};

struct Base: public ClonableBase<Base>
{
    virtual void foo() const { std::cout << "Base\n"; }
};

struct Derived1: public Clonable<Base, Base, Derived1>
{
    void foo() const override { std::cout << "Derived\n"; }
};

struct Derived2: public Clonable<Base, Derived1, Derived2>
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
