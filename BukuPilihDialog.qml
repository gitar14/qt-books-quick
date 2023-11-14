import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Kelompok7.Perpus

Dialog {
    parent: Overlay.overlay
    anchors.centerIn: parent
    contentHeight: parent.height
    modal: true
    standardButtons: Dialog.Ok | Dialog.Cancel

    property BookListModel listModel
    property int selectedIndex: bukuListView.currentIndex

    ColumnLayout {
        anchors.fill: parent

        TextField {
            Layout.fillWidth: true
            text: listModel.textQuery
            onTextChanged: listModel.textQuery = text
        }

        BukuListView {
            id: bukuListView
            Layout.fillHeight: true
            Layout.fillWidth: true
            model: listModel
        }
    }
}
