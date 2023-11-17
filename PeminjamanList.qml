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

    ListView {
        id: peminjamanListView
        anchors.fill: parent
        anchors.margins: 16
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

    FloatingActionButton {
        onClicked: addClicked()
    }
}
