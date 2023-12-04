import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Kelompok7.Perpus

Dialog {
    parent: Overlay.overlay
    anchors.centerIn: parent
    contentHeight: rootLayout.implicitHeight
    modal: true
    standardButtons: Dialog.Ok | Dialog.Cancel

    property BukuPilihViewModel viewModel: BukuPilihViewModel {}


    ColumnLayout {
        id: rootLayout
        anchors.fill: parent

        TextField {
            Layout.fillWidth: true
            text: viewModel.textQuery
            onTextChanged: viewModel.textQuery = text
        }

        BukuFilter {
            currentViewModel: viewModel
        }

        BukuListView {
            id: bukuListView
            Layout.fillHeight: true
            Layout.fillWidth: true
            model: viewModel.list
            onCurrentIndexChanged: viewModel.setSelectedIndex(currentIndex)
            highlightedText: viewModel.textQuery
            implicitHeight: contentHeight
        }
    }
}
