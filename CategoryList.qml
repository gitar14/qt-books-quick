import QtQuick
import my.id.levirs.books

Column {
    padding: 16
    GridView {
        width: Math.min(count, Math.floor((parent.width - parent.leftPadding - parent.rightPadding) / cellWidth)) * cellWidth
        anchors.horizontalCenter: parent.horizontalCenter
        height: parent.height
        cellWidth: 125
        cellHeight: 150

        model: KategoriModel {

        }

        delegate: Rectangle {
            width: GridView.view.cellWidth - 8
            height: GridView.view.cellHeight - 8

            border.color: "#dedede"
            border.width: 1
            radius: 16

            Column {
                id: itemComponent
                width: parent.width
                spacing: 2
                padding: 8

                Text {
                    text: model.kode
                    anchors.horizontalCenter: parent.horizontalCenter
                    horizontalAlignment: Text.AlignHCenter
                }

                Text {
                    text: model.jenis
                    anchors.horizontalCenter: parent.horizontalCenter
                }
            }
        }
    }
}
