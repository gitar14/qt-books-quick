import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import Kelompok7.Perpus
import "../"

Item {
    Layout.fillHeight: true
    Layout.fillWidth: true

    property PeminjamanViewModel currentViewModel
    signal addClicked()

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 16

        ColumnLayout {
            spacing: 0
            Label {
                text: "Status"
            }

            ComboBox {
                model: ListModel {
                    ListElement {
                       text: "Semua"
                       value: PeminjamanViewModel.SemuaStatus
                    }

                    ListElement {
                        text: "Belum Dikembalikan"
                        value: PeminjamanViewModel.BelumDikembalikanStatus
                    }

                    ListElement {
                        text: "Belum Dikembalikan Melewati Tenggat"
                        value: PeminjamanViewModel.MelewatiTenggatStatus
                    }

                    ListElement {
                        text: "Sudah Dikembalikan"
                        value: PeminjamanViewModel.SudahDikembalikanStatus
                    }
                }
                valueRole: "value"
                textRole: "text"
                currentIndex: 1
                onCurrentValueChanged: currentViewModel.statusFilter = currentValue
                Layout.maximumWidth: 400
                Layout.fillWidth: true
            }
        }


        ListView {
            Layout.fillHeight: true
            Layout.fillWidth: true
            id: peminjamanListView
            model: currentViewModel.list
            spacing: 8
            onCurrentIndexChanged: currentViewModel.setSelectedIndex(currentIndex)

            delegate: CardDelegate {
                id: peminjamanlistItem
                property var itemData: model
                highlighted: ListView.isCurrentItem
                width: ListView.view.width
                padding: 16
                onClicked: peminjamanListView.currentIndex = index

                contentItem: ColumnLayout {
                    Label {
                        text: modelData.namaMember
                        font.pixelSize: 16
                        font.bold: true
                    }

                    Flow {
                        Label {
                            text: "Dari " + Qt.formatDate(modelData.tanggalPeminjaman, locale, locale.LongFormat) + ". "
                            font.pixelSize: 14
                        }

                        Label {
                            text: (modelData.sudahDikembalikan ?
                                      "Dikembalikan pada " + Qt.formatDate(modelData.tanggalPengembalian, locale, locale.LongFormat) :
                                      "Tenggat pada " + Qt.formatDate(modelData.tenggatPengembalian, locale, locale.LongFormat)
                                   ) + ". "
                            font.pixelSize: 14
                        }
                    }

                    Label {
                        text: modelData.sudahDikembalikan ? "Sudah Dikembalikan" : "Belum Dikembalikan"
                        font.pixelSize: 14
                        color: Material.color(modelData.sudahDikembalikan ? Material.Green : Material.Red, Material.Shade700)
                    }
                }
             }
        }
    }

    FloatingActionButton {
        onClicked: addClicked()
    }
}
