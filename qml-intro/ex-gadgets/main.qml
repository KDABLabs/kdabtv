/*************************************************************************
 *
 * Copyright (c) 2015-2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

import QtQuick 2.0

Item {
    width: text.width + 20
    height: text.height + 20

    Text {
        id: text
        anchors.centerIn: parent
        text: "Press Me!"
        MouseArea {
            anchors.fill: parent
            onClicked: {
                // Accessing a global gadget
                console.log("Global lookup: ", _santa);

                // Returning a gadget from C++
                var santa = _db.lookup("Fake Santa")
                console.log("Looking Fake Santa up in the db: ", santa)

                // Returning a gadget back to C++
                _db.addPerson(_db.makePerson("Jesper", 18))
                var jesper = _db.lookup("Jesper")
                console.log("Adding Jesper to the DB and looking him up: ", jesper)

                // Updating a gadget
                jesper.age = 44
                console.log("Updating the gadget on the QML side: ", jesper)

                // Only the value on the QML side has been updated, the object in C++ remains unchanged
                jesper = _db.lookup("Jesper")
                console.log("Still the DB is unchanged: ", jesper)
            }
        }
    }
}
