import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.0

// Main page handler
import "../Main.js" as Main

GlassMessage {
    // Note: width and height must be set by caller

    property int modelId: -1
    property string title: ""
    property string description: ""
    property var triggerDate: null
    property var triggerTime: null
    property var createdAt: null
    property var updatedAt: null

    contentItem: Item {
        id: mainLayout
        anchors.fill: parent

        ColumnLayout {
            id: layoutMain
            anchors.fill: parent

            Flickable {
                id: flickable

                Layout.fillHeight: true
                Layout.fillWidth: true
                contentHeight: layout.height + 10
                clip: true

                ColumnLayout {
                    id: layout
                    width: parent.width

                    Label
                    {
                        Layout.fillWidth: true
                        Layout.topMargin: 20
                        Layout.rightMargin: 30
                        Layout.leftMargin: 30
                        text: title
                        color: Main.textColor
                        wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                        font.bold: true
                        font.pointSize: 18
                    }

                    Text {
                        Layout.fillWidth: true
                        Layout.topMargin: 30
                        Layout.rightMargin: 30
                        Layout.leftMargin: 30
                        text: description
                        color: Main.textColor
                        wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                        font.pointSize: 12
                    }

                    Text {
                        Layout.fillWidth: true
                        Layout.topMargin: 10
                        Layout.rightMargin: 30
                        Layout.leftMargin: 30
                        text: updatedAt ? "آخرین ویرایش در: " + Main.englishNumberToPersian(jalaliDate.unixTimestampToJalali(updatedAt)) : ""
                        color: Qt.lighter(Main.textColor)
                        font.italic: true
                        font.pointSize: 8
                    }

                }

                ScrollBar.vertical: ScrollBar { }

            }
            Rectangle {
                Layout.fillWidth: true
                height: 2
                color: "#aaa"
            }
            RowLayout {
                Layout.fillWidth: true

                Button {
                    Layout.leftMargin: 10
                    flat: true
                    text: qsTr("بستن")

                    onClicked: msg.close()
                }

                Item {
                    Layout.fillWidth: true
                }

                Text {
                    text: triggerDate ? Main.englishNumberToPersian(jalaliDate.unixTimestampToJalali(triggerDate)) : ""
                    color: Main.textColor
                }

                Text {
                    text: triggerTime ? Main.englishNumberToPersian(triggerTime) : ""
                    color: Main.textColor
                }

                RoundButton {
                    icon.source: "qrc:/images/trash.svg"
                    icon.height: 18
                    icon.width: 18
                    icon.color: Main.textColor
                    flat: true

                    onClicked: {
                        msg.close()
                        Main.showRemoveTaskQuestion(modelId, title)
                    }
                }
                RoundButton {
                    icon.source: "qrc:/images/pencil-edit-button.svg"
                    icon.height: 16
                    icon.width: 16
                    icon.color: Main.textColor
                    flat: true
                    Layout.rightMargin: 10

                    onClicked: {
                        msg.close()
                        Main.showEditTask(modelId, title, description, triggerDate, triggerTime, createdAt, updatedAt)
                    }
                }
            }
        }

        // Overlay
        Rectangle {
            id: rectOverlay
            anchors.fill: layoutMain
            visible: opacity !== 0
            opacity: 0
            color: "#903d0d6f"

            BusyIndicator {
                id: busyIndicator
                anchors.centerIn: parent
                running: false
            }

            Behavior on opacity
            {
                NumberAnimation
                {
                    duration: Main.msgShowDuration
                    easing.type: Main.msgEasingType
                }
            }
        }
    }
}
