import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
    Layout.fillWidth: true
    Layout.fillHeight: true

    property var currentItemData
    property var listModel
    signal addClicked()

    AppGridView {
        id: kategoriGrid

        onCurrentItemChanged: {
            if (currentItem == null) {
                currentItemData = null
            } else {
                currentItemData = currentItem.itemData
            }
        }

        model: listModel

        delegate: CardDelegate {
            property var itemData: model
            width: GridView.view.itemWidth
            height: GridView.view.itemHeight
            highlighted: GridView.isCurrentItem
            onClicked: GridView.view.currentIndex = index
            padding: 16

            contentItem: ColumnLayout {
                spacing: 2

                Image {
                    source: "qrc:/icons/buku-black.svg"
                    fillMode: Image.PreserveAspectFit
                    Layout.alignment: Qt.AlignHCenter
                    width: 48
                    height: 48
                    sourceSize.width: 48
                    sourceSize.height: 48
                }


                Rectangle {
                    Layout.fillHeight: true
                }

                Label {
                    text: model.jenis
                    Layout.alignment: Qt.AlignHCenter
                }
            }
        }
    }

    FloatingActionButton {
        onClicked: addClicked()
    }
}
