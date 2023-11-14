import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import Kelompok7.Perpus



Item {
    Layout.fillHeight: true
    Layout.fillWidth: true

    property var currentItemData
    required property PeminjamanModel listModel
    signal addClicked()

    ListView {
        id: peminjamanListView
        anchors.fill: parent
        anchors.margins: 16
        model: listModel
        spacing: 8

        onCurrentItemChanged: {
            if (currentItem != null){
                currentItemData = currentItem.itemData
            }
            else{
                currentItemData = null
            }
        }

        delegate: CardDelegate {
            id: peminjamanlistItem
            property var itemData: model
            highlighted: ListView.isCurrentItem
            width: ListView.view.width
            padding: 16
            onClicked: peminjamanListView.currentIndex = index

            contentItem: ColumnLayout {
                Label {
                    text: model.namaMember
                }

                Label {
                    text: model.tanggal
                }

                Label {
                   text: model.lama + " hari"
                }
            }
         }
    }

    FloatingActionButton {
        onClicked: addClicked()
    }
}
