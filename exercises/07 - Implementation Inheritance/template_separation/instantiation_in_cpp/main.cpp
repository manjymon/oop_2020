#include "test.hpp"

/*
THIS COMPILES
*/

int main()
{
    // Already instantiated once in test.cpp where the definitions were visible
    Test<int> t{10};
    return 0;
}
