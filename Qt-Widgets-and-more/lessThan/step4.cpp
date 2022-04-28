#include <iostream>
#include <tuple>

namespace {
class Foo
{
public:
    explicit Foo() { }
    explicit Foo(int i)
        : m_isValid(true)
        , m_value(i)
    {
    }

    friend bool operator<(const Foo &lhs, const Foo &rhs)
    {
        if (!lhs.m_isValid)
            return rhs.m_isValid;
        if (!rhs.m_isValid)
            return false;
        return lhs.m_value < rhs.m_value;
    }

private:
    bool m_isValid = false;
    int m_value;
};
}

void go4()
{
#define compare(x, expected)                                                                       \
    std::cout << #x << ": " << (((x) == expected) ? "Correct" : "Oops") << std::endl
    std::cout << "==== Step 4 ======\n";
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
