import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import Kelompok7.Perpus

ColumnLayout {
    property TextFieldData field;

    Label {
        text : field.name
    }

    TextField {
        text: field.value
        maximumLength: field.maxLength
        Layout.fillWidth: true
        onTextChanged: field.value = text;
    }

    Label {
        Layout.alignment: Qt.AlignRight
        text: field.availableLength + " tersisa"
    }

    Label {
        text: field.errorText
        color: Material.color(Material.Red)
        visible: !field.isValid
    }
}
