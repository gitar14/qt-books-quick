import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material

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

    footer : DialogButtonBox {
        Button {
            text: "Batal"
            DialogButtonBox.buttonRole: Dialog.RejectRole
            flat: true
        }
        Button {
            text: "Simpan"
            enabled: bukuJudul.length > 0 && bukuPenulis.length > 0 && bukuKodeKategori > 0 && bukuKodePenerbit > 0

            DialogButtonBox.buttonRole: Dialog.AcceptRole
            flat: true
        }
    }


    parent: Overlay.overlay

    x: (parent.width - width) / 2
    y: (parent.height - height) / 2
    width: 400
    contentHeight: editDialogColumn.height

    modal: true
    title: bukuKode == "" ? "Tambah Buku" : "Edit Buku"

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
                maximumLength: 25
                text: bukuJudul
                onTextChanged: bukuJudul = text
            }

            Label {
                text: "Judul Tidak Boleh Kosong"
                color: Material.color(Material.Red)
                visible: bukuJudul.length == 0
            }

            Label {
                text: "Penulis"
            }

            TextField {
                Layout.fillWidth: true
                maximumLength: 25
                text: bukuPenulis
                onTextChanged: bukuPenulis = text
            }

            Label {
                text: "Penulis Tidak Boleh Kosong"
                color: Material.color(Material.Red)
                visible: bukuPenulis.length == 0
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

            Label {
                text: "Kategori Tidak Boleh Kosong"
                color: Material.color(Material.Red)
                visible: bukuKodeKategori.length == 0
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
                text: "Penerbit Tidak Boleh Kosong"
                color: Material.color(Material.Red)
                visible: bukuKodePenerbit.length == 0
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
