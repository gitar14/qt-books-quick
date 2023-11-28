import QtQuick
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Controls.Material
import QtQuick.Layouts

ColumnLayout {
    property alias locale: combo.locale
    property date currentDate
    property string title

    Label {
        text: title
    }


    ComboBox {
        id: combo
        Layout.fillWidth: true
        displayText: Qt.formatDate(currentDate, locale, Locale.LongFormat)

        popup: Popup {
            id: controlPopup
            y: combo.height - 5
            width: contentItem.implicitWidth + horizontalPadding * 2
            implicitHeight: Math.min(
                                contentItem.implicitHeight + verticalPadding * 2,
                                combo.Window.height - topMargin - bottomMargin
                            )
            transformOrigin: Item.Top
            topMargin: 12
            bottomMargin: 12
            verticalPadding: 8

            onClosed: {
                if (yearView)
                    toggleYearView()
                controlListView.highlightMoveDuration = 0
                controlListView.currentIndex = controlListView.snapIndex
                controlListView.highlightMoveDuration = controlListView.maxMoveDuration
            }

            function toggleYearView() {
                controlPopup.yearView = !controlPopup.yearView
                if (!controlPopup.yearView) {
                    controlYearList.currentIndex = 0
                    controlYearList.currentIndex = controlYearList.snapIndex
                }
            }

            property bool yearView: false

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
                        icon.source: "qrc:/icons/chevron-left.svg"
                        icon.width: 24
                        icon.height: 24
                        onClicked: controlListView.decrementCurrentIndex()
                    }

                    Item {
                        Layout.fillWidth: true
                    }

                    RowLayout {
                        Label {
                            Layout.alignment: Qt.AlignVCenter
                            text: combo.locale.monthName(controlCalendarModel.monthAt(controlListView.currentIndex)) +
                                " " +
                                controlCalendarModel.yearAt(controlListView.currentIndex)

                            MouseArea {
                                anchors.fill: parent
                                onClicked: controlPopup.toggleYearView()
                            }
                        }

                        Image {
                            source: "qrc:/icons/arrow-down.svg"
                            width: 24
                            height: 24
                            sourceSize.width: 24
                            sourceSize.height: 24
                            fillMode: Image.PreserveAspectFit

                            MouseArea {
                                anchors.fill: parent
                                onClicked: controlPopup.toggleYearView()
                            }
                        }
                    }

                    Item {
                        Layout.fillWidth: true
                    }

                    RoundButton {
                        Material.background: "transparent"
                        icon.source: "qrc:/icons/chevron-right.svg"
                        icon.width: 24
                        icon.height: 24
                        onClicked: controlListView.incrementCurrentIndex()
                    }
                }

                ListView {
                    id: controlListView

                    property int maxMoveDuration: 500
                    visible: !controlPopup.yearView
                    width: 300
                    height: 200
                    snapMode: ListView.SnapOneItem
                    orientation: ListView.Horizontal
                    highlightRangeMode: ListView.StrictlyEnforceRange
                    clip: true
                    model: controlCalendarModel
                    highlightMoveDuration: maxMoveDuration

                    property int snapIndex: controlCalendarModel.indexOf(currentDate)

                    onSnapIndexChanged: {
                        currentIndex = snapIndex
                    }

                    delegate: ColumnLayout {
                        width: controlListView.width
                        height: controlListView.height

                        DayOfWeekRow {
                            locale: combo.locale
                            Layout.fillWidth: true
                        }

                        MonthGrid {
                            id: monthGrid
                            Layout.fillWidth: true
                            Layout.fillHeight: true
                            month: model.month
                            year: model.year
                            locale: combo.locale

                            onClicked: (date) => currentDate = date

                            delegate: Rectangle {
                                color: (
                                           model.date.getDate() == currentDate.getDate() &&
                                           model.date.getMonth() == currentDate.getMonth() &&
                                           model.date.getFullYear() == currentDate.getFullYear()
                                        ) ?
                                           Material.shade(combo.Material.accent, Material.Shade100) :
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

                ListView {
                    id: controlYearList
                    visible: controlPopup.yearView
                    width: 300
                    height: 200
                    model: 3000
                    highlightRangeMode: ListView.ApplyRange
                    highlightMoveDuration: 0
                    clip: true

                    property int snapIndex: controlCalendarModel.yearAt(controlListView.currentIndex)
                    onSnapIndexChanged: currentIndex = snapIndex


                    delegate: Rectangle {
                        width: ListView.view.width
                        height: yearDelegateLabel.height + 32
                        id: yearDelegate
                        radius: 16
                        color: ListView.isCurrentItem ? Material.shade(combo.Material.accent, Material.Shade100) :
                        "transparent"

                        MouseArea {
                            anchors.fill: parent

                            onClicked: {
                                controlListView.highlightMoveDuration = 0
                                controlListView.currentIndex = controlCalendarModel.indexOf(
                                            index,
                                            controlCalendarModel.monthAt(controlListView.currentIndex)
                                            )
                                controlPopup.yearView = false
                                controlListView.highlightMoveDuration = controlListView.maxMoveDuration
                            }
                        }

                        Label {
                            anchors.centerIn: parent
                            id: yearDelegateLabel
                            text: index
                        }
                    }

                }

                Button {
                    Layout.alignment: Qt.AlignRight
                    Material.background: "transparent"
                    Material.foreground: combo.Material.accent
                    text: "OK"
                    onClicked: controlPopup.close()
                }
            }
        }
    }
}
