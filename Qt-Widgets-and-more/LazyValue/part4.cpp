#include "shared.h"
#include <mutex>

template <typename Calculator>
class LazyValueV2
{
    using ValueType = decltype(std::declval<Calculator &>()());

public:
    LazyValueV2(Calculator calculator)
        : m_calculator(std::move(calculator)){};
    ValueType operator()() const
    {
        std::call_once(m_calculated, [this] { m_value = m_calculator(); });
        return m_value;
    }

private:
    const Calculator m_calculator;
    mutable std::once_flag m_calculated;
    mutable ValueType m_value = {};
};

template <typename Calculator>
LazyValueV2(Calculator) -> LazyValueV2<std::remove_cv_t<std::remove_reference_t<Calculator>>>;

int part4()
{
    const LazyValueV2 x([] { return calculate(42); });
    const LazyValueV2 y = [] { return calculate(10); };

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
