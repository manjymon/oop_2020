#include "test.hpp"

template<typename T>
Test<T>::Test(int x): data{x} {}

// Instantiate Test<int> here, where all the definitions are visible
template class Test<int>;
