import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Dialog {
    parent: Overlay.overlay

    width: 400
    x: parent.width / 2 - width / 2
    y: parent.height / 2 - height / 2

    standardButtons: Dialog.Ok | Dialog.Cancel

    modal: true

    property string kategoriKode: ""
    property string kategoriJenis: ""

    title: kategoriKode == "" ? "Kategori Baru" : "Edit Kategori"

    ColumnLayout {
        spacing: 8
        width: parent.width

        Label {
            text: "Nama"
        }

        TextField {
            Layout.fillWidth: true
            text: kategoriJenis
            onTextChanged: kategoriJenis = text
        }
    }
}
