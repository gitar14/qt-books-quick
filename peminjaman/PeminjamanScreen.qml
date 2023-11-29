import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Kelompok7.Perpus
import "../"

Page {
    leftPadding: sidebarRadius

    header: ToolBar {
        RowLayout{
            anchors.fill: parent

            Label {
                Layout.fillWidth: true
                text: "Peminjaman"
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                font.pixelSize: 20
            }

            SearchField {
//                 text: peminjamanBukuModel.textQuery
//                 onTextChanged: peminjamanBukuModel.textQuery = text
            }
        }
    }

    PeminjamanViewModel {
        id: viewModel
    }

    RowLayout {
        anchors.fill: parent

        PeminjamanList {
            currentViewModel: viewModel
            onAddClicked: {
                editPeminjamanDialog.viewModel.configure(-1)
                editPeminjamanDialog.open()
            }
        }

        PeminjamanEditDialog{
            id: editPeminjamanDialog
        }

        PengembalianAddDialog {
            id: dialogPengembalian
        }

        PeminjamanDetailFrame{
            id: peminjamanDetailFrame
            currentViewModel: viewModel
            onEditClicked: {
                editPeminjamanDialog.viewModel.configure(viewModel.selectedData.kode)
                editPeminjamanDialog.open();
            }

            onDeleteClicked: {
                viewModel.removeSelectedItem()
            }

            onTandaiDikembalikanClicked: {
                dialogPengembalian.viewModel.configure(viewModel.selectedData.kode)
                dialogPengembalian.open()
            }

            onTandaiBelumDikembalikanClicked: {
                viewModel.tandaiBelumDikembalikanSelected()
            }
        }
    }
}
