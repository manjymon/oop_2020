#include "noisy.hpp"

int main()
{
    Noisy n{6};
    Noisy nn{n};
    n.shout();
    return 0;
}
