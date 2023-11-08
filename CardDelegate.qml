import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material
import QtQuick.Controls.Material.impl

ItemDelegate {
    id: control
    width: parent.width

    background: Rectangle {
        implicitHeight: control.Material.delegateHeight

        color: control.highlighted ?
                   control.Material.listHighlightColor
                 : "transparent"
        radius: 16
        border.width: 1
        border.color: control.Material.listHighlightColor

        Ripple {
            width: parent.width
            height: parent.height
            clip: true
            clipRadius: 16
            pressed: control.pressed
            anchor: control
            active: enabled &&
                    (control.down || control.visualFocus || control.hovered)
            color: control.Material.rippleColor
        }

    }
}
