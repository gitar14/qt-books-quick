import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Kelompok7.Perpus
import "../"

Item {
    id: list
    Layout.fillHeight: true
    Layout.fillWidth: true

    property BukuViewModel currentViewModel

    signal addClicked()

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 16
        anchors.bottomMargin: 64 + 16 + 16

        BukuFilter {
            currentViewModel: list.currentViewModel
        }

        BukuListView {
            Layout.fillHeight: true
            Layout.fillWidth: true
            id: listView
            onCurrentIndexChanged: currentViewModel.setSelectedIndex(currentIndex)
            model: currentViewModel.list
            highlightedText: currentViewModel.textQuery
        }
    }

    FloatingActionButton {
        onClicked: addClicked()
    }
}
