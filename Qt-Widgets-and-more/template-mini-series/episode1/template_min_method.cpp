/* MIT License

Copyright (C) 2022 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <iostream>
using namespace std;

namespace {
template <typename T>
const T &myMin(const T &x, const T &y)
{
    return x < y ? x : y;
}

class Test
{
public:
    Test(int x, int y)
        : x(x)
        , y(y)
    {
    }
    friend bool operator<(const Test &a, const Test &b)
    {
        if (a.x != b.x)
            return a.x < b.x;
        return a.y < b.y;
    }
    friend ostream &operator<<(ostream &os, const Test &t)
    {
        os << "Test(" << t.x << ", " << t.y << ")";
        return os;
    }

private:
    int x;
    int y;
};
} // end namespace

void template_min_method()
{
    std::cout << "========== episode1 - template min method ==========\n";
    std::cout << "integers " << myMin(1, 2) << endl;
    std::cout << "strings " << myMin(std::string("abc"), std::string("def")) << endl;
    std::cout << "classes " << myMin(Test(2, 5), Test(2, 4)) << endl;
}
