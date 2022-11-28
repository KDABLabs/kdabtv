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
#include <memory>
#include <vector>
using namespace std;

namespace {

template <typename T>
class Stack
{
public:
    using item_type = T;
    void push(const T &t) { m_items.push_back(t); }
    void push(T &&t) { m_items.push_back(std::move(t)); }
    T pop()
    {
        auto item = std::move(m_items.back());
        m_items.pop_back();
        return item;
    }
    size_t size() const { return m_items.size(); }
    void printStack() const
    {
        bool first = true;
        cout << "Stack: [";
        for (const T &item : m_items) {
            if (!first)
                cout << ", ";
            first = false;
            cout << item;
        }
        cout << "]" << endl;
    }

private:
    std::vector<T> m_items;
};

struct Foo
{
    Foo(int x, int y)
        : x(x)
        , y(y)
    {
    }
    int x;
    int y;
};

template <typename T>
using UniqPtrStack = Stack<std::unique_ptr<T>>;

} // end namespace

void template_stack()
{
    cout << "========== episode1 - template stack ==========\n";
    Stack<int> intStack;
    intStack.push(1);
    intStack.push(2);
    int i = 3;
    intStack.push(i);
    intStack.printStack();
    cout << "intStack pop: " << intStack.pop() << endl;

    Stack<std::string> stringStack;
    stringStack.push("abc");
    stringStack.push("def");
    cout << "stringStack pop: " << stringStack.pop() << endl;

    Stack<Foo> fooStack;
    fooStack.push({1, 2});
    fooStack.push({3, 4});
    fooStack.push({5, 6});
    Foo foo = fooStack.pop();
    cout << "Foo: " << foo.x << "," << foo.y << endl;

    UniqPtrStack<Foo> fooPtrStack;
    fooPtrStack.push(make_unique<Foo>(1, 2));
    fooPtrStack.push(make_unique<Foo>(3, 4));
    fooPtrStack.push(make_unique<Foo>(5, 6));
    auto fooPtr = fooPtrStack.pop();
    cout << "Foo: " << fooPtr->x << "," << fooPtr->y << endl;

    // This doesn't work as Foo doesn't support operator<<
    //    fooStack.printStack();
}
