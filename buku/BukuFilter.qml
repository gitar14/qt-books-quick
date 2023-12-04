import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import Kelompok7.Perpus

GridLayout {
    property BukuPilihViewModel currentViewModel
    columns: 2
    rowSpacing: 0

    Label {
        text: "Kategori"
    }

    Label {
        text: "Penerbit"
    }

    ComboBox {
        model: currentViewModel.kategoriFilterList
        valueRole: "kode"
        textRole: "nama"
        editable: true
        currentIndex: 0
        onCurrentValueChanged: currentViewModel.kategoriFilter = currentValue
        Layout.fillWidth: true
        Layout.maximumWidth: 200
    }

    ComboBox {
        model: currentViewModel.penerbitFilterList
        valueRole: "kode"
        textRole: "nama"
        editable: true
        currentIndex: 0
        onCurrentValueChanged: currentViewModel.penerbitFilter = currentValue
        Layout.fillWidth: true
        Layout.maximumWidth: 200
    }
}
