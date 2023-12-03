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

    property MemberPilihViewModel viewModel: MemberPilihViewModel {}

    ColumnLayout {
        anchors.fill: parent

        TextField {
            Layout.fillWidth: true
            text: viewModel.textQuery
            onTextChanged: viewModel.textQuery = text
        }

        ListView {
            id: memberListView
            Layout.fillHeight: true
            Layout.fillWidth: true
            currentIndex: viewModel.selectedIndex
            onCurrentIndexChanged: viewModel.selectedIndex = currentIndex
            model: viewModel.list
            spacing: 8

            delegate: CardDelegate {
                property var itemData: model
                highlighted: ListView.isCurrentItem
                onClicked: memberListView.currentIndex = index
                text: TextHighlighter.highlightText(modelData.nama, viewModel.textQuery)
            }
        }
    }
}
