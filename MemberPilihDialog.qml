import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Kelompok7.Perpus

Dialog {
    parent: Overlay.overlay
    anchors.centerIn: parent
    contentHeight: parent.height
    standardButtons: Dialog.Ok | Dialog.Cancel
    width: 400

    required property MemberModel listModel
    property var currentItemData

    ColumnLayout {
        anchors.fill: parent

        TextField {
            Layout.fillWidth: true
        }

        ListView {
            id: memberListView
            Layout.fillHeight: true
            Layout.fillWidth: true

            model: listModel

            onCurrentItemChanged: {
                currentItemData = currentItem == null ? null : currentItem.itemData
            }

            delegate: CardDelegate {
                property var itemData: model
                highlighted: ListView.isCurrentItem
                onClicked: memberListView.currentIndex = index
                text: model.name
            }
        }
    }
}
