#include <algorithm>
#include <fstream>
#include <iostream>

struct Stud
{
    int id{0};
    char name[30]{};
};

void print_stud(const Stud& student)
{
    std::cout << student.id << ": " << student.name << '\n';
}

void print_studs(Stud* first, Stud * last)
{
    std::for_each(first, last,
                  [](const Stud& student){ print_stud(student); });
}

void sort_studs(Stud* first, Stud * last)
{
    std::sort(first, last,
              [](const Stud& lhs, const Stud& rhs) { return lhs.id < rhs.id; });
}

void input_studs(Stud* first, Stud* last)
{
    std::for_each(first, last,
                  [](Stud& student) { (std::cin >> student.id).getline(student.name, 29); });
}

void serialize_studs(const Stud* first, const Stud* last, const char* file_name)
{
    std::ofstream out{file_name, std::ios::binary};
    out.write(reinterpret_cast<const char*>(first), (last - first) * sizeof(Stud));
}

Stud get_stud_from_stream(std::istream& bin_stream, unsigned index)
{
    bin_stream.seekg(index * sizeof(Stud));
    Stud result{};
    bin_stream.read(reinterpret_cast<char*>(&result), sizeof(Stud));

    return result;
}

int main()
{
    Stud students[]{
        { 3, "Pe6o Pe6ov" },
        { 1, "Go6o Go6ov" },
        { 0, "Spartak Spartakov" },
        { 2, "Firstname Lastname" }
    };

    print_studs(std::begin(students), std::end(students));
    std::cout << '\n';

    sort_studs(std::begin(students), std::end(students));
    print_studs(std::begin(students), std::end(students));
    std::cout << '\n';

    serialize_studs(std::begin(students), std::end(students), "students.bin");
    std::ifstream in{"students.bin", std::ios::binary};
    print_stud(get_stud_from_stream(in, 2));
    std::cout << '\n';

    input_studs(std::begin(students), std::end(students));
    print_studs(std::begin(students), std::end(students));
    std::cout << '\n';

    return 0;
}
