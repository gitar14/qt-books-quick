import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import my.id.levirs.books
import Kelompok7.Perpus

RowLayout {
    BookListDetailModel {
        id: detailModel
    }

    BookListModel {
        id: listModel
    }

    KategoriModel {
        id: bukuKategoriModel
    }

    PenerbitModel{
        id: bukuPenerbitModel
    }

    property var currentItemData: bukuListView.currentItem ? bukuListView.currentItem.itemData : null
    property var currentKode: currentItemData ? currentItemData.kode : ""
    property var currentJudul: currentItemData ? currentItemData.judul : ""
    property var currentPenulis: currentItemData ? currentItemData.penulis : ""
    property var currentTahunTerbit: currentItemData ? currentItemData.tahunTerbit : ""
    property var currenKategori: currentItemData ? currentItemData.kategori : ""

    Rectangle {
        Layout.fillHeight: true
        Layout.fillWidth: true
        ListView {
            id: bukuListView
            anchors.fill: parent
            anchors.margins: 16
            anchors.bottomMargin: 64 + 16 + 16
            onCurrentItemChanged: {

                detailModel.kode = model.getKodeByIndex(currentIndex)
                if (currentItem == null){
                bookDetailFrame.bukuPenerbit = ""
                }
                else {
                bookDetailFrame.bukuPenerbit = currentItem.itemData.penerbit
                }
            }

            spacing: 8
            model: listModel

            delegate: Rectangle {
                property var listView: ListView.view
                property var itemData: model
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

                    Label{
                        text: model.penerbit
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
                    editDialog.kode = ""
                    editDialog.judul = ""
                    editDialog.penulis = ""
                    editDialog.jumlahBuku = 0
                    editDialog.tahunTerbit = 0
                    editDialog.kodeKategori = ""
                    editDialog.kodePenerbit = ""
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

    Frame {
        id: bookDetailFrame
//        border.color: "#dedede"
//        border.width: 1
//        radius: 16
        width: 300
        Layout.minimumWidth: 300
        Layout.maximumWidth: 300
        Layout.fillHeight: true
        Layout.rightMargin: 16
        Layout.topMargin: 16
        Layout.bottomMargin: 16

        property string bukuPenerbit: ""

        GridLayout {
            anchors.fill: parent
            columns: 2
            columnSpacing: 16
            visible: currentKode != ""

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
                text: currentKode
            }

            Text {
                text: "Judul"
            }

            Text {
                Layout.fillWidth: true
                text: currentJudul
            }

            Text {
                text: "Penulis"
            }

            Text {
                Layout.fillWidth: true
                text: currentPenulis
            }

            Text {
                text: "Kategori"
            }

            Text {
                Layout.fillWidth: true
                text: currenKategori
            }

            Label {
                text: "Penerbit"
            }

            Label{
                text: bookDetailFrame.bukuPenerbit
                Layout.fillWidth: true
            }

            Text {
                text: "Jumlah Buku"
            }

            Text {
                Layout.fillWidth: true
                text: detailModel.jumlahBuku
            }

            Text {
                text: "Tahun Terbit"
            }

            Text {
                Layout.fillWidth: true
                text: currentTahunTerbit
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
                        editDialog.kode = currentKode
                        editDialog.judul = currentJudul
                        editDialog.penulis = currentPenulis
                        editDialog.jumlahBuku = detailModel.jumlahBuku
                        editDialog.tahunTerbit = currentTahunTerbit
                        editDialog.kodeKategori = detailModel.kodeKategori
                        editDialog.kodePenerbit = detailModel.kodePenerbit
                        editDialog.open()
                    }
                }

                Button {
                    text: "Hapus"
                    onClicked: listModel.remove(currentKode)
                }
            }
        }

        Label {
            text: "Tidak Ada Data Buku"
            visible: currentKode == ""
        }
    }

    Dialog {
        property string kode: ""
        property string judul: ""
        property string penulis: ""
        property int jumlahBuku: 0
        property int tahunTerbit: 0
        property string kodeKategori: ""
        property string kodePenerbit: ""

        id: editDialog
        parent: Overlay.overlay

        x: (parent.width - width) / 2
        y: (parent.height - height) / 2
        width: 400
        contentHeight: editDialogColumn.height

        modal: true
        title: kode == "" ? "Tambah Buku" : "Edit Buku"
        standardButtons: Dialog.Ok | Dialog.Cancel

        onAccepted: {
            if (kode == "")
                listModel.addNew(
                    judul,
                    penulis,
                    jumlahBuku,
                    tahunTerbit,
                    kodeKategori,
                    kodePenerbit
                )
            else
                listModel.edit(
                    kode,
                    judul,
                    penulis,
                    jumlahBuku,
                    tahunTerbit,
                    kodeKategori,
                    kodePenerbit
                )
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
                    text: editDialog.judul
                    onTextChanged: editDialog.judul = text
                }


                Label {
                    text: "Penulis"
                }

                TextField {
                    Layout.fillWidth: true
                    text: editDialog.penulis
                    onTextChanged: editDialog.penulis = text
                }

                Label {
                    text: "Kategori"
                }

                ComboBox {
                    Layout.fillWidth: true
                    model: bukuKategoriModel
                    valueRole: "kode"
                    textRole: "jenis"
                    editable: true
                    currentIndex: bukuKategoriModel.getIndexByKode(editDialog.kodeKategori)
                    onCurrentValueChanged: editDialog.kodeKategori = currentValue
                }

                Label{
                text: "Penerbit"
                }

                ComboBox{
                Layout.fillWidth: true
                model: bukuPenerbitModel
                valueRole: "kode"
                textRole: "name"
                editable: true
                currentIndex: bukuPenerbitModel.getIndexByKode(editDialog.kodePenerbit)
                onCurrentValueChanged: editDialog.kodePenerbit = currentValue
                }


                Label {
                    text: "Jumlah Buku"
                }

                SpinBox {
                    Layout.fillWidth: true
                    value: editDialog.jumlahBuku
                    onValueChanged: editDialog.jumlahBuku = value
                    editable: true
                    from: 0
                    to: 10000
                }

                Label {
                    text: "Tahun Terbit"
                }

                SpinBox {
                    Layout.fillWidth: true
                    value: editDialog.tahunTerbit
                    onValueChanged: editDialog.tahunTerbit = value
                    editable: true
                    from: 0
                    to: 10000
                }
            }
        }
    }
}
