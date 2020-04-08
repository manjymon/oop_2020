#include <iostream>

struct Base
{
    void print(int) const { std::cout << "INT\n"; }
};

struct DerivedError : Base
{
    void print(double) const { std::cout << "DOUBLE\n"; }
    void print(long) const { std::cout << "LONG\n"; }
};

struct EmptyDerived : Base
{

};

struct DerivedCombined : Base
{
    void print(double) const { std::cout << "DOUBLE\n"; }
    void print(long) const { std::cout << "LONG\n"; }
    using Base::print;
};

struct DerivedOverriden : Base
{
    void print(double) const { std::cout << "DOUBLE\n"; }
    void print(long) const { std::cout << "LONG\n"; }
    void print(int) const { std::cout << "OVERRIDEN INT\n"; }
};

int main()
{
    DerivedError d;
    // d.print(10); // ERROR: ambiguous call
    /*
        Overloads only consider the scope of the derived class
        In this case we only get overloads for long and double and we can't get choose one between them
    */

    d.Base::print(10); // INT
    // In this case we specifically search for print in Base

    EmptyDerived dd;
    dd.print(10); // INT
    // In this case there are no overloads of print in EmptyDerived so we look for one in Base

    DerivedCombined ddd;
    ddd.print(10); // INT
    // In this case we take print's overload set from Base and add it directly to DerivedCombined.
    // Now the int version is unambiguously the best fitting version

    DerivedOverriden dddd;
    dddd.print(10); // OVERRIDEN INT
    // We override print for ints
}
