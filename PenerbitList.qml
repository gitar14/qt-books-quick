import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item  {
    Layout.fillHeight: true
    Layout.fillWidth: true

    signal addClicked()
    property var listModel
    property var currentItemData

    AppGridView {
        id: penerbitGridView
        model : listModel

        onCurrentItemChanged: {
            if(currentItem == null){
                currentItemData = null;
            }
            else{
                currentItemData = currentItem.itemData;
            }
        }
        delegate: CardDelegate {
            property var itemData: model
            width: GridView.view.cellWidth - 8
            height: GridView.view.cellHeight - 8
            padding: 16
            highlighted: GridView.isCurrentItem
            onClicked: penerbitGridView.currentIndex = index


            ColumnLayout{
                anchors.fill:parent
                anchors.margins: 16

                Image {
                    source: "qrc:/icons/icons/homework-black.svg"
                    fillMode: Image.PreserveAspectFit
                    Layout.alignment: Qt.AlignHCenter
                    width: 48
                    height: 48
                    sourceSize.width: 48
                    sourceSize.height: 48
                }

                Rectangle{
                    Layout.fillHeight: true

                }
                Label {
                    text: model.name
                    Layout.alignment: Qt.AlignHCenter
                }
                Label {
                    text: model.alamat
                    Layout.alignment: Qt.AlignHCenter
                }
            }
        }
    }

    FloatingActionButton {
        onClicked: addClicked()
    }
}
