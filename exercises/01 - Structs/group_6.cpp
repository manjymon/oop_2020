#include <cstring>
#include <iostream>
#include <fstream>


struct pair
{
    const int* ptr1{};
    const int* ptr2{};
};

pair minmax_element(const int* first, const int* last)
{
    const int * min{first};
    const int * max{first};
    for (++first; first != last; ++first)
    {
        if (*first < *min)
        {
            min = first;
        }
        else if (*first >= *max)
        {
            max = first;
        }
    }

    return {min, max};
}

struct Person
{
    char name[52];
    unsigned id;
    unsigned age;
};

using Comparator = bool(*)(const Person&, const Person&);

void print_person(const Person& p, std::ostream& out)
{
    out << p.id << ' ' << p.age << ' ' << p.name << '\n';
}

void print_people(const Person* first, const Person* last, std::ostream& out)
{
    for (; first != last; ++first)
    {
        print_person(*first, out);
    }
}

Person* min_element(Person* first, Person* last, Comparator cmp)
{
    Person* min{first};
    for (++first; first != last; ++first)
    {
        if (cmp(*first, *min))
        {
            min = first;
        }
    }

   return min;
}

void selection_sort(Person* first, Person* last, Comparator cmp)
{
    for (; first != last; ++first)
    {
        std::iter_swap(first, min_element(first, last, cmp));
    }
}

bool compare_ids(const Person& lhs, const Person& rhs)
{
    return lhs.id < rhs.id;
}

bool compare_names(const Person& lhs, const Person& rhs)
{
    return strcmp(lhs.name, rhs.name) < 0;
}


void input_person(Person& p, std::istream& in)
{
    in >> p.id >> p.age;
    in.ignore();
    in.getline(p.name, 51);
}

void input_people(Person* first, Person* last, std::istream& in)
{
    for (; first != last; ++first)
    {
        input_person(*first, in);
    }
}

void people_to_bin(const Person* first, const Person* last, std::ostream& out)
{
    out.write(reinterpret_cast<const char*>(first), (last - first) * sizeof(Person));
}

int main()
{
    Person people[]{
        {"Pe6o", 2, 30},
        {"Go6o", 0, 20},
        {"To6o", 1, 10},
        {"Az", 10, 10}
    };

    std::ofstream bin{"people.bin", std::ios::binary};

    people_to_bin(people, std::cend(people), bin);

    return 0;
}
