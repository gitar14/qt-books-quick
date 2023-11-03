import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
    Layout.fillHeight: true
    Layout.fillWidth: true
    Layout.leftMargin: 16
    Layout.topMargin: 16
    Layout.bottomMargin: 16

    signal addClicked()
    property var currentItemData
    property var listModel

    GridView {
        id: memberGridView
        model: listModel

        height: parent.height
        width: parent.width
        cellHeight: 150
        cellWidth: 125
        onCurrentItemChanged: {
             if(currentItem==null){
                 currentItemData=null

                }
             else {
                 currentItemData=currentItem.itemData

                }
        }

        delegate: Rectangle {
            property var itemData: model
            width: GridView.view.cellWidth - 8
            height: GridView.view.cellHeight - 8
            border.color: "#dedede"
            border.width: 1
            radius: 16
            color: GridView.isCurrentItem ? "#efefef" : "#ffffff"

            MouseArea {
                anchors.fill: parent

                onClicked: memberGridView.currentIndex = index
            }

            ColumnLayout{
                anchors.fill:parent
                anchors.margins: 16
                Rectangle{
                    Layout.fillHeight: true

                }
                Label {
                    text: model.name
                    Layout.alignment: Qt.AlignHCenter
                }
                Label {
                    text: model.tanggalLahir
                    Layout.alignment: Qt.AlignHCenter
                }
            }
        }
    }
    RoundButton {
        text : "+"
        width : 64
        height : 64
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        font.pixelSize: 24

        onClicked: addClicked()
    }
}
