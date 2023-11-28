import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import Kelompok7.Perpus

ColumnLayout {
    property TextFieldData field;
    property string title
    property bool showAvailableCount: true
    property alias validator: textField.validator
    property alias echoMode: textField.echoMode

    Label {
        text: title
    }

    TextField {
        id: textField
        text: field.value
        maximumLength: field.maxLength
        Layout.fillWidth: true
        onTextChanged: field.value = text;
    }

    Label {
        visible: showAvailableCount
        Layout.alignment: Qt.AlignRight
        text: (field.maxLength - field.value.length) + " tersisa"
    }

    Label {
        text: title + " " + field.errorText
        color: Material.color(Material.Red)
        visible: !field.isValid
    }
}
