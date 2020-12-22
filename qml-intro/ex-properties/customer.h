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
    Q_PROPERTY(QString phone MEMBER m_phone NOTIFY phoneChanged)
    Q_PROPERTY(QDate dateEstablished READ getDateEstablished CONSTANT) // Read-only
    Q_PROPERTY(CustomerType type READ getCustomerType CONSTANT) // Read-only
//--> hide
    Q_PROPERTY(QString address READ getAddress WRITE setAddress)
//<-- hide
public:
    enum CustomerType {
        Corporate, Individual, Educational, Government
    };
    Q_ENUM(CustomerType)
//<-- slide
    Customer(CustomerType type, const QDate &dateEstablished, QObject* parent = nullptr);
//--> slide
    QString getName() const;
    void setName(const QString &name);

    QDate getDateEstablished() const;
    CustomerType getCustomerType() const;
//--> hide
    QString getAddress() const;
    void setAddress(const QString &address);
//<-- hide
signals:
    void nameChanged();
    void phoneChanged();
//--> hide
    void addressChanged();
//<-- hide
private:
    QString m_name;
    QString m_phone;
    QDate m_dateEstablished;
    CustomerType m_customerType;
//--> hide
    QString m_address;
//<-- hide
};
//<-- slide

#endif
