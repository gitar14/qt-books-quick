import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import my.id.levirs.books

Dialog {
    parent: Overlay.overlay
    anchors.centerIn: parent
    contentHeight: parent.height
    modal: true
    standardButtons: Dialog.Ok | Dialog.Cancel

    property BookListModel listModel
    property int selectedIndex: bukuListView.currentIndex

    ColumnLayout {
        anchors.fill: parent

        TextField {
            Layout.fillWidth: true
        }

        // TODO: Buat component reusable
        ListView {
            id: bukuListView
            Layout.fillHeight: true
            Layout.fillWidth: true

            spacing: 8
            model: listModel

            delegate: Rectangle {
                property var listView: ListView.view
                property var itemData: model
                width: ListView.view.width
                height: column1.height

                border.color: "#dedede"
                border.width: 1
                radius: 16

                color: ListView.isCurrentItem ? "#efefef" : "#ffffff"

                MouseArea {
                    anchors.fill: parent
                    onClicked: parent.listView.currentIndex = index
                }

                Column {
                    id: column1
                    width: parent.width
                    padding: 16

                    Text {
                        text: model.judul
                    }

                    Text {
                        text: model.penulis
                    }

                    Text {
                        text: model.kategori
                    }
                }
            }
        }
    }
}
