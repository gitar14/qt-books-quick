import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import Kelompok7.Perpus

ColumnLayout {
    property TextFieldData field;
    property alias validator: textField.validator
    property alias echoMode: textField.echoMode

    Label {
        text : field.name
    }

    TextField {
        id: textField
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
