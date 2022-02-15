import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.12

ApplicationWindow {
    width: 640
    height: 480
    visible: true
    title: qsTr("Database")
    font.pointSize: 20

    GridLayout {
        anchors.fill: parent
        anchors.margins: 10
        columns: 2

        BusyIndicator {
            running: true
        }
        Tumbler {
            model: 100
        }


        RowLayout {
            Layout.columnSpan: 2
            Layout.fillWidth: true

            Button {
                text: "QtSql 5s query"
                onClicked: {
                    db.qsqlQuery()
                }
            }
            Button {
                text: "QtSql 5s query threaded"
                onClicked: {
                    db.qsqlQueryThread()
                }
            }
            Button {
                text: "ASql 5s query"
                onClicked: {
                    db.asqlQuery()
                }
            }
            Button {
                text: "Cancel ASql query"
                onClicked: {
                    db.cancelAsqlQuery()
                }
            }
        }

        RowLayout {
            Layout.columnSpan: 2
            Layout.fillWidth: true

            SpinBox {
                from: 0
                to: 10
                id: targetId
            }
            Button {
                text: "Migrate"
                onClicked: {
                    db.migrate(targetId.value)
                }
            }
            Button {
                text: "Count rows"
                onClicked: {
                    db.countRows()
                }
            }
        }

        ScrollView {
            Layout.columnSpan: 2
            Layout.fillWidth: true
            Layout.fillHeight: true
            id: view
            TextArea {
                id: textArea
            }
        }

        Button {
            text: "Clear Results"
            highlighted: true
            onClicked: {
                textArea.clear()
            }
        }

        Connections {
            target: db

            function onGotResult(rows) {
                console.debug("result: " + JSON.stringify(rows))
                textArea.append(JSON.stringify(rows) + "\n")
            }
        }
    }
}
