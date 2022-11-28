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

#include <array>
#include <iostream>
#include <vector>
using namespace std;

namespace {

template <typename T>
void mySort(std::vector<T> &items)
{
    cout << "Calling the default method\n";
    std::sort(items.begin(), items.end());
}

template <>
void mySort<char>(std::vector<char> &items)
{
    cout << "Calling the specialized method\n";
    std::array<int, 256> data{};
    for (char c : items) {
        data[c]++;
    }
    auto it = items.begin();
    for (int i = 0; i < 256; ++i) {
        for (int j = 0; j < data[i]; ++j) {
            *(it++) = (char)i;
        }
    }
}

} // end namespace

void specialization()
{
    cout << "========== episode2 - specialization ==========\n";
    std::vector<int> ints{1, 54, 2, 1, 42};
    mySort(ints);
    for (int i : ints)
        cout << i << ", ";
    cout << endl;

    std::vector<char> chars{'h', 'e', 'l', 'l', 'o'};
    mySort(chars);
    for (char c : chars)
        cout << c;
    cout << endl;
}
