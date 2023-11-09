import QtQuick
import QtQuick.Controls
import Kelompok7.Perpus

ApplicationWindow {
    property string currentView: "KategoriScreen.qml"

    width: 960
    height: 480
    visible: true
    title: qsTr("Hello World")

    property int sidebarRadius: 32
    property int sidebarWidth: 250

    Component.onCompleted: {
        if (!ConnectionManager.connectByRemembered()) {
            mainStackView.push("ConnectionScreen.qml");
        }
    }

    Connections {
        target: ConnectionManager

        function onConnected() {
            mainStackView.replace("DashboardScreen.qml");
        }
        function onConnectionFailed() {
            if (!mainStackView.currentItem)
                mainStackView.push("ConnectionScreen.qml");
        }
    }


    StackView {
        id: mainStackView
        anchors.fill: parent
    }

}
