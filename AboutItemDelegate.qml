import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ItemDelegate {
    id: itemDelegate
    Layout.fillWidth: true
    required property string url
    required property string imageSource
    required property string title
    required property string subtitle

    onClicked: {
        Qt.openUrlExternally(url)
    }

    contentItem: RowLayout {
        width: parent.width
        spacing: 16

        Image {
            source: itemDelegate.imageSource
            Layout.fillWidth: true
            Layout.minimumWidth: 32
            Layout.minimumHeight: 32
            Layout.maximumHeight: 32
            Layout.maximumWidth: 32
            fillMode: Image.PreserveAspectFit
        }


        Column {
            Layout.fillWidth: true

            Label {
                text: itemDelegate.title
                font.bold: true
                horizontalAlignment: Qt.AlignLeft
            }

            Label {
                text: itemDelegate.subtitle
            }
        }
    }
}
