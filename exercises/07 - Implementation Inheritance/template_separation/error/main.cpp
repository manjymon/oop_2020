#include "test.hpp"

/*
THIS SHOULD NOT COMPILE.
*/

int main()
{
    // The compiler needs to see the definition of Test(int) here but it is in the .cpp file
    Test<int> t{10};
    return 0;
}
