import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import my.id.levirs.books

RowLayout {
    BookListDetailModel {
        id: detailModel
    }

    BookListEditModel {
        id: editModel
    }

    BookListModel {
        id: listModel
    }

    Rectangle {
        Layout.fillHeight: true
        Layout.fillWidth: true
        ListView {
            anchors.fill: parent
            anchors.margins: 16
            anchors.bottomMargin: 64 + 16 + 16
            onCurrentItemChanged:  detailModel.bookId = model.getKodeByIndex(currentIndex)

            spacing: 8
            model: listModel

            delegate: Rectangle {
                property var listView: ListView.view
                width: ListView.view.width
                height: column.height

                border.color: "#dedede"
                border.width: 1
                radius: 16

                color: ListView.isCurrentItem ? "#efefef" : "#ffffff"

                MouseArea {
                    anchors.fill: parent
                    onClicked: parent.listView.currentIndex = index
                }

                Column {
                    id: column
                    width: parent.width
                    padding: 8

                    Text {
                        text: model.Kode
                    }

                    Text {
                        text: model.Judul
                    }

                    Text {
                        text: model.Pengarang
                    }

                    Text {
                        text: model.Penerbit
                    }
                }
            }
        }

        Rectangle {
            width: 64
            height: 64
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.rightMargin: 16
            anchors.bottomMargin: 16
            radius: 32
            color: "#bebebe"

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    editModel.setIsNew()
                    editDialog.open()
                }
            }

            Text {
                font.pixelSize: 48
                text: "+"
                anchors.centerIn: parent
            }
        }
    }

    Rectangle {
        border.color: "#dedede"
        border.width: 1
        radius: 16
        width: 300
        Layout.maximumWidth: 300
        Layout.fillHeight: true
        Layout.rightMargin: 16
        Layout.topMargin: 16
        Layout.bottomMargin: 16

        GridLayout {
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.margins: 16
            columns: 2
            columnSpacing: 16

            Text {
                Layout.columnSpan: 2
                text: "Detail Buku"
                font.pixelSize: 24
            }

            Text {
                text: "Kode"
            }

            Text {
                Layout.fillWidth: true
                text: detailModel.bookId
            }

            Text {
                text: "Judul"
            }

            Text {
                Layout.fillWidth: true
                text: detailModel.judul
            }

            Text {
                text: "Pengarang"
            }

            Text {
                Layout.fillWidth: true
                text: detailModel.penulis
            }

            Text {
                text: "Penerbit"
            }

            Text {
                Layout.fillWidth: true
                text: detailModel.namaPenerbit
            }

            Text {
                text: "Jumlah Buku"
            }

            Text {
                Layout.fillWidth: true
                text: detailModel.jumlahBuku
            }


            Rectangle {
                Layout.columnSpan: 2
                Layout.fillHeight: true
            }

            RowLayout {
                Layout.columnSpan: 2


                Button {
                    text: "Edit"
                    onClicked: {
                        editModel.bookId = detailModel.bookId
                        editDialog.open()
                    }
                }

                Button {
                    text: "Hapus"
                }
            }
        }
    }

    Dialog {
        id: editDialog
        parent: Overlay.overlay

        x: (parent.width - width) / 2
        y: (parent.height - height) / 2
        width: 400
        contentHeight: editDialogColumn.height

        modal: true
        title: "Edit Buku"
        standardButtons: Dialog.Ok | Dialog.Cancel

        onAccepted: {
            editModel.submit()
            listModel.refresh()
        }

        Flickable {
            id: editDialogFlickable
            anchors.fill: parent
            clip: true
            contentHeight: editDialogColumn.height

            ColumnLayout {
                id: editDialogColumn
                spacing: 8
                width: parent.width

                Label {
                    text: "Judul"
                }

                TextField {
                    Layout.fillWidth: true
                    text: editModel.judul
                    onTextChanged: editModel.judul = text
                }


                Label {
                    text: "Pengarang"
                }

                TextField {
                    Layout.fillWidth: true
                    text: editModel.penulis
                    onTextChanged: editModel.penulis = text
                }

                Label {
                    text: "Penerbit"
                }

                ComboBox {
                    Layout.fillWidth: true
                    model: editModel.penerbitList
                    currentIndex: editModel.penerbitIndex
                    onCurrentIndexChanged: editModel.penerbitIndex = currentIndex
                }


                Label {
                    text: "Jumlah Buku"
                }

                SpinBox {
                    Layout.fillWidth: true
                    value: editModel.jumlahBuku
                    onValueChanged: editModel.jumlahBuku = value
                }
            }
        }
    }
}
