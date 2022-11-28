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

#include <deque>
#include <iostream>
#include <vector>
using namespace std;

namespace {
template <typename ItemType, typename Container = std::vector<ItemType>>
class Stack
{
public:
    using item_type = ItemType;
    void push(const ItemType &t) { m_items.push_back(t); }
    ItemType pop()
    {
        auto item = m_items.back();
        m_items.pop_back();
        return item;
    }
    size_t size() const { return m_items.size(); }
    void printStack()
    {
        bool first = true;
        cout << "Stack: [";
        for (ItemType &item : m_items) {
            if (!first)
                cout << ", ";
            first = false;
            cout << item;
        }
        cout << "]" << endl;
    }

private:
    Container m_items;
};
} // end namespace

void stack_container_type()
{
    cout << "========== episode1 - stack container type ==========\n";
    Stack<int> intStack;
    intStack.push(1);
    intStack.push(2);
    intStack.printStack();
    cout << "intStack pop: " << intStack.pop() << endl;

    Stack<int, std::deque<int>> dequeStack;
    dequeStack.push(1);
    dequeStack.push(2);
    dequeStack.printStack();
    cout << "dequeStack pop: " << dequeStack.pop() << endl;

    // Ouch this is possible too....
    //    Stack<int, std::deque<string>> brokenStack;
    //    brokenStack.push(1);
}
