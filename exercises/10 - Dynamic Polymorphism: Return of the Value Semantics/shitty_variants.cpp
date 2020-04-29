#include <iostream>

/*
    This is just to visualize the idea behind std::variants (with our current knowledge)
    DO NOT WRITE CODE LIKE THIS
*/

class Printable
{
 public:
    Printable(int value) :
        m_value{.i = value},
        m_tag{Tag::is_int}
    {}
    Printable(double value) :
        m_value{.d = value},
        m_tag{Tag::is_double}
    {}
    Printable(char value) :
        m_value{.c = value},
        m_tag{Tag::is_char}
    {}

    void print() const
    {
        switch (m_tag)
        {
            case Tag::is_int:
                std::cout << "INT " << m_value.i << '\n';
                break;
            case Tag::is_double:
                std::cout << "DUBLE " << m_value.d << '\n';
                break;
            case Tag::is_char:
                std::cout << "CHAR " << m_value.c << '\n';
                break;
        }
    }
 private:
    union ValueSet
    {
        int i;
        char c;
        double d;
    };
    enum class Tag
    {
        is_int, is_char, is_double
    };
    ValueSet m_value;
    Tag m_tag;
};
int main()
{
    Printable x = 10;
    x.print();
    x = 2.3;
    x.print();
    x = 'a';
    x.print();
    std::cout << sizeof(x);
}
