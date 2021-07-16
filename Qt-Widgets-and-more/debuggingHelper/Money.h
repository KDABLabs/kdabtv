#pragma once

class QString;

class Money
{
public:
    enum Currency { EUR, USD };
    Money() = default;
    Money(Currency currency, double amount);

    Currency currency() const;
    double amount() const;

    QString toString() const;

private:
    bool m_valid = false;
    Currency m_currency = EUR;
    double m_amount = 0;
};
