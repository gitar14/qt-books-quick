import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Kelompok7.Perpus

Item {
    property var selectedIndex

    Frame {
        anchors.centerIn: parent
        width: 384
        contentHeight: stackView.currentItem.implicitHeight
        clip: true

        StackView {
            id: stackView
            anchors.fill: parent
            initialItem: selectView
        }

        Component {
            id: selectView

            ColumnLayout {

                Label {
                    font.pixelSize: 20
                    text: "Pilih Koneksi"
                    Layout.alignment: Qt.AlignHCenter
                    bottomPadding: 8
                }

                Repeater {
                    model: ListModel {
                        ListElement {
                            name: "SQLite Lokal"
                        }

                        ListElement {
                            name: "MySQL (File Lokal)"
                        }
                    }

                    CardDelegate {
                        Layout.fillWidth: true
                        text: name
                        highlighted: selectedIndex == index
                        onClicked: selectedIndex = index
                    }
                }

                CheckBox {
                    text: "Ingat pilihan saat ini"
                }

                Button {
                    Layout.alignment: Qt.AlignRight
                    text: "Pilih"
                    enabled: selectedIndex != null
                    highlighted: true

                    onClicked: {
                        if (selectedIndex == 0) {
                            ConnectionManager.openSqlite();
                        } else if (selectedIndex == 1) {
                            stackView.push(mysqlView)
                        }
                    }
                }
            }
        }

        Component {
            id: mysqlView

            ColumnLayout {
                id: mysqlLayout
                property string host: "localhost"
                property int port: 3306
                property string database: ""
                property string username: ""
                property string password: ""

                Label {
                    font.pixelSize: 20
                    text: "Koneksi MySQL"
                    Layout.alignment: Qt.AlignHCenter
                    bottomPadding: 8
                }

                GridLayout {
                    Layout.fillWidth: true
                    columns: 2

                    Label {
                        text: "Host"
                        Layout.fillWidth: true
                    }

                    Label {
                        text: "Port"
                    }

                    TextField {
                        Layout.fillWidth: true
                        text: mysqlLayout.host
                        onTextChanged: mysqlLayout.host = text
                    }

                    SpinBox {
                        value: mysqlLayout.port
                        onValueChanged: mysqlLayout.port = value
                        from: 0
                        to: 10000
                        editable: true
                    }
                }

                Label {
                    text: "Database"
                }

                TextField {
                    Layout.fillWidth: true
                    text: mysqlLayout.database
                    onTextChanged: mysqlLayout.database = text
                }

                Label {
                    text: "Username"
                }

                TextField {
                    Layout.fillWidth: true
                    text: mysqlLayout.username
                    onTextChanged: mysqlLayout.username = text
                }

                Label {
                    text: "Password"
                }

                TextField {
                    Layout.fillWidth: true
                    text: mysqlLayout.password
                    onTextChanged: mysqlLayout.password = text
                }

                RowLayout {
                   Layout.fillWidth: true

                   Button {
                       text: "Kembali"
                       onClicked: stackView.pop()
                   }

                   Item {
                       Layout.fillWidth: true
                   }

                   Button {
                       text: "Hubungkan"
                       highlighted: true

                       onClicked: {
                           ConnectionManager.openMySql(
                                       mysqlLayout.host,
                                       mysqlLayout.port,
                                       mysqlLayout.database,
                                       mysqlLayout.username,
                                       mysqlLayout.password
                            );
                       }
                   }
                }
            }
        }
    }
}
