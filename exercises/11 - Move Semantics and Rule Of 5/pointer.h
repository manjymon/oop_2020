#include <iostream>
#include <utility>

template<typename T>
class pointer
{
 public:
    pointer() = default;
    pointer(const T& data):
        m_ptr{new T{data}}
    {}

    pointer(T* ptr): m_ptr{ptr}
    {}

    pointer(const pointer& other): m_ptr{new T}
    {
        if (other.m_ptr) {
            *m_ptr = *other.m_ptr;
        }
    }

    pointer(pointer&& other): m_ptr{std::exchange(other.m_ptr, nullptr)}
    {
    }

    pointer& operator=(const pointer& other)
    {
        pointer tmp{other};
        std::swap(tmp.m_ptr, m_ptr);
        return *this;
    }

    pointer& operator=(pointer&& other)
    {
        pointer tmp{std::move(other)};
        std::swap(tmp.m_ptr, m_ptr);
        return *this;
    }

    ~pointer()
    {
        delete m_ptr;
    }
 private:
    T* m_ptr{nullptr};
};
