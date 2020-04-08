#pragma once

template<typename T>
struct Test
{
    Test(int);
    T data;
};

template<typename T>
Test<T>::Test(int x): data{x} {}
