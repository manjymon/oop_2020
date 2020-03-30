#include <iostream>

// Any bool (only false is not covered) + any creates an empty struct
template<bool, typename T = void>
struct enable_if {};

// true + any type creates a struct that provides the type
template<typename T>
struct enable_if<true, T> { using type = T; };

// Syntax Sugar
template<bool Condition, typename Type>
// We have to use typename for nested types
using enable_if_t = typename enable_if<Condition, Type>::type;

// Any two types (except two identical ones) create a struct with value false
template<typename, typename>
struct is_same { static const bool value = false; };

// Two identical types create a struct with value true
template<typename T>
struct is_same<T, T> { static const bool value = true; };

// This exact example could be done easily without enable_if and is_same this is a toy example
template<
    typename T1,
    typename T2,
    /*
        Our goal is to get an error on identical types so we can skip this template for them using SFINAE
        is_same on identical types gives a true value -> negated to false
        enable_if with false does not provide ::value => error => SFINAE
        typename = some_type means 3rd template parameter with default value
        the point of the above is to try to force an error in a meaningless context
    */
    typename = enable_if_t<!is_same<T1, T2>::value, T1>
>
T1 add(const T1& lhs, const T2& rhs)
{
    std::cout << "HERE BE DRAGONS\n";
    return lhs + static_cast<T1>(rhs);
}

// Catch all template for the rest of the cases
template<typename T>
T add(const T& lhs, const T& rhs)
{
    std::cout << "THIS IS FINE\n";
    return lhs + rhs;
}

int main()
{
    int x = 10;
    unsigned y = 20;
    int32_t z = 30;
    
    add(x, y); // Calls specialization for same types
    add(x, z); // Calls specialization for different types
}
