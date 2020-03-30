#include <iostream>

#include "stack.hpp"

int main()
{
    stack<int> st;
    st.push(10);
    st.push(20);
    std::cout << st.top() << std::endl; // 20
    st.pop();
    std::cout << st.top() << std::endl; // 10
    st.top() = 30;
    std::cout << st.top(); // 30

    return 0;
}
