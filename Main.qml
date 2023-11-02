import QtQuick
import QtQuick.Window
import QtQuick.Controls

Window {
    property string currentView: "CategoryList.qml"

    width: 960
    height: 480
    visible: true
    title: qsTr("Hello World")

    Rectangle {
        width: 250
        height: parent.height
        color: "#dedede"

        Column {
            anchors.fill: parent
            Repeater {

                model: ListModel {
                    ListElement {
                        name: "Buku"
                        view: "BookList.qml"
                    }
                    ListElement {
                        name: "Kategori"
                        view: "CategoryList.qml"
                    }
                    ListElement{
                        name : "Penerbit"
                        view : "PenerbitList.qml"
                    }
                    ListElement{
                        name : "Member"
                        view : "MemberList.qml"
                    }
                    ListElement {
                        name: "Pengadaan Buku"
                        view: "PengadaanList.qml"
                    }
                }

                delegate: Rectangle {
                    height: row.height
                    width: parent.width
                    color: "#dedede"

                    MouseArea {
                        anchors.fill: parent
                        onClicked: currentView = view
                    }

                    Column {
                        width: parent.width
                        id: row
                        padding: 16

                        Text {
                            text: name
                        }
                    }
                }
            }
        }
    }

    Loader {
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        anchors.leftMargin: 250

        source: currentView
    }
}
