#include <exception>
#include <stdexcept>
#include <string>
#include <iostream>

class FooException: public std::exception
{
 public:
    FooException(std::string msg): m_msg{std::move(msg)} {}
    virtual const char* what() const noexcept
    {
        return m_msg.c_str();
    }
 private:
    const std::string m_msg;
};

class BarException: public std::exception
{
 public:
    BarException(std::string msg): m_msg{std::move(msg)} {}
    virtual const char* what() const noexcept
    {
        return m_msg.c_str();
    }
 private:
    const std::string m_msg;
};

int foo()
{
    std::cout << "start" << std::endl;
    throw FooException("abc\n");
    // ----------------------------
    std::cout << "end" << std::endl;

    return 0;
}

int bar(int x)
{
    if (x % 2 == 0)
    {
        throw BarException("def\n");
    }

    return 10;
}

int main()
{
    try
    {
        bar(2);
        foo();
        // ..
        // ...

    }
    catch(FooException& f)
    {
        std::cout << f.what();
    }
    catch(BarException& b)
    {
        std::cout << b.what();
    }

    std::cout << "ama programata ne crashna" << std::endl;

    return 0;
}
