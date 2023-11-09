import QtQuick
import QtQuick.Controls
import Kelompok7.Perpus

ApplicationWindow {
    property string currentView: "KategoriScreen.qml"

    width: 960
    height: 640
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
            if (!UserManager.hasAvailableUser()) {
                loginAfterUserAddedConnection.enabled = true
                mainStackView.push("UserBuatAdminScreen.qml")
            } else {
                mainStackView.push("UserLoginScreen.qml")
            }
        }

        function onConnectionFailed() {
            if (!mainStackView.currentItem)
                mainStackView.push("ConnectionScreen.qml");
        }
    }

    Connections {
        target: UserManager

        function onLoggedIn() {
            mainStackView.push("DashboardScreen.qml")
        }
    }

    Connections {
        id: loginAfterUserAddedConnection
        enabled: false
        target: UserManager

        function onUserAdded() {
            mainStackView.push("UserLoginScreen.qml")
            loginAfterUserAddedConnection.enabled = false
        }
    }


    StackView {
        id: mainStackView
        anchors.fill: parent
    }

}
