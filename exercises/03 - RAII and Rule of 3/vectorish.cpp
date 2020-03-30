#include <iostream>
#include <cassert>
#include <algorithm>

class ReverseIterator
{
 public:
    ReverseIterator(int* ptr): m_ptr{ptr} {}
    bool operator!=(const ReverseIterator& other) const
    {
        return m_ptr != other.m_ptr;
    }

    ReverseIterator& operator++()
    {
        --m_ptr;
        return *this;
    }

    const int& operator*() const
    {
        return *m_ptr;
    }

    int& operator*()
    {
        return *m_ptr;
    }

    const int* operator->() const
    {
        return m_ptr;
    }

    int* operator->()
    {
        return m_ptr;
    }
 private:
    int* m_ptr{nullptr};
};


class DynamicIntArray
{
public:
    DynamicIntArray() = default;
    // RAII
    // Resource Acquisition Is Initialization
    // Acquire resources in ctor
    // Release them in the dtor
    explicit DynamicIntArray(size_t size):
        m_arr{new int[size]{}},
        m_size{size},
        m_capacity{size}
    {}

    // Rule of 3
    // If you define / delete one of destructor, copy constructor and assignment operator
    // you must define / delete them all if you want your program to run correctly
    ~DynamicIntArray()
    {
        delete [] m_arr;
    }

    DynamicIntArray(const DynamicIntArray& other):
        m_arr{new int[other.m_capacity]},
        m_size{other.m_size},
        m_capacity{other.m_capacity}
    {
        std::copy(other.begin(), other.end(), begin());
    }

    // Copy and Swap Idiom
    DynamicIntArray& operator=(const DynamicIntArray& other)
    {
        DynamicIntArray temp{other};
        swap(temp);
        return *this;
    }

    void push_back(int element)
    {
        if (m_size >= m_capacity)
        {
            extend();
        }
        m_arr[m_size++] = element;
    }

    size_t size() const
    {
        return m_size;
    }

    size_t capacity() const
    {
        return m_capacity;
    }

    ReverseIterator rbegin()
    {
        return ReverseIterator{end() - 1};
    }

    ReverseIterator rend()
    {
        return ReverseIterator{begin() - 1};
    }

    int* begin()
    {
        return m_arr;
    }

    int* end()
    {
        return m_arr + m_size;
    }

    const int* begin() const
    {
        return m_arr;
    }

    const int* end() const
    {
        return m_arr + m_size;
    }

    void reserve(size_t capacity)
    {
        if (capacity > m_capacity)
        {
            resize(capacity);
        }
    }

    void swap(DynamicIntArray& other)
    {
        using std::swap;
        swap(m_arr, other.m_arr);
        swap(m_size, other.m_size);
        swap(m_capacity, other.m_capacity);
    }

    bool operator==(const DynamicIntArray& other) const
    {
        return m_size == other.m_size &&
               std::equal(begin(), end(), other.begin());
    }
private:
    int* m_arr{nullptr};
    size_t m_size{0};
    size_t m_capacity{0};

    void extend()
    {
        resize(m_capacity * 3 / 2 + 1);
    }

    void resize(size_t capacity)
    {
        m_capacity = capacity;

        int* new_m_arr{new int[m_capacity]};
        std::copy(begin(), end(), new_m_arr);
        delete [] m_arr;
        m_arr = new_m_arr;
    }
};

// ADL
void swap(DynamicIntArray& lhs, DynamicIntArray& rhs)
{
    lhs.swap(rhs);
}

int main()
{
    DynamicIntArray da;
    da.reserve(20);
    for (int i = 0; i < 20; i++)
    {
        da.push_back(i);
    }

    DynamicIntArray db = da;

    std::cout << std::boolalpha << (da == db) << std::endl;

    std::for_each(
        da.rbegin(),
        da.rend(),
        [](int a) {
            std::cout << a << ' '; 
        }
    );


    return 0;
}
