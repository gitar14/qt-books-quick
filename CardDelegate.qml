import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material
import QtQuick.Controls.Material.impl

ItemDelegate {
    id: control
    width: parent.width

    background: CardBackground {
        implicitHeight: control.Material.delegateHeight

        color: control.highlighted ?
                   control.Material.listHighlightColor
                 : "white"

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
