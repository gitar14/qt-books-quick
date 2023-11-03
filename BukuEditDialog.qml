import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Dialog {
    property string bukuKode: ""
    property string bukuJudul: ""
    property string bukuPenulis: ""
    property int bukuJumlahBuku: 0
    property int bukuTahunTerbit: 0
    property string bukuKodeKategori: ""
    property string bukuKodePenerbit: ""
    property var kategoriModel
    property var penerbitModel

    parent: Overlay.overlay

    x: (parent.width - width) / 2
    y: (parent.height - height) / 2
    width: 400
    contentHeight: editDialogColumn.height

    modal: true
    title: bukuKode == "" ? "Tambah Buku" : "Edit Buku"
    standardButtons: Dialog.Ok | Dialog.Cancel

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
                text: bukuJudul
                onTextChanged: bukuJudul = text
            }

            Label {
                text: "Penulis"
            }

            TextField {
                Layout.fillWidth: true
                text: bukuPenulis
                onTextChanged: bukuPenulis = text
            }

            Label {
                text: "Kategori"
            }

            ComboBox {
                Layout.fillWidth: true
                model: kategoriModel
                valueRole: "kode"
                textRole: "jenis"
                editable: true
                currentIndex: kategoriModel.getIndexByKode(bukuKodeKategori)
                onCurrentValueChanged: bukuKodeKategori = currentValue
            }

            Label{
                text: "Penerbit"
            }

            ComboBox{
                Layout.fillWidth: true
                model: penerbitModel
                valueRole: "kode"
                textRole: "name"
                editable: true
                currentIndex: penerbitModel.getIndexByKode(bukuKodePenerbit)
                onCurrentValueChanged: bukuKodePenerbit = currentValue
            }


            Label {
                text: "Jumlah Buku"
            }

            SpinBox {
                Layout.fillWidth: true
                value: bukuJumlahBuku
                onValueChanged: bukuJumlahBuku = value
                editable: true
                from: 0
                to: 10000
            }

            Label {
                text: "Tahun Terbit"
            }

            SpinBox {
                Layout.fillWidth: true
                value: bukuTahunTerbit
                onValueChanged: bukuTahunTerbit = value
                editable: true
                from: 0
                to: 10000
            }
        }
    }
}
