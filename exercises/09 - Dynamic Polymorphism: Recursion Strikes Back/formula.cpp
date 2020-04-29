/*
<Number> ...float
<Symbol> := + | - | * | /
<Formula> := <Number> | (<Formula><Symbol><Formula>)

print(поток)
evaluate

"(1+1)".evaluate() -> 2
*/

#include <iostream>
#include <cassert>
#include <string>

class Formula
{
 public:
    Formula() = default;
    virtual float evaluate() const = 0;
    virtual std::ostream& print(std::ostream& out = std::cout) const = 0;
    virtual ~Formula() = default;
    virtual Formula* clone() const = 0;
    Formula(const Formula&) = delete;
    Formula& operator=(const Formula&) = delete;
};

class Number: public Formula
{
 public:
    Number(float value) : m_value{value}
    {}

    float evaluate() const override
    {
        return m_value;
    }

    std::ostream& print(std::ostream& out) const override
    {
        return out << m_value;
    }

    Number* clone() const override
    {
        return new Number{m_value};
    }
 private:
    float m_value;
};

class Operation : public Formula
{
 public:
    Operation(char op, Formula* lhs, Formula* rhs) :
        m_op{op},
        m_lhs{lhs},
        m_rhs{rhs}
    {}

    float evaluate() const override
    {
        switch(m_op)
        {
            case '+':
                return m_lhs->evaluate() + m_rhs->evaluate();
            case '*':
                return m_lhs->evaluate() * m_rhs->evaluate();
            case '/':
                return m_lhs->evaluate() / m_rhs->evaluate();
            case '-':
                return m_lhs->evaluate() - m_rhs->evaluate();
            default:
                assert(false);
        }
    }

    std::ostream& print(std::ostream& out) const override
    {
        out << "(";
        m_lhs->print(out);
        out << m_op;
        m_rhs->print(out);
        out << ")";
        return out;
    }

    ~Operation()
    {
        delete m_lhs;
        delete m_rhs;
    }

    Operation* clone() const override
    {
        return new Operation{m_op, m_lhs->clone(), m_rhs->clone()};
    }

 private:
    char m_op;
    Formula* m_lhs;
    Formula* m_rhs;
};

/*
single digits only
no white space
brackets everywhere
only parses correct things
*/

size_t find_next(const std::string& expr, size_t from)
{
    char current{expr[from++]};
    if (current >= '0' && current <= '9')
    {
        return from;
    }

    for(size_t counter{1} ; counter ; ++from)
    {
        current = expr[from];
        if (current == '(')
        {
            ++counter;
        }
        if (current == ')')
        {
            --counter;
        }
    }

    return from;
}

Formula* parse(const std::string& expr, size_t from = 0)
{
    char current{expr[from]};
    if (current >= '0' && current <= '9')
    {
        return new Number{static_cast<float>(current - '0')};
    }
    // if (current = '(')
    size_t next{find_next(expr, from + 1)};
    char op{expr[next]};
    // next formula starts at: next + 1
    return new Operation{
        op,
        parse(expr, from + 1),
        parse(expr, next + 1)
    };
}

int main()
{
    std::string input;
    std::cin >> input;
    Formula* ptr = parse(input);
    ptr->print();
    std::cout << " = " << ptr->evaluate();
    delete ptr;
    return 0;
}
