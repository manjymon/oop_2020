#include <iostream>
#include <vector>
#include <string>

using namespace std::literals;

template<typename T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& v)
{
    for (const T& x : v)
    {
        out << x << std::endl;
    }

    return out;
}

class PrintableInterface
{
 public:
    virtual std::ostream& print(std::ostream&) const = 0;
    virtual ~PrintableInterface() = default;
    virtual PrintableInterface* clone() const = 0;
};

template<typename T>
class PrintableImplementation: public PrintableInterface
{
 public:
    PrintableImplementation(const T& value): m_value(value) {}
    std::ostream& print(std::ostream& out) const override
    {
        return out << m_value;
    }

    PrintableImplementation* clone() const override
    {
        return new PrintableImplementation{*this};
    }
 private:
    T m_value;
};

class Printable
{
 public:
    template<typename T>
    Printable(const T& value): m_ptr{new PrintableImplementation<T>{value}}
    {}

    friend std::ostream& operator<<(std::ostream& out, const Printable& p)
    {
        return p.m_ptr->print(out);
    }

    Printable(const Printable& other):
        m_ptr{other.m_ptr->clone()}
    {}

    Printable& operator=(const Printable& other)
    {
        Printable temp{other};
        std::swap(m_ptr, temp.m_ptr);
        return *this;
    }

    ~Printable()
    {
        delete m_ptr;
    }
 private:

    PrintableInterface* m_ptr{};
};

struct Student
{
    std::string name;
};

std::ostream& operator<<(std::ostream& out, const Student& v)
{
    return out << v.name;
}

int main()
{
    std::vector<Printable> v;
    v.emplace_back(2);
    v.emplace_back("alabala"s);
    v.emplace_back(2.3);
    v.emplace_back(Student{"Pe6o"});
    v.emplace_back(v);

    std::cout << v;
    return 0;
}
