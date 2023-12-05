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
    property bool intoMain: false

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
                intoMain = true
                mainStackView.push("DashboardScreen.qml")
            }
        }
    }

    StackView {
        id: mainStackView
        anchors.fill: parent
        initialItem: splashScreen

        property Transition normalPushEnter: Transition {
            XAnimator {
                from: (mainStackView.mirrored ? -1 : 1) * mainStackView.width
                to: 0
                duration: 1000
                easing.type: Easing.InOutCubic
            }
        }

        property Transition intoMainPushEnter: Transition {
            NumberAnimation {
                properties: "opacity"
                duration: 0
                from: 0
                to: 0
            }

            SequentialAnimation {
                PauseAnimation {
                    duration: 600
                }
                OpacityAnimator {
                    duration: 250
                    from: 0
                    to: 1
                }
            }
        }

        property Transition normalPushExit: Transition {
            XAnimator {
                from: 0
                to: (mainStackView.mirrored ? -1 : 1) * -mainStackView.width
                duration: 1000
                easing.type: Easing.InOutCubic
            }
        }

        property Transition intoMainPushExit: Transition {
            ScaleAnimator {
                from: 1
                to: 0
                duration: 500
                easing.type: Easing.InOutCubic
            }
        }

        pushEnter: !intoMain ? normalPushEnter : intoMainPushEnter

        pushExit: !intoMain ? normalPushExit : intoMainPushExit

        replaceEnter: Transition {
            XAnimator {
                from: (mainStackView.mirrored ? -1 : 1) * -mainStackView.width
                to: 0
                duration: 1000
                easing.type: Easing.InOutCubic
            }
        }

        replaceExit: Transition {
            XAnimator {
                from: 0
                to: (mainStackView.mirrored ? -1 : 1) * mainStackView.width
                duration: 1000
                easing.type: Easing.InOutCubic
            }
        }
    }

}
