/*************************************************************************
 *
 * Copyright (c) 2016-2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/
#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <QObject>
#include <QDate>

//--> slide
class Customer : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString address READ getAddress WRITE setAddress NOTIFY addressChanged)
    Q_PROPERTY(QString phone MEMBER m_phone NOTIFY phoneChanged)
    Q_PROPERTY(QDate dateEstablished READ getDateEstablished CONSTANT) // Read-only
    Q_PROPERTY(CustomerType type READ getCustomerType CONSTANT) // Read-only
public:
    enum CustomerType {Corporate, Individual, Educational, Government};
    Q_ENUM(CustomerType)

//--> hide
    Customer(CustomerType type, const QDate &dateEstablished, QObject* parent = nullptr);
//<-- hide
    QString getName() const;
    void setName(const QString &name);
    QString getAddress() const;
    void setAddress(const QString &address);
    QDate getDateEstablished() const;
    CustomerType getCustomerType() const;

signals:
    void nameChanged();
    void phoneChanged();
    void addressChanged();

private:
    QString m_name;
    QString m_phone;
    QDate m_dateEstablished;
    CustomerType m_customerType;
    QString m_address;
};
//<-- slide

#endif
