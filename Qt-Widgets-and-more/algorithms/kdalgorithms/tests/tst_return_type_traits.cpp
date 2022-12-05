#include "../src/bits/return_type_trait.h"
#include <functional>
#include <string>
#include <type_traits>
#include <vector>

using namespace kdalgorithms::traits;

class TestReturnTypeTraits
{
    void lambda();
    void globalFunction();
    void operatorOnObject();
    void operatorOnConstObject();
    void pointerToMemberFunction();
    void voidFunction();
    void stdFunction();
    void referenceToT(const std::function<bool()> &function);
};

void TestReturnTypeTraits::lambda()
{
    auto fn = [] { return 10; };
    static_assert(std::is_same<return_type_of_t<decltype(fn)>, int>::value, "");
}

std::string function(int x, const std::string &y)
{
    (void)x;
    (void)y;
    return "Hello World";
}

void TestReturnTypeTraits::globalFunction()
{
    (void)function;
    static_assert(std::is_same<return_type_of_t<decltype(function)>, std::string>::value, "");
}

struct C1
{
    std::vector<int> operator()(bool) { return {}; };
};

void TestReturnTypeTraits::operatorOnObject()
{
    static_assert(std::is_same<return_type_of_t<decltype(C1())>, std::vector<int>>::value, "");
}

struct C2
{
    char operator()(const std::vector<int> &) const { return {}; };
};

void TestReturnTypeTraits::operatorOnConstObject()
{
    static_assert(std::is_same<return_type_of_t<decltype(C2())>, char>::value, "");
}

struct C3
{
    bool getBool() const;
};

void TestReturnTypeTraits::pointerToMemberFunction()
{
    static_assert(std::is_same<return_type_of_t<decltype(&C3::getBool)>, bool>::value, "");
}

void TestReturnTypeTraits::voidFunction()
{
    static_assert(std::is_same<return_type_of_t<void()>, void>::value, "");
}

void TestReturnTypeTraits::stdFunction()
{
    static_assert(std::is_same<return_type_of_t<std::function<bool(int)>>, bool>::value, "");

    const std::function<bool(int)> fn;
    static_assert(std::is_same<return_type_of_t<decltype(fn)>, bool>::value, "");
}

void TestReturnTypeTraits::referenceToT(const std::function<bool()> &function)
{
    (void)function;
    static_assert(std::is_same<return_type_of_t<std::function<bool()> &>, bool>::value, "");
    static_assert(std::is_same<return_type_of_t<decltype(function)>, bool>::value, "");
}

// All testing in here is done at compile time
int main()
{
    return 0;
}
