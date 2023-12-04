import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Kelompok7.Perpus
import "../"

Dialog {
    title: "Pilih Member"
    parent: Overlay.overlay
    anchors.centerIn: parent
    contentHeight: rootLayout.implicitHeight
    standardButtons: Dialog.Ok | Dialog.Cancel
    width: 400

    property MemberPilihViewModel viewModel: MemberPilihViewModel {}

    ColumnLayout {
        id: rootLayout
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
            implicitHeight: contentHeight
            clip: true

            delegate: CardDelegate {
                width: ListView.view.width
                highlighted: ListView.isCurrentItem
                onClicked: memberListView.currentIndex = index
                text: TextHighlighter.highlightText(modelData.nama, viewModel.textQuery)
            }
        }
    }
}
