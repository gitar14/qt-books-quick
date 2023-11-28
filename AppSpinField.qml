import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

ColumnLayout {
    property string title
    property string suffix
    property alias from: spinBox.from
    property alias to: spinBox.to
    property alias value: spinBox.value
    property alias editable: spinBox.editable


    Label {
        text: title
    }

    RowLayout {
        SpinBox {
            Layout.fillWidth: true
            id: spinBox
        }

        Label {
            visible: suffix.length > 0
            text: suffix
            font.pixelSize: 16
            Layout.leftMargin: 8
        }
    }
}
