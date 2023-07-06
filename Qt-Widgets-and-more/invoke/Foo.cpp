#include "Foo.h"

std::ostream &operator<<(std::ostream &os, const Foo &foo)
{
    os << "{" << foo.first << "," << foo.second << "}";
    return os;
}

std::ostream &operator<<(std::ostream &os, const std::vector<Foo> &foos)
{
    os << "[ ";

    bool first = true;
    for (const Foo &foo : foos) {
        if (first)
            first = false;
        else
            os << ", ";
        os << foo;
    }
    os << " ]";
    return os;
}

std::ostream &operator<<(std::ostream &os, const std::vector<Foo *> &foos)
{
    os << "[ ";

    bool first = true;
    for (const Foo *foo : foos) {
        if (first)
            first = false;
        else
            os << ", ";
        os << *foo;
    }
    os << " ]";
    return os;
}

void print(const std::string &title, const std::vector<Foo> &foos)
{
    std::cout << title << ": " << foos << std::endl;
}

void print(const std::string &title, const std::vector<Foo *> &foos)
{
    std::cout << title << ": " << foos << std::endl;
}
