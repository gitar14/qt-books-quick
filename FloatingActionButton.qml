import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material

RoundButton {
    text : "+"
    width : 64
    height : 64
    anchors.right: parent.right
    anchors.bottom: parent.bottom
    anchors.bottomMargin: 16
    anchors.rightMargin: 16
    font.pixelSize: 24
    Material.background: Material.accent
    Material.foreground: "#ffffff"
}
