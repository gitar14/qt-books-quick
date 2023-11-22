import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Kelompok7.Perpus

Item {
    Layout.fillHeight: true
    Layout.fillWidth: true

    property BookListModel listModel
    property KategoriFilterModel kategoriFilterModel
    property PenerbitFilterModel penerbitFilterModel
    property var currentItemData

    signal addClicked()

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 16
        anchors.bottomMargin: 64 + 16 + 16

        GridLayout {
            columns: 2
            rowSpacing: 0

            Label {
                text: "Kategori"
            }

            Label {
                text: "Penerbit"
            }

            ComboBox {
                model: kategoriFilterModel
                valueRole: "kode"
                textRole: "jenis"
                editable: true
                currentIndex: 0
                onCurrentValueChanged: listModel.kategoriFilter = currentValue
                Layout.fillWidth: true
                Layout.maximumWidth: 200
            }

            ComboBox {
                model: penerbitFilterModel
                valueRole: "kode"
                textRole: "name"
                editable: true
                currentIndex: 0
                onCurrentValueChanged: listModel.penerbitFilter = currentValue
                Layout.fillWidth: true
                Layout.maximumWidth: 200
            }
        }

        BukuListView {
            Layout.fillHeight: true
            Layout.fillWidth: true
            id: listView
            onCurrentItemChanged: {
                if (currentItem == null){
                    currentItemData = null
                }
                else {
                    currentItemData = currentItem.itemData
                }
            }
            model: listModel
        }
    }

    FloatingActionButton {
        onClicked: addClicked()
    }
}
