#include <algorithm>
#include <cassert>
#include <cstring>
#include <iostream>
#include <numeric>

/*
Notes
This solution was from before I changed the specifications.
Instead of asserting that the age / salary values are correct, we clamp them between the correct values
std::clamp is a standard library function (C++17) below is a possible implementation that only works with unsigned integers
*/

unsigned clamp(unsigned value, unsigned low, unsigned high)
{
    assert(low <= high);
    return value < low ? low : high < value ? high : value;
}

class Employee
{
 public:
    Employee() = default;

    Employee(const char * name, unsigned age, unsigned salary):
        m_age{clamp(age, 18, 64)},
        m_salary{clamp(salary, 610, 10000)}
    {
        set_name(name);
    }

    void set_name(const char * name)
    {
        assert(name && strlen(name) < 50);
        strcpy(m_name, name);
    }

    void set_age(unsigned age)
    {
        m_age = clamp(age, 18, 64);
    }

    void set_salary(unsigned salary)
    {
        m_salary = clamp(salary, 610, 10000);
    }

    const char * get_name() const
    {
        return m_name;
    }

    unsigned get_age() const
    {
        return m_age;
    }

    unsigned get_salary() const
    {
        return m_salary;
    }

    void print() const
    {
        std::cout << m_name << ' ' << m_age << ' ' << m_salary << '\n';
    }
 private:
    char m_name[51]{};
    unsigned m_age{18};
    unsigned m_salary{610};
};

class Company
{
 public:
    bool empty() const
    {
        return !m_size;
    }

    size_t size() const
    {
        return m_size;
    }

    Company& add(const Employee& employee)
    {
        assert(m_size != 1000);
        employees_[m_size++] = employee;

        return *this;
    }

    void print() const
    {
        std::for_each(employees_, employees_ + m_size, [](const Employee& employee){
            employee.print();
        });
    }
 private:
    Employee employees_[1000]{};
    size_t m_size{0};
};

int main()
{
    Company c{};
    c.add({"Pe6o", 0, 0})
     .add({"Stamat", 100, 100000})
     .add({"Asen", 30, 3000})
     .print();

    std::cout << '\n';

    // c.fire("Stamat");
    c.add({"Be6o", 33, 7000})
     .print();

    // std::cout << "\nTOTAL: " << c.total_salaries() << "\n\n";

    // c.sort().print();
    return 0;
}
