import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material
import Kelompok7.Perpus

Page {
    leftPadding: sidebarRadius

    header: ToolBar {
        RowLayout {
            anchors.fill: parent

            Label {
                Layout.fillWidth: true
                text: "Kategori"
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                font.pixelSize: 20
            }

            SearchField {
                text: viewModel.textQuery
                onTextChanged: viewModel.textQuery = text
            }
        }
    }

    KategoriViewModel {
        id: viewModel
    }

    RowLayout {
        anchors.fill: parent

        KategoriList {
            currentViewModel: viewModel
            onAddClicked: {
                kategoriEditDialog.viewModel.configure()
                kategoriEditDialog.open()
            }
            onSelectedIndexChanged: viewModel.setSelectedIndex(selectedIndex)
        }

        KategoriDetailFrame {
            id: kategoriDetailFrame
            onEditClicked: {
                kategoriEditDialog.viewModel.configure(
                            viewModel.selectedKode,
                            viewModel.selectedName)
                kategoriEditDialog.open()
            }
            onDeleteClicked: viewModel.removeSelected()
            currentViewModel: viewModel
        }


        KategoriEditDialog{
            id: kategoriEditDialog
        }
    }
}
