import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import my.id.levirs.books

RowLayout {
    id: categoryRoot
    property var currentItemData: kategoriGrid.currentItem ? kategoriGrid.currentItem.itemData : null
    property string currentKode: currentItemData ? currentItemData.kode : ""
    property string currentJenis: currentItemData ? currentItemData.jenis : ""

    KategoriModel {
        id: kategoriModel
    }

    Rectangle {
        Layout.fillWidth: true
        Layout.fillHeight: true

        Column {
            anchors.fill: parent
            padding: 16

            GridView {
                id: kategoriGrid
                width: Math.min(count, Math.floor((parent.width - parent.leftPadding - parent.rightPadding) / cellWidth)) * cellWidth
                anchors.horizontalCenter: parent.horizontalCenter
                height: parent.height
                cellWidth: 125
                cellHeight: 150

                model: kategoriModel

                delegate: Rectangle {
                    property var itemData: model
                    width: GridView.view.cellWidth - 8
                    height: GridView.view.cellHeight - 8

                    border.color: "#dedede"
                    border.width: 1
                    radius: 16
                    color: GridView.isCurrentItem ? "#efefef" : "#ffffff"

                    MouseArea {
                        anchors.fill: parent
                        onClicked: kategoriGrid.currentIndex = index
                    }

                    ColumnLayout {
                        anchors.fill: parent
                        anchors.margins: 16
                        spacing: 2

                        Rectangle {
                            Layout.fillHeight: true
                        }

                        Label {
                            text: model.jenis
                            Layout.alignment: Qt.AlignHCenter
                        }
                    }
                }
            }
        }

        RoundButton {
            anchors.right: parent.right
            anchors.bottom: parent.bottom

            anchors.bottomMargin: 16
            anchors.rightMargin: 16

            width: 64
            height: 64

            text: "+"

            font.pixelSize: 24

            onClicked: {
                editDialog.isNew = true
                editDialog.open()
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
            visible: currentItemData ? true : false

            Label {
                text: "Kode"
            }

            Label {
                Layout.fillWidth: true
                text: currentKode
            }

            Label {
                text: "Jenis"
            }

            Label {
                Layout.fillWidth: true
                text: currentJenis
            }

            Rectangle {
                Layout.fillHeight: true
                Layout.columnSpan: 2
            }

            RowLayout {
                Layout.columnSpan: 2

                Button {
                    text: "Edit"
                    onClicked: {
                        editDialog.isNew = false
                        editDialog.open()
                    }
                }

                Button {
                    text: "Hapus"
                    onClicked: {
                        kategoriModel.remove(currentKode)
                    }
                }
            }
        }

        Label {
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.margins: 16
            visible: currentItemData ? false : true

            text: "Tidak ada kategori yang terpilih"
        }
    }


    Dialog {
        id: editDialog
        parent: Overlay.overlay

        width: 400
        x: parent.width / 2 - width / 2
        y: parent.height / 2 - height / 2

        standardButtons: Dialog.Ok | Dialog.Cancel

        modal: true

        property bool isNew: false
        title: isNew ? "Kategori Baru" : "Edit Kategori"

        onAccepted: {
            if (isNew)
                kategoriModel.addNew(jenisTextField.text)
            else kategoriModel.edit(
                     currentKode,
                     jenisTextField.text
                )
            isNew = false
        }

        ColumnLayout {
            spacing: 8
            width: parent.width

            Label {
                text: "Nama"
            }

            TextField {
                id: jenisTextField
                Layout.fillWidth: true
                text: editDialog.isNew ? "" : currentJenis
            }
        }
    }
}
