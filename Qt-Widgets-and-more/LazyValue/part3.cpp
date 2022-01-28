#include "shared.h"

template <typename Calculator>
class LazyValue
{
    using ValueType = decltype(std::declval<Calculator>()());

public:
    LazyValue(Calculator calculator)
        : m_calculator(calculator){};

    ValueType operator()()
    {
        if (!m_calculated)
            m_value = m_calculator();
        m_calculated = true;
        return m_value;
    }

private:
    Calculator m_calculator;
    bool m_calculated = false;
    ValueType m_value = {};
};

int part3()
{
    LazyValue x([] { return calculate(42); });
    LazyValue y = [] { return calculate(10); };

    int z = 0;

    if (cond1())
        z = x();
    else
        z = y();

    if (cond2())
        return z + x();
    else
        return z + y();
}
