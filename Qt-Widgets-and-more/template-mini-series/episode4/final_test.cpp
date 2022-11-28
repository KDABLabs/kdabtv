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
#include <list>
#include <type_traits>
#include <vector>

using namespace std;

namespace {

template <typename InputContainer, typename ResultContainer>
inline constexpr bool myCheckV1 =
    std::is_same_v<InputContainer, ResultContainer> &&std::is_rvalue_reference_v<InputContainer>;

template <typename InputContainer, typename ResultContainer>
inline constexpr bool myCheckV2 =
    std::is_same_v<std::remove_reference_t<InputContainer>, ResultContainer>
        &&std::is_rvalue_reference_v<InputContainer>;

// Cpp 17
template <typename InputContainer, typename ResultContainer>
inline constexpr bool myCheckV3 =
    std::conjunction_v<std::is_same<std::remove_reference_t<InputContainer>, ResultContainer>,
                       std::is_rvalue_reference<InputContainer>>;

template <typename ResultContainer, typename InputContainer>
void transform(InputContainer &&)
{
    cout << "transform: "
         << (std::conjunction_v<
                std::is_same<std::remove_reference_t<InputContainer>, ResultContainer>,
                std::is_rvalue_reference<InputContainer &&>>)
         << endl;
}
} // end namespace

void final_test()
{
    cout << "========== episode3 - final_test ==========\n";

    std::vector<int> vec1;
    std::vector<int> vec2;
    std::list<int> list;

    cout << "Check1: " << myCheckV1<decltype(std::move(vec1)), decltype(vec2)> << endl;
    cout << "Check2: " << myCheckV2<decltype(std::move(vec1)), decltype(vec2)> << endl;
    cout << "Check3: " << myCheckV2<decltype(vec1), decltype(vec2)> << endl;
    cout << "Check4: " << myCheckV2<decltype(std::move(vec1)), decltype(list)> << endl;
    cout << "Check6: " << myCheckV2<decltype(std::move(vec1)), decltype(vec2)> << endl;

    transform<std::vector<int>>(std::move(vec1));
}
