#include "test.hpp"

/*
THIS COMPILES
*/

int main()
{
    // The compiler needs to see the definition of Test(int) here and it can because it is in test.hpp (included above)
    Test<int> t{10};
    return 0;
}
