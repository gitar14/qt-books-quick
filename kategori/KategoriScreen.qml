import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material
import Kelompok7.Perpus
import "../"

Page {
    leftPadding: sidebarRadius

    header: ToolBar {
        RowLayout {
            anchors.fill: parent
            anchors.leftMargin: sidebarRadius

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
        }

        KategoriDetailFrame {
            id: kategoriDetailFrame
            onEditClicked: {
                kategoriEditDialog.viewModel.configure(viewModel.selectedData.kode)
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
