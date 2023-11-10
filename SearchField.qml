import QtQuick
import QtQuick.Controls.Basic as Basic
import QtQuick.Controls.Material
import QtQuick.Layouts

Basic.TextField {
    id: control
    Layout.minimumWidth: 200
    Layout.maximumWidth: 200
    Layout.rightMargin: 16
    placeholderText: "Cari"
    leftPadding: 36
    rightPadding: 16

    background: Rectangle {
        color: "#ffffff"
        radius: 16
        border.width: control.focus ? 2 : 0
        border.color: Material.accentColor

        Image {
            width: 24
            height: parent.height
            fillMode: Image.Pad
            x: 8
            source: "qrc:/icons/search-black.svg"
        }
    }
}
