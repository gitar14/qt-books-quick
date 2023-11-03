import QtQuick
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Controls.Material
import QtQuick.Layouts

ComboBox {
    id: control
    property date currentDate

    displayText: Qt.formatDate(currentDate, locale, locale.LongFormat)

    popup: Popup {
        id: controlPopup
        y: control.height - 5
        width: contentItem.implicitWidth + horizontalPadding * 2
        implicitHeight: Math.min(
                            contentItem.implicitHeight + verticalPadding * 2,
                            control.Window.height - topMargin - bottomMargin
                        )
        transformOrigin: Item.Top
        topMargin: 12
        bottomMargin: 12
        verticalPadding: 8

        onClosed: {
            controlListView.highlightMoveDuration = 0
            controlListView.currentIndex = controlListView.snapIndex
            controlListView.highlightMoveDuration = -1
        }

        contentItem: ColumnLayout {
            clip: true
            spacing: 0

            CalendarModel {
                id: controlCalendarModel
            }

            RowLayout {
                Layout.fillWidth: true

                RoundButton {
                    Material.background: "transparent"
                    text: "<"
                    onClicked: controlListView.decrementCurrentIndex()
                }

                Label {
                    Layout.fillWidth: true
                    text: control.locale.monthName(controlCalendarModel.monthAt(controlListView.currentIndex)) +
                        " " +
                        controlCalendarModel.yearAt(controlListView.currentIndex)
                    horizontalAlignment: Qt.AlignHCenter
                }

                RoundButton {
                    Material.background: "transparent"
                    text: ">"
                    onClicked: controlListView.incrementCurrentIndex()
                }
            }

            ListView {
                id: controlListView

                width: 300
                height: 200
                snapMode: ListView.SnapOneItem
                orientation: ListView.Horizontal
                highlightRangeMode: ListView.StrictlyEnforceRange
                clip: true
                model: controlCalendarModel

                property var snapIndex: controlCalendarModel.indexOf(currentDate)

                onSnapIndexChanged: {
                    currentIndex = snapIndex
                }

                delegate: ColumnLayout {
                    width: controlListView.width
                    height: controlListView.height

                    DayOfWeekRow {
                        locale: control.locale
                        Layout.fillWidth: true
                    }

                    MonthGrid {
                        id: monthGrid
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        month: model.month
                        year: model.year
                        locale: control.locale

                        onClicked: (date) => currentDate = date

                        delegate: Rectangle {
                            color: (
                                       model.date.getDate() == currentDate.getDate() &&
                                       model.date.getMonth() == currentDate.getMonth() &&
                                       model.date.getFullYear() == currentDate.getFullYear()
                                    ) ?
                                       Material.shade(control.Material.accent, Material.Shade100) :
                                       "transparent"

                            Label {
                                anchors.fill: parent
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                                text: model.day
                                opacity: model.month == monthGrid.month ? 1 : 0.5
                            }
                        }
                    }
                }
            }

            Button {
                Layout.alignment: Qt.AlignRight
                Material.background: "transparent"
                Material.foreground: control.Material.accent
                text: "OK"
                onClicked: controlPopup.close()
            }
        }
    }
}
