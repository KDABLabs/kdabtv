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

#include <cassert>
#include <iostream>
#include <optional>
#include <string>
#include <variant>

using namespace std;

namespace {

template <typename ValueType, typename ErrorType>
class Result
{
public:
    Result(const ValueType &value)
        : m_data(value)
    {
    }
    Result(const ErrorType &err)
        : m_data(err)
    {
    }

    bool hasValue() const { return m_data.index() == 0; }
    const ValueType &value() const { return std::get<0>(m_data); }
    const ErrorType &error() const { return std::get<1>(m_data); }

private:
    std::variant<ValueType, ErrorType> m_data;
};

template <typename ErrorType>
class Result<void, ErrorType>
{
public:
    Result() = default;
    Result(const ErrorType error)
        : m_error(error)
    {
    }

    bool hasError() const { return m_error.has_value(); }
    const ErrorType &error() const { return *m_error; }

private:
    std::optional<ErrorType> m_error;
};

// -----------------------------------------
using AgeResult = Result<int, string>;

AgeResult getAge(const string &who)
{
    if (who == "Jesper")
        return AgeResult(18);
    else if (who == "Jesper's Wife")
        return AgeResult("You don't ask a women of her name!");
    else
        return AgeResult("Unknown person");
}

// -----------------------------------------
enum Error { NoPermission, UnknownCommand }; // Defined somewhere else, which we cant edit
using ActionResult = Result<void, Error>;

ActionResult doAction(const string &action)
{
    if (action == "reformat text")
        return ActionResult();
    else if (action == "format c:")
        return ActionResult(NoPermission);
    else
        return ActionResult(UnknownCommand);
}
} // end namespace

void specialization_classes()
{
    cout << "========== episode2 - specialization classes ==========\n";
    AgeResult ageResult = getAge("Jesper");
    assert(ageResult.hasValue());
    cout << "Jesper's age: " << ageResult.value() << endl;

    ageResult = getAge("Linus Torvalds");
    assert(!ageResult.hasValue());
    cout << "We asked for Linus's age, but the answer was: " << ageResult.error() << endl;

    ActionResult actionResult = doAction("reformat text");
    assert(!actionResult.hasError());

    actionResult = doAction("format c:");
    assert(actionResult.hasError());
    assert(actionResult.error() == NoPermission);
}
