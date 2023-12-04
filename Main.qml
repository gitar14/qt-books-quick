import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material
import Kelompok7.Perpus
import "./user"

ApplicationWindow {
    width: 960
    height: 640
    visible: true
    title: qsTr("QuickPerpus")

    property int sidebarRadius: 32
    property int sidebarWidth: 250

    Component.onCompleted: {
        TextHighlighter.setHighlightColor(Material.shade(Material.accent, Material.Shade500));
    }

    Component {
        id:  splashScreen

        SplashScreen {
            onSplashEnd: {
                if (!ConnectionManager.connectByRemembered()) {
                    mainStackView.push("ConnectionScreen.qml");
                }
            }
        }
    }

    Connections {
        target: ConnectionManager

        function onConnected() {
            if (!UserManager.hasAvailableUser()) {
                mainStackView.push(userBuatAdmin)
            } else {
                mainStackView.push(userLogin)
            }
        }

        function onConnectionFailed() {
            if (!mainStackView.currentItem)
                mainStackView.push("ConnectionScreen.qml");
        }
    }


    Component {
        id: userBuatAdmin

        UserBuatAdminScreen {
            onUserCreated: {
                mainStackView.replace(userLogin)
            }
        }
    }

    Component {
        id: userLogin

        UserLoginScreen {
            onLoggedIn: {
                mainStackView.push("DashboardScreen.qml")
            }
        }
    }

    StackView {
        id: mainStackView
        anchors.fill: parent
        initialItem: splashScreen

        pushEnter: Transition {
            XAnimator {
                from: (mainStackView.mirrored ? -1 : 1) * mainStackView.width
                to: 0
                duration: 1000
                easing.type: Easing.OutCubic
            }
        }

        pushExit: Transition {
            XAnimator {
                from: 0
                to: (mainStackView.mirrored ? -1 : 1) * -mainStackView.width
                duration: 1000
                easing.type: Easing.OutCubic
            }
        }

        replaceEnter: Transition {
            XAnimator {
                from: (mainStackView.mirrored ? -1 : 1) * -mainStackView.width
                to: 0
                duration: 1000
                easing.type: Easing.OutCubic
            }
        }

        replaceExit: Transition {
            XAnimator {
                from: 0
                to: (mainStackView.mirrored ? -1 : 1) * mainStackView.width
                duration: 1000
                easing.type: Easing.OutCubic
            }
        }
    }

}
