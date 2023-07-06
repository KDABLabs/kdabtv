#pragma once

#include <iostream>
#include <vector>

struct Foo
{
    int first;
    int second;
    int go() const { return first * second; }
    double fraction() const { return 1.0 / first; }
    int go2(int z) const { return first * z; }
};

std::ostream &operator<<(std::ostream &os, const Foo &foo);
std::ostream &operator<<(std::ostream &os, const std::vector<Foo> &foos);
std::ostream &operator<<(std::ostream &os, const std::vector<Foo *> &foos);

void print(const std::string &title, const std::vector<Foo> &foos);
void print(const std::string &title, const std::vector<Foo *> &foos);
