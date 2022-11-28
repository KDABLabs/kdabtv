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
#include <cassert>
#include <iostream>
using namespace std;

namespace {
template <typename T, size_t maxSize>
class Stack
{
public:
    using item_type = T;
    void push(T &&t)
    {
        assert(m_size < maxSize);
        m_items[m_size++] = std::move(t);
    }

    T pop()
    {
        assert(m_size > 0);
        m_size--;
        return m_items.at(m_size);
    }

    size_t size() const { return m_size; }

    void printStack()
    {
        cout << "Stack: [";
        for (size_t i = 0; i < m_size; ++i) {
            if (i != 0)
                cout << ", ";
            cout << m_items[i];
        }
        cout << "]" << endl;
    }

private:
    std::array<T, maxSize> m_items;
    size_t m_size = 0;
};

} // end namespace

void template_stackV2()
{
    cout << "========== episode1 - template stack V2 ==========\n";
    Stack<int, 5> intStack;
    intStack.push(1);
    intStack.push(2);
    intStack.printStack();
    cout << "intStack pop: " << intStack.pop() << endl;
}
