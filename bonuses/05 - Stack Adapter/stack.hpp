#include <iostream>
#include <deque>
#include <list>
#include <vector>

template<
    typename T,
    typename Container = std::deque<T>,
    // Non-standard behaviour
    typename = std::enable_if_t<std::is_same<T, typename Container::value_type>::value, std::nullptr_t>
>
class stack
{
 public:
    using container_type = Container;
    using value_type = typename container_type::value_type;
    using size_type = typename container_type::size_type;
    using reference = typename container_type::reference;
    using const_reference = typename container_type::const_reference;
        
    stack() = default;
    explicit stack(const container_type& container) :
        m_container(container)
    { }

    bool empty() const { return m_container.empty(); }
    size_type size() const { return m_container.size(); }
    reference top() { return m_container.back(); }
    const_reference top() const { return m_container.back(); }
    void pop() { m_container.pop_back(); }
    void push(const value_type& element) { m_container.push_back(element); }
        
    void swap(const stack& other)
    {
        using std::swap;
        swap(m_container, other.m_container);
    }
        
 private:
    container_type m_container{};
};

template<typename Value, typename Container>
bool operator==(const stack<Value, Container>& lhs, const stack<Value, Container>& rhs)
{
    return lhs.m_container == rhs.m_container;
}

template<typename Value, typename Container>
bool operator!=(const stack<Value, Container>& lhs, const stack<Value, Container>& rhs)
{
    return !(lhs.m_container == rhs.m_container);
}

template<typename Value, typename Container>
bool operator<(const stack<Value, Container>& lhs, const stack<Value, Container>& rhs)
{
    return lhs.m_container < rhs.m_container;
}

template<typename Value, typename Container>
bool operator>(const stack<Value, Container>& lhs, const stack<Value, Container>& rhs)
{
    return lhs.m_container < rhs.m_container;
}

template<typename Value, typename Container>
bool operator<=(const stack<Value, Container>& lhs, const stack<Value, Container>& rhs)
{
    return !(lhs.m_container > rhs.m_container);
}

template<typename Value, typename Container>
bool operator>=(const stack<Value, Container>& lhs, const stack<Value, Container>& rhs)
{
    return !(lhs.m_container < rhs.m_container);
}

template<typename Value, typename Container>
void swap(stack<Value, Container>& lhs, stack<Value, Container>& rhs)
{
    lhs.swap(rhs);
}
