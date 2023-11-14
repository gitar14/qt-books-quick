import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
    Layout.fillHeight: true
    Layout.fillWidth: true

    property var listModel
    property var currentItemData

    signal addClicked()

    BukuListView {
        id: listView
        anchors.fill: parent
        anchors.margins: 16
        anchors.bottomMargin: 64 + 16 + 16
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

    FloatingActionButton {
        onClicked: addClicked()
    }
}
