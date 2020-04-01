#include <algorithm>
#include <iostream>
#include <fstream>
#include <cassert>
#include <string>

// static

void test()
{
    static int i{1};
    std::cout << i << std::endl;
    i++;
}

// memoization

// RAII

int fib(int n)
{
    assert(n < 100);
    static int memo[100]{0, 1};
    if (n == 0 || memo[n]) 
    {
        return memo[n];
    }
    std::cout << "calc for " << n << std::endl;
    return memo[n] = (fib(n - 1) + fib(n - 2));
}

// static members

class Test
{
 public:
    static const int x = 10;
    static void print()
    {
        std::cout << "ne6to\n";
    }
};

class Student
{
 public:
    Student() :
        m_id{get_id()}
    {}

    Student(const std::string& name) :
        m_name{name},
        m_id{get_id()}
    {}

    size_t id() const
    {
        return m_id;
    }

    friend std::istream& operator>>(std::istream& in, Student& s)
    {
        return in >> s.m_id >> s.m_name;
    }

    friend std::ostream& operator<<(std::ostream& out, const Student& s)
    {
        return out << s.m_id << ' ' << s.m_name;
    }
 private:
    static size_t s_last_id;
    std::string m_name{};
    size_t m_id{};

    static size_t get_id()
    {
        return s_last_id++;
    }
};

size_t Student::s_last_id{0};

template<typename T>
class istream_iterator
{
 public:
    using iterator_category = std::input_iterator_tag;
    using value_type = T;
    using difference_type = ptrdiff_t;
    using pointer = const value_type*;
    using reference = const value_type&;

    istream_iterator() = default;
    istream_iterator(std::istream& in) :
        m_in{&in}
    {
        read();   
    }

    istream_iterator& operator++()
    {
        read();
        return *this;
    }

    istream_iterator operator++(int)
    {
        istream_iterator tmp{*this};
        ++(*this);
        return tmp;
    }

    bool operator!=(const istream_iterator& other) const
    {
        return m_in != other.m_in;
    }

    const T& operator*() const
    {
        return m_value;
    }
    
    const T* operator->() const
    {
        return &m_value;
    }
 private:
    std::istream* m_in{};
    T m_value{};

    void read()
    {
        *m_in >> m_value;

        if (!(*m_in))
        {
            m_in = nullptr;
        }
    }
};

template<typename T>
class ostream_iterator
{
 public:
    using iterator_category = std::output_iterator_tag;
    using value_type = void;
    using difference_type = void;
    using pointer = void;
    using reference = void;

    ostream_iterator() = default;
    ostream_iterator(std::ostream& out, const char* delim = nullptr) :
        m_out{&out},
        m_delim{delim}
    {}

    ostream_iterator& operator=(const T& value)
    {
        *m_out << value;
        if (m_delim) *m_out << m_delim;
        return *this;
    }

    ostream_iterator& operator*()
    {
        return *this;
    }

    ostream_iterator& operator++()
    {
        return *this;
    }

    ostream_iterator& operator++(int)
    {
        return *this;
    }
 private:
    std::ostream* m_out{};
    const char* m_delim{nullptr};
};

int main()
{
    std::ifstream in{"input.txt"};
    // std::ofstream out{"output.txt"};

    std::copy_if(
        istream_iterator<Student>{in},
        istream_iterator<Student>{},
        ostream_iterator<Student>{std::cout, ",\n"},

        [](const Student& s) { return s.id() % 2 == 1; }
    );

    return 0;
}
