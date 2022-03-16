#ifndef JSS_STRONG_TYPEDEF_HPP
#define JSS_STRONG_TYPEDEF_HPP
#include <functional>
#include <ostream>
#include <type_traits>
#include <utility>

namespace jss {
/// Internal implementation namespace
namespace detail {
    /// A small type used for operation tests
    using small_result = char;
    /// A large type with a different size to the small type, used for
    /// operation tests
    struct large_result
    {
        small_result dummy[2];
    };

} // namespace detail

/// The strong_typedef template used to create unique types with
/// specific properties.
///
/// Tag is a tag type used for uniqueness. It can be incomplete as
/// it is never used for anything except creating unique template
/// instantiations
///
/// ValueType is the type this Strong typedef is based on: it is the type of
/// the underlying value
///
/// Properties are types that provide mixins that enable certain operations
/// on values of this type.
template <typename Tag, typename ValueType, typename... Properties>
class strong_typedef
    : public Properties::template mixin<strong_typedef<Tag, ValueType, Properties...>, ValueType>...
{
public:
    /// The underlying value type
    using underlying_value_type = ValueType;

    /// A default constructed strong_typedef has a default-constructed value
    constexpr strong_typedef() noexcept
        : value()
    {
    }

    /// Construct a strong_typedef holding the specified value
    explicit constexpr strong_typedef(ValueType value_) noexcept(
        std::is_nothrow_move_constructible<ValueType>::value)
        : value(std::move(value_))
    {
    }

    /// Explicit conversion operator to read the underlying value
    explicit constexpr operator ValueType const &() const noexcept { return value; }

    /// Get a const reference to the underlying value
    constexpr ValueType const &underlying_value() const noexcept { return value; }

    /// Get a reference to the underlying value
    constexpr ValueType &underlying_value() noexcept { return value; }

    /// Get a reference to the underlying value
    friend constexpr ValueType &underlying_value(strong_typedef &t) { return t.underlying_value(); }

    /// Get a const reference to the underlying value
    friend constexpr ValueType const &underlying_value(strong_typedef const &t)
    {
        return t.underlying_value();
    }

    /// Get a const rvalue reference to the underlying value
    friend constexpr ValueType &&underlying_value(strong_typedef &&t)
    {
        return std::move(t.underlying_value());
    }

    /// Get an rvalue reference to the underlying value
    friend constexpr ValueType const &&underlying_value(strong_typedef const &&t)
    {
        return std::move(t.underlying_value());
    }

private:
    /// The underlying value
    ValueType value;
};

/// The underlying value of a value that is not a strong_typedef is just
/// that value
template <typename T>
constexpr T &&underlying_value(T &&t)
{
    return std::forward<T>(t);
}

/// Namespace to wrap the property types
namespace strong_typedef_properties {
    /// Add operator== and operator!= to the strong_typedef
    struct equality_comparable
    {
        template <typename Derived, typename ValueType>
        struct mixin
        {
            friend constexpr bool operator==(Derived const &lhs, Derived const &rhs) noexcept(
                noexcept(std::declval<ValueType const &>() == std::declval<ValueType const &>()))
            {
                return lhs.underlying_value() == rhs.underlying_value();
            }
            friend constexpr bool operator!=(Derived const &lhs, Derived const &rhs) noexcept(
                noexcept(std::declval<ValueType const &>() != std::declval<ValueType const &>()))
            {
                return lhs.underlying_value() != rhs.underlying_value();
            }
        };
    };

    /// Add the preincrement operator to the strong_typedef
    struct pre_incrementable
    {
        template <typename Derived, typename ValueType>
        struct mixin
        {
            friend Derived &
            operator++(Derived &self) noexcept(noexcept(++std::declval<ValueType &>()))
            {
                ++self.underlying_value();
                return self;
            }
        };
    };

    /// Add the post-increment operator to the strong_typedef
    struct post_incrementable
    {
        template <typename Derived, typename ValueType>
        struct mixin
        {
            friend Derived operator++(Derived &self,
                                      int) noexcept(noexcept(std::declval<ValueType &>()++))
            {
                return Derived{self.underlying_value()++};
            }
        };
    };

    /// Add both pre- and post-increment operators to the strong_typedef
    struct incrementable
    {
        template <typename Derived, typename ValueType>
        struct mixin : pre_incrementable::mixin<Derived, ValueType>,
                       post_incrementable::mixin<Derived, ValueType>
        {
        };
    };

    /// Add the pre-decrement operator to the strong_typedef
    struct pre_decrementable
    {
        template <typename Derived, typename ValueType>
        struct mixin
        {
            friend Derived &
            operator--(Derived &self) noexcept(noexcept(--std::declval<ValueType &>()))
            {
                --self.underlying_value();
                return self;
            }
        };
    };

    /// Add the post-decrement operator to the strong_typedef
    struct post_decrementable
    {
        template <typename Derived, typename ValueType>
        struct mixin
        {
            friend Derived operator--(Derived &self,
                                      int) noexcept(noexcept(std::declval<ValueType &>()--))
            {
                return Derived{self.underlying_value()--};
            }
        };
    };

    /// Add both pre- and post-decrement operators to the strong_typedef
    struct decrementable
    {
        template <typename Derived, typename ValueType>
        struct mixin : pre_decrementable::mixin<Derived, ValueType>,
                       post_decrementable::mixin<Derived, ValueType>
        {
        };
    };

    /// Add operator+ that supports adding the strong_typedef to anything
    /// the underlying value can be added to
    struct generic_mixed_addable
    {
        template <typename Derived, typename ValueType>
        struct mixin
        {
            template <typename Rhs>
            friend typename std::enable_if<
                !std::is_same<Rhs, Derived>::value
                    && std::is_convertible<
                        decltype(std::declval<ValueType const &>()
                                 + underlying_value(std::declval<Rhs const &>())),
                        ValueType>::value,
                Derived>::type
            operator+(Derived const &lhs, Rhs const &rhs) noexcept(noexcept(
                std::declval<ValueType const &>() + underlying_value(std::declval<Rhs const &>())))
            {
                return Derived{lhs.underlying_value() + underlying_value(rhs)};
            }

            template <typename Lhs>
            friend typename std::enable_if<
                !std::is_same<Lhs, Derived>::value
                    && std::is_convertible<decltype(underlying_value(std::declval<Lhs const &>())
                                                    + std::declval<ValueType const &>()),
                                           ValueType>::value,
                Derived>::type
            operator+(Lhs const &lhs, Derived const &rhs) noexcept(noexcept(
                underlying_value(std::declval<Lhs const &>()) + std::declval<ValueType const &>()))
            {
                return Derived{underlying_value(lhs) + rhs.underlying_value()};
            }
        };
    };
#define JSS_COMPOUND_ASSIGN(op_symbol) op_symbol## =

#define JSS_DEFINE_OP_MIXINS(name, op_symbol)                                                      \
    /** Add operator op_symbol to the strong_typedef **/                                           \
    template <typename Other>                                                                      \
    struct mixed_##name                                                                            \
    {                                                                                              \
        template <typename Derived, typename ValueType,                                            \
                  bool = std::is_literal_type<ValueType>::value>                                   \
        struct mixin                                                                               \
        {                                                                                          \
            friend constexpr Derived                                                               \
            operator op_symbol(Derived const &lhs, Other const &rhs) noexcept(                     \
                noexcept(std::declval<ValueType const &>()                                         \
                             op_symbol underlying_value(std::declval<Other const &>())))           \
            {                                                                                      \
                return Derived{lhs.underlying_value() op_symbol underlying_value(rhs)};            \
            }                                                                                      \
                                                                                                   \
            friend constexpr Derived                                                               \
            operator op_symbol(Other const &lhs, Derived const &rhs) noexcept(                     \
                noexcept(underlying_value(std::declval<Other const &>())                           \
                             op_symbol std::declval<ValueType const &>()))                         \
            {                                                                                      \
                return Derived{underlying_value(lhs) op_symbol rhs.underlying_value()};            \
            }                                                                                      \
                                                                                                   \
            friend Derived &                                                                       \
            operator JSS_COMPOUND_ASSIGN(op_symbol)(Derived &lhs, Other const &rhs) noexcept(      \
                noexcept(std::declval<ValueType &>() JSS_COMPOUND_ASSIGN(op_symbol)                \
                             underlying_value(std::declval<Other const &>())))                     \
            {                                                                                      \
                lhs.underlying_value() JSS_COMPOUND_ASSIGN(op_symbol) underlying_value(rhs);       \
                return lhs;                                                                        \
            }                                                                                      \
        };                                                                                         \
    };                                                                                             \
    template <typename Other>                                                                      \
    template <typename Derived, typename ValueType>                                                \
    struct mixed_##name<Other>::mixin<Derived, ValueType, false>                                   \
    {                                                                                              \
        friend Derived operator op_symbol(Derived const &lhs, Other const &rhs) noexcept(          \
            noexcept(std::declval<ValueType const &>()                                             \
                         op_symbol underlying_value(std::declval<Other const &>())))               \
        {                                                                                          \
            return Derived{lhs.underlying_value() op_symbol underlying_value(rhs)};                \
        }                                                                                          \
                                                                                                   \
        friend Derived operator op_symbol(Other const &lhs, Derived const &rhs) noexcept(          \
            noexcept(underlying_value(std::declval<Other const &>())                               \
                         op_symbol std::declval<ValueType const &>()))                             \
        {                                                                                          \
            return Derived{underlying_value(lhs) op_symbol rhs.underlying_value()};                \
        }                                                                                          \
                                                                                                   \
        friend Derived &                                                                           \
        operator JSS_COMPOUND_ASSIGN(op_symbol)(Derived &lhs, Other const &rhs) noexcept(          \
            noexcept(std::declval<ValueType &>() JSS_COMPOUND_ASSIGN(op_symbol)                    \
                         underlying_value(std::declval<Other const &>())))                         \
        {                                                                                          \
            lhs.underlying_value() JSS_COMPOUND_ASSIGN(op_symbol) underlying_value(rhs);           \
            return lhs;                                                                            \
        }                                                                                          \
    };                                                                                             \
    struct self_##name                                                                             \
    {                                                                                              \
        template <typename Derived, typename ValueType,                                            \
                  bool = std::is_literal_type<ValueType>::value>                                   \
        struct mixin                                                                               \
        {                                                                                          \
            friend constexpr Derived                                                               \
            operator op_symbol(Derived const &lhs, Derived const &rhs) noexcept(noexcept(          \
                std::declval<ValueType const &>() op_symbol std::declval<ValueType const &>()))    \
            {                                                                                      \
                return Derived{lhs.underlying_value() op_symbol rhs.underlying_value()};           \
            }                                                                                      \
            friend Derived &                                                                       \
            operator JSS_COMPOUND_ASSIGN(op_symbol)(Derived &lhs, Derived const &rhs) noexcept(    \
                noexcept(std::declval<ValueType &>() JSS_COMPOUND_ASSIGN(op_symbol)                \
                             std::declval<ValueType const &>()))                                   \
            {                                                                                      \
                lhs.underlying_value() JSS_COMPOUND_ASSIGN(op_symbol) rhs.underlying_value();      \
                return lhs;                                                                        \
            }                                                                                      \
        };                                                                                         \
    };                                                                                             \
                                                                                                   \
    template <typename Derived, typename ValueType>                                                \
    struct self_##name::mixin<Derived, ValueType, false>                                           \
    {                                                                                              \
        friend Derived operator op_symbol(Derived const &lhs, Derived const &rhs) noexcept(        \
            noexcept(std::declval<ValueType const &>()                                             \
                         op_symbol std::declval<ValueType const &>()))                             \
        {                                                                                          \
            return Derived{lhs.underlying_value() op_symbol rhs.underlying_value()};               \
        }                                                                                          \
        friend Derived &                                                                           \
        operator JSS_COMPOUND_ASSIGN(op_symbol)(Derived &lhs, Derived const &rhs) noexcept(        \
            noexcept(std::declval<ValueType &>() JSS_COMPOUND_ASSIGN(op_symbol)                    \
                         std::declval<ValueType const &>()))                                       \
        {                                                                                          \
            lhs.underlying_value() JSS_COMPOUND_ASSIGN(op_symbol) rhs.underlying_value();          \
            return lhs;                                                                            \
        }                                                                                          \
    };                                                                                             \
    struct name                                                                                    \
    {                                                                                              \
        template <typename Derived, typename ValueType>                                            \
        struct mixin : self_##name::mixin<Derived, ValueType>,                                     \
                       mixed_##name<ValueType>::template mixin<Derived, ValueType>                 \
        {                                                                                          \
        };                                                                                         \
    };

    /// Define mixins for the built-in operators
    ///
    /// self_xxx provides the operation where both LHS and RHS are
    /// the strong_typedef
    ///
    /// mixed_xxx<Other> provides the operation where only the LHS or RHS
    /// is the strong_typedef and the other operand is of type Other
    ///
    /// xxx combines self_xxx and mixed_xxx<underlying_value_type>
    ///
    JSS_DEFINE_OP_MIXINS(addable, +)
    JSS_DEFINE_OP_MIXINS(subtractable, -)
    JSS_DEFINE_OP_MIXINS(multiplicable, *)
    JSS_DEFINE_OP_MIXINS(divisible, /)
    JSS_DEFINE_OP_MIXINS(modulus, %)
    JSS_DEFINE_OP_MIXINS(bitwise_or, |)
    JSS_DEFINE_OP_MIXINS(bitwise_and, &)
    JSS_DEFINE_OP_MIXINS(bitwise_xor, ^)

    /// Allow subtraction with any type that can be subtracted from the
    /// underlying value, or the underlying value can be subtracted from
    struct generic_mixed_subtractable
    {
        template <typename Derived, typename ValueType>
        struct mixin
        {
            template <typename Rhs>
            friend typename std::enable_if<
                !std::is_same<Rhs, Derived>::value
                    && std::is_convertible<
                        decltype(std::declval<ValueType const &>()
                                 - underlying_value(std::declval<Rhs const &>())),
                        ValueType>::value,
                Derived>::type
            operator-(Derived const &lhs, Rhs const &rhs) noexcept(noexcept(
                std::declval<ValueType const &>() - underlying_value(std::declval<Rhs const &>())))
            {
                return Derived{lhs.underlying_value() - underlying_value(rhs)};
            }

            template <typename Lhs>
            friend typename std::enable_if<
                !std::is_same<Lhs, Derived>::value
                    && std::is_convertible<decltype(underlying_value(std::declval<Lhs const &>())
                                                    - std::declval<ValueType const &>()),
                                           ValueType>::value,
                Derived>::type
            operator-(Lhs const &lhs, Derived const &rhs) noexcept(noexcept(
                underlying_value(std::declval<Lhs const &>()) - std::declval<ValueType const &>()))
            {
                return Derived{underlying_value(lhs) - rhs.underlying_value()};
            }
        };
    };

    /// Allow subtracting two strong_typedef instances to produce
    /// a DifferenceType value tha represents the difference
    template <typename DifferenceType>
    struct difference
    {
        template <typename Derived, typename ValueType>
        struct mixin
        {
            friend DifferenceType operator-(Derived const &lhs, Derived const &rhs) noexcept(
                noexcept(std::declval<ValueType const &>() - std::declval<ValueType const &>()))
            {
                return DifferenceType{lhs.underlying_value() - rhs.underlying_value()};
            }
        };
    };

    /// Add ordering comparison operators to the strong_typedef
    struct ordered
    {
        template <typename Derived, typename ValueType>
        struct mixin
        {
            friend constexpr bool operator<(Derived const &lhs, Derived const &rhs) noexcept(
                noexcept(std::declval<ValueType const &>() < std::declval<ValueType const &>()))
            {
                return lhs.underlying_value() < rhs.underlying_value();
            }
            friend constexpr bool operator>(Derived const &lhs, Derived const &rhs) noexcept(
                noexcept(std::declval<ValueType const &>() > std::declval<ValueType const &>()))
            {
                return lhs.underlying_value() > rhs.underlying_value();
            }
            friend constexpr bool operator<=(Derived const &lhs, Derived const &rhs) noexcept(
                noexcept(std::declval<ValueType const &>() <= std::declval<ValueType const &>()))
            {
                return lhs.underlying_value() <= rhs.underlying_value();
            }
            friend constexpr bool operator>=(Derived const &lhs, Derived const &rhs) noexcept(
                noexcept(std::declval<ValueType const &>() >= std::declval<ValueType const &>()))
            {
                return lhs.underlying_value() >= rhs.underlying_value();
            }
        };
    };

    /// Add ordering comparisons to the strong_typedef where the
    /// other operand is of type Other
    template <typename Other>
    struct mixed_ordered
    {
        template <typename Derived, typename ValueType>
        struct mixin
        {
            friend typename std::enable_if<
                !std::is_same<Other, Derived>::value
                    && std::is_convertible<
                        decltype(std::declval<ValueType const &>()
                                 < underlying_value(std::declval<Other const &>())),
                        bool>::value,
                bool>::type
            operator<(Derived const &lhs, Other const &rhs) noexcept(
                noexcept(std::declval<ValueType const &>()
                         < underlying_value(std::declval<Other const &>())))
            {
                return lhs.underlying_value() < underlying_value(rhs);
            }

            friend typename std::enable_if<
                !std::is_same<Other, Derived>::value
                    && std::is_convertible<decltype(underlying_value(std::declval<Other const &>())
                                                    < std::declval<ValueType const &>()),
                                           bool>::value,
                bool>::type
            operator<(Other const &lhs, Derived const &rhs) noexcept(
                noexcept(underlying_value(std::declval<Other const &>())
                         < std::declval<ValueType const &>()))
            {
                return underlying_value(lhs) < rhs.underlying_value();
            }

            friend typename std::enable_if<
                !std::is_same<Other, Derived>::value
                    && std::is_convertible<
                        decltype(std::declval<ValueType const &>()
                                 > underlying_value(std::declval<Other const &>())),
                        bool>::value,
                bool>::type
            operator>(Derived const &lhs, Other const &rhs) noexcept(
                noexcept(std::declval<ValueType const &>()
                         > underlying_value(std::declval<Other const &>())))
            {
                return lhs.underlying_value() > underlying_value(rhs);
            }

            friend typename std::enable_if<
                !std::is_same<Other, Derived>::value
                    && std::is_convertible<decltype(underlying_value(std::declval<Other const &>())
                                                    > std::declval<ValueType const &>()),
                                           bool>::value,
                bool>::type
            operator>(Other const &lhs, Derived const &rhs) noexcept(
                noexcept(underlying_value(std::declval<Other const &>())
                         > std::declval<ValueType const &>()))
            {
                return underlying_value(lhs) > rhs.underlying_value();
            }

            friend typename std::enable_if<
                !std::is_same<Other, Derived>::value
                    && std::is_convertible<
                        decltype(std::declval<ValueType const &>()
                                 >= underlying_value(std::declval<Other const &>())),
                        bool>::value,
                bool>::type
            operator>=(Derived const &lhs,
                       Other const &rhs) noexcept(noexcept(std::declval<ValueType const &>()
                                                           >= std::declval<Other const &>()))
            {
                return lhs.underlying_value() >= underlying_value(rhs);
            }

            friend typename std::enable_if<
                !std::is_same<Other, Derived>::value
                    && std::is_convertible<decltype(underlying_value(std::declval<Other const &>())
                                                    >= std::declval<ValueType const &>()),
                                           bool>::value,
                bool>::type
            operator>=(Other const &lhs, Derived const &rhs) noexcept(
                noexcept(underlying_value(std::declval<Other const &>())
                         >= std::declval<ValueType const &>()))
            {
                return underlying_value(lhs) >= rhs.underlying_value();
            }

            friend typename std::enable_if<
                !std::is_same<Other, Derived>::value
                    && std::is_convertible<
                        decltype(std::declval<ValueType const &>()
                                 <= underlying_value(std::declval<Other const &>())),
                        bool>::value,
                bool>::type
            operator<=(Derived const &lhs, Other const &rhs) noexcept(
                noexcept(std::declval<ValueType const &>()
                         <= underlying_value(std::declval<Other const &>())))
            {
                return lhs.underlying_value() <= underlying_value(rhs);
            }

            friend typename std::enable_if<
                !std::is_same<Other, Derived>::value
                    && std::is_convertible<decltype(underlying_value(std::declval<Other const &>())
                                                    <= std::declval<ValueType const &>()),
                                           bool>::value,
                bool>::type
            operator<=(Other const &lhs, Derived const &rhs) noexcept(
                noexcept(underlying_value(std::declval<Other const &>())
                         <= std::declval<ValueType const &>()))
            {
                return underlying_value(lhs) <= rhs.underlying_value();
            }
        };
    };

    /// Allow this strong_typedef to be used with std::hash
    struct hashable
    {
        struct base
        {
        };
        template <typename Derived, typename ValueType>
        struct mixin : base
        {
        };
    };

    /// Add a stream operator to write the strong_typedef to a std::ostream
    struct streamable
    {
        template <typename Derived, typename ValueType>
        struct mixin
        {
            friend std::ostream &operator<<(std::ostream &os, Derived const &st)
            {
                return os << st.underlying_value();
            }
        };
    };

    /// Combine ordered and equality_comparable
    struct comparable
    {
        template <typename Derived, typename ValueType>
        struct mixin : ordered::template mixin<Derived, ValueType>,
                       equality_comparable::template mixin<Derived, ValueType>
        {
        };
    };

    /// Add a division operation to the strong_typedef that
    /// produces a RatioType instances representing the result
    template <typename RatioType>
    struct ratio
    {
        template <typename Derived, typename ValueType>
        struct mixin
        {
            friend RatioType operator/(Derived const &lhs, Derived const &rhs) noexcept(
                noexcept(std::declval<ValueType const &>() / std::declval<ValueType const &>()))
            {
                return RatioType{lhs.underlying_value() / rhs.underlying_value()};
            }
        };
    };

    /// Add the bitwise not operator to the strong_typedef
    struct bitwise_not
    {
        template <typename Derived, typename ValueType,
                  bool = std::is_literal_type<ValueType>::value>
        struct mixin
        {
            friend constexpr Derived
            operator~(Derived const &lhs) noexcept(noexcept(~std::declval<ValueType const &>()))
            {
                return Derived{~lhs.underlying_value()};
            }
        };
    };

    template <typename Derived, typename ValueType>
    struct bitwise_not::mixin<Derived, ValueType, false>
    {
        friend Derived
        operator~(Derived const &lhs) noexcept(noexcept(~std::declval<ValueType const &>()))
        {
            return Derived{~lhs.underlying_value()};
        }
    };

    /// Add the bitwise left-shift operator to the strong_typedef
    template <typename Other>
    struct bitwise_left_shift
    {
        template <typename Derived, typename ValueType,
                  bool = std::is_literal_type<ValueType>::value>
        struct mixin
        {
            friend constexpr Derived operator<<(Derived const &lhs, Other const &rhs) noexcept(
                noexcept(std::declval<ValueType const &>()
                         << underlying_value(std::declval<Other const &>())))
            {
                return Derived{lhs.underlying_value() << underlying_value(rhs)};
            }
            friend Derived &operator<<=(Derived &lhs, Other const &rhs) noexcept(noexcept(
                std::declval<ValueType &>() <<= underlying_value(std::declval<Other const &>())))
            {
                lhs.underlying_value() <<= underlying_value(rhs);
                return lhs;
            }
        };
    };

    template <typename Other>
    template <typename Derived, typename ValueType>
    struct bitwise_left_shift<Other>::mixin<Derived, ValueType, false>
    {
        friend Derived operator<<(Derived const &lhs, Other const &rhs) noexcept(noexcept(
            std::declval<ValueType const &>() << underlying_value(std::declval<Other const &>())))
        {
            return Derived{lhs.underlying_value() << underlying_value(rhs)};
        }
        friend Derived &operator<<=(Derived &lhs, Other const &rhs) noexcept(noexcept(
            std::declval<ValueType &>() <<= underlying_value(std::declval<Other const &>())))
        {
            lhs.underlying_value() <<= underlying_value(rhs);
            return lhs;
        }
    };

    /// Add the bitwise right-shift operator to the strong_typedef
    template <typename Other>
    struct bitwise_right_shift
    {
        template <typename Derived, typename ValueType,
                  bool = std::is_literal_type<ValueType>::value>
        struct mixin
        {
            friend constexpr Derived operator>>(Derived const &lhs, Other const &rhs) noexcept(
                noexcept(std::declval<ValueType const &>()
                         >> underlying_value(std::declval<Other const &>())))
            {
                return Derived{lhs.underlying_value() >> underlying_value(rhs)};
            }
            friend Derived &operator>>=(Derived &lhs, Other const &rhs) noexcept(noexcept(
                std::declval<ValueType &>() >>= underlying_value(std::declval<Other const &>())))
            {
                lhs.underlying_value() >>= underlying_value(rhs);
                return lhs;
            }
        };
    };

    template <typename Other>
    template <typename Derived, typename ValueType>
    struct bitwise_right_shift<Other>::mixin<Derived, ValueType, false>
    {
        friend Derived operator>>(Derived const &lhs, Other const &rhs) noexcept(noexcept(
            std::declval<ValueType const &>() >> underlying_value(std::declval<Other const &>())))
        {
            return Derived{lhs.underlying_value() >> underlying_value(rhs)};
        }
        friend Derived &operator>>=(Derived &lhs, Other const &rhs) noexcept(noexcept(
            std::declval<ValueType &>() >>= underlying_value(std::declval<Other const &>())))
        {
            lhs.underlying_value() >>= underlying_value(rhs);
            return lhs;
        }
    };

} // namespace strong_typedef_properties
} // namespace jss

namespace std {
/// A specialization of std::hash for those instances of strong_typedef that
/// have the hashable property
template <typename Tag, typename ValueType, typename... Properties>
struct hash<jss::strong_typedef<Tag, ValueType, Properties...>>
{
    template <typename Arg>
    typename std::enable_if<
        std::is_same<Arg, jss::strong_typedef<Tag, ValueType, Properties...>>::value
            && std::is_base_of<jss::strong_typedef_properties::hashable::base, Arg>::value,
        size_t>::type
    operator()(Arg const &arg) const
        noexcept(noexcept(std::hash<ValueType>()(std::declval<ValueType const &>())))
    {
        return std::hash<ValueType>()(arg.underlying_value());
    }
};

} // namespace std

#endif
