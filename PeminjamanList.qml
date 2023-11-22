import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import Kelompok7.Perpus

Item {
    Layout.fillHeight: true
    Layout.fillWidth: true

    property var currentItemData
    required property PeminjamanModel listModel
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
                       value: PeminjamanModel.SemuaStatus
                    }

                    ListElement {
                        text: "Belum Dikembalikan"
                        value: PeminjamanModel.BelumDikembalikanStatus
                    }

                    ListElement {
                        text: "Belum Dikembalikan Melewati Tenggat"
                        value: PeminjamanModel.MelewatiTenggatStatus
                    }

                    ListElement {
                        text: "Sudah Dikembalikan"
                        value: PeminjamanModel.SudahDikembalikanStatus
                    }
                }
                valueRole: "value"
                textRole: "text"
                currentIndex: 1
                onCurrentValueChanged: listModel.statusFilter = currentValue
                Layout.maximumWidth: 400
                Layout.fillWidth: true
            }
        }


        ListView {
            Layout.fillHeight: true
            Layout.fillWidth: true
            id: peminjamanListView
            model: listModel
            spacing: 8

            onCurrentItemChanged: {
                if (currentItem != null){
                    currentItemData = currentItem.itemData
                }
                else{
                    currentItemData = null
                }
            }

            delegate: CardDelegate {
                id: peminjamanlistItem
                property var itemData: model
                highlighted: ListView.isCurrentItem
                width: ListView.view.width
                padding: 16
                onClicked: peminjamanListView.currentIndex = index

                contentItem: ColumnLayout {
                    Label {
                        text: model.namaMember
                        font.pixelSize: 16
                        font.bold: true
                    }

                    Flow {
                        Label {
                            text: "Dari " + Qt.formatDate(model.tanggal, locale, locale.LongFormat) + ". "
                            font.pixelSize: 14
                        }

                        Label {
                            text: (model.sudahDikembalikan ?
                                      "Dikembalikan pada " + Qt.formatDate(model.tanggalPengembalian, locale, locale.LongFormat) :
                                      "Tenggat pada " + Qt.formatDate(model.tanggalTenggat, locale, locale.LongFormat)
                                   ) + ". "
                            font.pixelSize: 14
                        }
                    }

                    Label {
                        text: model.sudahDikembalikan ? "Sudah Dikembalikan" : "Belum Dikembalikan"
                        font.pixelSize: 14
                        color: Material.color(model.sudahDikembalikan ? Material.Green : Material.Red, Material.Shade700)
                    }
                }
             }
        }
    }

    FloatingActionButton {
        onClicked: addClicked()
    }
}
