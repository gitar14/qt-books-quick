import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Kelompok7.Perpus
import my.id.levirs.books

RowLayout {
    PengadaanBukuModel {
        id: pengadaanBukuModel
        kodePengadaan: pengadaanDetailFrame.detailKode
    }

    EditablePengadaanBukuModel {
        id: editablePengadaanBukuModel

        onItemsChanged: pengadaanBukuListModel.setIgnoredKodeList(kodeBukuList)
    }

    BookListModel {
        id: pengadaanBukuListModel
    }

    PengadaanModel {
        id: pengadaanModel
    }

    Item {
        Layout.fillWidth: true
        Layout.fillHeight: true
        ListView {
            id: pengadaanListView
            anchors.fill: parent
            anchors.margins: 16
            model: pengadaanModel
            spacing: 8

            onCurrentItemChanged: {
                if (currentItem != null) {
                    pengadaanDetailFrame.detailKode = currentItem.itemData.kode
                    pengadaanDetailFrame.detailSumber = currentItem.itemData.sumber
                } else {
                    pengadaanDetailFrame.detailKode = ""
                    pengadaanDetailFrame.detailSumber = ""
                }
            }

            delegate: Control {
                id: pengadaanListItem
                property var itemData: model
                property bool isSelected: ListView.isCurrentItem
                width: ListView.view.width
                padding: 16

                background: Rectangle {
                    border.color: "#dedede"
                    border.width: 1
                    radius: 16
                    color: pengadaanListItem.isSelected ? "#efefef" : "#ffffff"

                    MouseArea {
                        anchors.fill: parent

                        onClicked: pengadaanListView.currentIndex = index
                    }
                }

                contentItem: Label {
                    id: pengadaanListItemContent
                    text: model.sumber
                }
            }
        }

        FloatingActionButton {
            onClicked: {
                editPengadaanDialog.sumber = ""
                editablePengadaanBukuModel.clear();
                editPengadaanDialog.open()
            }
        }
    }

    Frame {
        id: pengadaanDetailFrame
        property string detailKode: ""
        property string detailSumber: ""

        Layout.minimumWidth: 300
        Layout.maximumWidth: 300
        Layout.fillHeight: true
        Layout.rightMargin: 16
        Layout.topMargin: 16
        Layout.bottomMargin: 16
        padding: 16

        background: Rectangle {
            border.color: "#dedede"
            border.width: 1
            radius: 16
        }

        GridLayout {
            anchors.fill: parent
            columnSpacing: 16
            visible: pengadaanDetailFrame.detailKode != ""
            columns: 2

            Label {
                text: "Kode"
            }

            Label {
                text: pengadaanDetailFrame.detailKode
                Layout.fillWidth: true
            }

            Label {
                text: "Sumber"
            }

            Label {
                text: pengadaanDetailFrame.detailSumber
                Layout.fillWidth: true
            }

            Label {
                text: pengadaanBukuModel.count > 0 ?  "Buku" : "Buku kosong"
                Layout.columnSpan: 2
                Layout.alignment: Qt.AlignHCenter

            }

            ListView {
                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.columnSpan: 2
                model: pengadaanBukuModel
                spacing: 8

                delegate: Pane {
                    width: ListView.view.width
                    padding: 16

                    background: Rectangle {
                        border.color: "#dedede"
                        border.width: 1
                        radius: 16
                    }

                    contentItem: ColumnLayout {
                        Label {
                            text: model.judulBuku
                        }
                        Label {
                            text: model.jumlah
                        }
                    }
                }
            }

            Row {
                Layout.columnSpan: 2
                spacing: 8

                Button {
                    text: "Edit"
                    onClicked: {
                        editPengadaanDialog.pengadaanKode = pengadaanDetailFrame.detailKode
                        editPengadaanDialog.sumber = pengadaanDetailFrame.detailSumber
                        editablePengadaanBukuModel.populateFrom(pengadaanBukuModel);
                        editPengadaanDialog.open();
                    }
                }

                Button {
                    text: "Hapus"
                    onClicked: {
                        pengadaanBukuModel.removeAll();
                        pengadaanModel.remove(pengadaanDetailFrame.detailKode);
                    }
                }
            }

        }

        Label {
            visible: pengadaanDetailFrame.detailSumber == ""
            text: "Tidak ada item yang terpilih"
        }
    }

    Dialog {
        property string pengadaanKode: ""
        property string sumber: ""

        id: editPengadaanDialog
        parent: Overlay.overlay
        anchors.centerIn: parent

        modal: true
        title: "Pengadaan Baru"
        standardButtons: Dialog.Ok | Dialog.Cancel

        width: 400
        contentHeight: editPengadaanDialogLayout.height

        onAccepted: {
            if (pengadaanKode == "") {
                pengadaanKode = pengadaanModel.add(sumber);
                pengadaanBukuModel.addAll(pengadaanKode, editablePengadaanBukuModel);
            } else {
                pengadaanModel.update(pengadaanKode, sumber);
                pengadaanBukuModel.updateAll(editablePengadaanBukuModel);
            }

            pengadaanKode = ""
            sumber = ""
        }

        Flickable {
            id: editPengadaanDialogFlickable
            anchors.fill: parent
            contentHeight: editPengadaanDialogLayout.height

            ColumnLayout {
                id: editPengadaanDialogLayout
                width: parent.width

                Label {
                    text: "Sumber"
                }
                TextField {
                    Layout.fillWidth: true
                    text: editPengadaanDialog.sumber
                    onTextChanged: editPengadaanDialog.sumber = text
                }
                Label {
                    text: "Buku"
                }
                Repeater {
                    model: editablePengadaanBukuModel

                    delegate: Frame {
                        Layout.fillWidth: true

                        ColumnLayout {
                            spacing: 8
                            anchors.fill: parent

                            Label {
                                text: model.judulBuku
                            }

                            Label {
                                text: "Jumlah"
                            }

                            SpinBox {
                                editable: true
                                from: 0
                                to: 10000
                                value: model.jumlah
                                Layout.fillWidth: true
                                onValueChanged: model.jumlah = value
                            }

                            Button {
                                text: "Hapus"
                                Layout.fillWidth: true
                                onClicked: editablePengadaanBukuModel.remove(index)
                            }
                        }

                    }
                }
                Button {
                    text: "Tambah Buku"
                    Layout.fillWidth: true
                    onClicked: tambahPengadaanBukuDialog.open()
                }
            }
        }
    }

    Dialog {
        id: tambahPengadaanBukuDialog
        parent: Overlay.overlay
        anchors.centerIn: parent
        contentHeight: parent.height
        modal: true
        title: "Tambah Buku ke Pengadaan"
        standardButtons: Dialog.Ok | Dialog.Cancel

        onAccepted: {
            editablePengadaanBukuModel.append(
                pengadaanBukuListModel.getKodeByIndex(bukuListView.currentIndex),
                0
            )
        }

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
                model: pengadaanBukuListModel

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
}
