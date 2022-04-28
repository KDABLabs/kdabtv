#include <iostream>
#include <tuple>

namespace {
class Foo
{
public:
    explicit Foo() { }
    explicit Foo(int i)
        : m_isNull(false)
        , m_value(i)
    {
    }

    friend bool operator<(const Foo &lhs, const Foo &rhs)
    {

#define version 5
#if version == 1 // Error prone
        if (lhs.m_isNull)
            return !rhs.m_isNull;
        if (rhs.m_isNull)
            return false;
        return lhs.m_value < rhs.m_value;
#elif version == 2 // Incorrect
        return std::tie(lhs.m_isNull, lhs.m_value) < std::tie(rhs.m_isNull, rhs.m_value);
#elif version == 3 // Doesn't compile
        return std::tie(!lhs.m_isNull, lhs.m_value) < std::tie(!rhs.m_isNull, rhs.m_value);
#elif version == 4 // works, but hmmm
        return std::tie(rhs.m_isNull, lhs.m_value) < std::tie(lhs.m_isNull, rhs.m_value);
#elif version == 5 // works fine, but use std::tie when possible to avoid copying
        return std::tuple(!lhs.m_isNull, lhs.m_value) < std::tuple(!rhs.m_isNull, rhs.m_value);
#endif
    }

private:
    bool m_isNull = true;
    int m_value = 0;
};
}

void go6()
{
#define compare(x, expected)                                                                       \
    std::cout << #x << ": " << (((x) == expected) ? "Correct" : "Oops") << std::endl
    std::cout << "==== Step 6 ======\n";
    const Foo null1;
    const Foo null2;
    const Foo val1(10);
    const Foo val2(20);

    compare(null1 < null2, false);
    compare(null2 < null1, false);
    compare(null1 < val1, true);
    compare(val1 < null1, false);
    compare(val1 < val2, true);
    compare(val2 < val1, false);
}
