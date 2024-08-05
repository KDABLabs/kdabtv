/*************************************************************************
 *
 * Copyright (c) 2016-2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/
#include "customer.h"

#include <QVariant>

int main()
{
    Customer customer(Customer::Corporate, QDate(2528, 11, 21));

//--> slide
    customer.setAddress("Complaints Division, Sirius B, Sirius Tau System, Canis Major");
    const QVariant address = customer.property("address");

    const QVariant name(QString("Sirius Cybernetics Corporation"));
    customer.setProperty("name", name);

    Q_ASSERT(address.toString() == customer.getAddress());
    Q_ASSERT(customer.getName() == customer.property("name"));
//<-- slide

    Q_ASSERT(customer.getDateEstablished() == customer.property("dateEstablished"));
    Q_ASSERT(customer.getCustomerType() == customer.property("type"));
}
