/*************************************************************************
 *
 * Copyright (c) 2016-2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/
#include "customer.h"

Customer::Customer(Customer::CustomerType type, const QDate &dateEstablished, QObject *parent)
    : QObject(parent),
      m_dateEstablished(dateEstablished),
      m_customerType(type)
{
}

QString Customer::getName() const
{
    return m_name;
}

void Customer::setName(const QString &name)
{
    if (name == m_name) return;

    m_name = name;
    emit nameChanged();
}

QString Customer::getAddress() const
{
    return m_address;
}

void Customer::setAddress(const QString &address)
{
    if (address == m_address) return;

    m_address = address;
    emit addressChanged();
}

Customer::CustomerType Customer::getCustomerType() const
{
    return m_customerType;
}

QDate Customer::getDateEstablished() const
{
    return m_dateEstablished;
}

