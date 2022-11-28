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

#include <algorithm>
#include <iostream>
#include <list>
#include <type_traits>
#include <vector>

using namespace std;

namespace {

template <typename InputContainer, typename ResultContainer>
inline constexpr bool items_can_be_moved_v =
    std::conjunction_v<std::is_same<std::remove_reference_t<InputContainer>, ResultContainer>,
                       std::is_rvalue_reference<InputContainer &&>>;

template <typename ResultContainer, typename InputContainer, typename Transform>
ResultContainer transform(InputContainer &&container, Transform &&transform)
{
    if constexpr (items_can_be_moved_v<InputContainer, ResultContainer>) {
        cout << "--- Doing an in-place transform --\n";
        std::transform(container.begin(), container.end(), container.begin(),
                       std::forward<Transform>(transform));
        return container;
    } else {
        cout << "--- creating a temporary for the result ---\n";
        ResultContainer result;
        std::transform(container.begin(), container.end(), std::back_inserter(result),
                       std::forward<Transform>(transform));
        return result;
    }
}
} // end namespace

void transform_cpp17()
{
    cout << "========== episode3 - transform_cpp17 ==========\n";

    {
        cout << "++++ Test 1 ++++\n";
        std::vector<int> vec{1, 2, 3, 4};
        auto square = [](int i) { return i * i; };
        const std::list<int> result = transform<std::list<int>>(vec, square);
        for (auto x : result)
            cout << x << ", ";
        cout << endl;
    }
    {
        cout << "++++ Test 2 ++++\n";
        std::vector<int> vec{1, 2, 3, 4};
        auto square = [](int i) { return i * i; };
        const auto result = transform<std::vector<int>>(vec, square);
        for (auto x : result)
            cout << x << ", ";
        cout << endl;
    }
    {
        cout << "++++ Test 3 ++++\n";
        std::vector<int> vec{1, 2, 3, 4};
        auto square = [](int i) { return i * i; };
        const auto result = transform<std::vector<int>>(std::move(vec), square);
        for (auto x : result)
            cout << x << ", ";
        cout << endl;
    }
}
