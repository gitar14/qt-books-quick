import QtQuick

GridView {
    width: Math.min(count,
                    Math.floor(
                        (parent.width - 2 * anchors.topMargin) / cellWidth)
                    ) * cellWidth
    anchors.horizontalCenter: parent.horizontalCenter
    anchors.top: parent.top
    anchors.bottom: parent.bottom
    anchors.topMargin: 16
    height: parent.height
    cellWidth: 128
    cellHeight: 150

    property int itemWidth: cellWidth - 8
    property int itemHeight: cellHeight - 8
}
