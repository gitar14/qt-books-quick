import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Kelompok7.Perpus
import "../"

Dialog {
    parent: Overlay.overlay
    anchors.centerIn: parent
    contentHeight: parent.height
    standardButtons: Dialog.Ok | Dialog.Cancel
    width: 400

    property MemberViewModel viewModel: MemberViewModel {}

    ColumnLayout {
        anchors.fill: parent

        TextField {
            Layout.fillWidth: true
        }

        ListView {
            id: memberListView
            Layout.fillHeight: true
            Layout.fillWidth: true
            onCurrentIndexChanged: viewModel.setSelectedIndex(currentIndex)
            model: viewModel.list

            delegate: CardDelegate {
                property var itemData: model
                highlighted: ListView.isCurrentItem
                onClicked: memberListView.currentIndex = index
                text: modelData.namaDepan + " " + modelData.namaBelakang
            }
        }
    }
}
