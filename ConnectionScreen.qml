import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material
import Kelompok7.Perpus

Item {
    property var selectedConnection
    property bool isRememberConnection: false

    Component.onCompleted: {
        selectedConnection = ConnectionManager.getRememberedConnection()

        if (selectedConnection == "mysql") {
            stackView.push(mysqlView);
        }

        if (selectedConnection.length > 0) {
            isRememberConnection = true
        }
    }

    Frame {
        id: frame
        anchors.centerIn: parent
        width: 384
        contentHeight: stackView.currentItem.implicitHeight
        clip: true
        background: CardBackground {

        }

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
                            name: "sqlite"
                            title: "SQLite Lokal"
                        }

                        ListElement {
                            name: "mysql"
                            title: "MySQL (File Lokal)"
                        }
                    }

                    CardDelegate {
                        Layout.fillWidth: true
                        text: title
                        highlighted: selectedConnection == name
                        onClicked: selectedConnection = name
                    }
                }

                CheckBox {
                    text: "Ingat pilihan saat ini"
                    checked: isRememberConnection
                    onCheckStateChanged: isRememberConnection = checked
                }

                Button {
                    Layout.alignment: Qt.AlignRight
                    text: "Pilih"
                    enabled: selectedConnection.length > 0
                    highlighted: true

                    onClicked: {
                        ConnectionManager.setRememberedConnection(isRememberConnection ? selectedConnection : "");
                        if (selectedConnection == "sqlite") {
                            ConnectionManager.openSqlite();
                        } else if (selectedConnection == "mysql") {
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
                property string host
                property int port
                property string database
                property string username
                property string password
                property bool isRemembered

                Component.onCompleted: {
                    host = ConnectionManager.getRememberedMySqlHost();
                    port = ConnectionManager.getRememberedMySqlPort();
                    database = ConnectionManager.getRememberedMySqlDatabase();
                    username = ConnectionManager.getRememberedMySqlUserName();
                    password = ConnectionManager.getRememberedMySqlPassword();
                    isRemembered = ConnectionManager.isMySqlConfigRemembered();
                }

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

                CheckBox {
                    text: "Simpan konfigurasi MySQL"
                    checked: mysqlLayout.isRemembered
                    onCheckedChanged: mysqlLayout.isRemembered = checked
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
                                       mysqlLayout.isRemembered,
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
