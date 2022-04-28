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

    friend std::strong_ordering operator<=>(const Foo &lhs, const Foo &rhs)
    {
#define version 2
#if version == 1
        return std::make_tuple(!lhs.m_isNull, lhs.m_value)
            <=> std::make_tuple(!rhs.m_isNull, rhs.m_value);
#elif version == 2
        if (!lhs.m_isNull && !rhs.m_isNull) // both valid objects
            return lhs.m_value <=> rhs.m_value;
        return !lhs.m_isNull <=> !rhs.m_isNull; // one or both invalid.
#endif
    }

    bool operator==(const Foo &other) const = default;

private:
    bool m_isNull = true;
    int m_value = 0;
};
}

void go7()
{
#define compare(x, expected)                                                                       \
    std::cout << #x << ": " << (((x) == expected) ? "Correct" : "Oops") << std::endl
    std::cout << "===== Step 7 =======\n";
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

    compare(null1 > null2, false);
    compare(null2 > null1, false);
    compare(null1 > val1, false);
    compare(val1 > null1, true);
    compare(val1 > val2, false);
    compare(val2 > val1, true);

    compare(null1 == null2, true);
    compare(null2 == null1, true);
    compare(null1 == val1, false);
    compare(val1 == null1, false);
    compare(val1 == val2, false);
    compare(val2 == val1, false);
    compare(val1 == val1, true);
}
