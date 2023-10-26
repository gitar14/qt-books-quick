import QtQuick

Column {
    padding: 16
    GridView {
        width: Math.min(count, Math.floor((parent.width - parent.leftPadding - parent.rightPadding) / cellWidth)) * cellWidth
        anchors.horizontalCenter: parent.horizontalCenter
        height: parent.height
        cellWidth: 125
        cellHeight: 150

        model: penerbitModel

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
                    text: model.Kode_penerbit
                    anchors.horizontalCenter: parent.horizontalCenter
                    horizontalAlignment: Text.AlignHCenter
                }

                Text {
                    text: model.Nm_penerbit
                    anchors.horizontalCenter: parent.horizontalCenter
                }
            }
        }
    }
}
