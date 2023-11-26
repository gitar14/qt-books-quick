import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Kelompok7.Perpus

Item {
    Layout.fillHeight: true
    Layout.fillWidth: true

    signal addClicked()
    property var currentItemData
    property MemberViewModel currentViewModel

    AppGridView {
        id: memberGridView
        model: currentViewModel.list

        onCurrentIndexChanged: currentViewModel.setSelectedIndex(currentIndex)

        delegate: CardDelegate {
            property var itemData: model
            width: GridView.view.cellWidth - 8
            height: GridView.view.cellHeight - 8
            highlighted: GridView.isCurrentItem
            onClicked: memberGridView.currentIndex = index
            padding: 16

            contentItem: ColumnLayout{
                Image {
                    source: "qrc:/icons/assignment-ind-black.svg"
                    fillMode: Image.PreserveAspectFit
                    Layout.alignment: Qt.AlignHCenter
                    width: 48
                    height: 48
                    sourceSize.width: 48
                    sourceSize.height: 48
                }

                Label {
                    Layout.fillWidth: true
                    text: TextHighlighter.highlightText(modelData.namaDepan + " " + modelData.namaBelakang, currentViewModel.textQuery)
                    horizontalAlignment: Qt.AlignHCenter
                    wrapMode: Label.Wrap
                    maximumLineCount: 2
                    elide: Text.ElideRight
                    textFormat: Label.StyledText
                }
                Label {
                    Layout.fillWidth: true
                    text: Qt.formatDate(modelData.tanggalLahir, locale, locale.LongFormat)
                    horizontalAlignment: Qt.AlignHCenter
                    wrapMode: Text.Wrap
                }
            }
        }
    }

    FloatingActionButton {
        onClicked: addClicked()
    }
}
