import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import "../Main.js" as Main

Item {

    id: itemToday

    ColumnLayout
    {
        anchors.fill: itemToday
        spacing: 2

        Text {
            Layout.fillWidth: true
            horizontalAlignment: Text.AlignHCenter
            color: Main.textColor
            text: todayEvents.persianDate
        }

        Text {
            Layout.fillWidth: true
            horizontalAlignment: Text.AlignHCenter
            color: Main.textColor
            text: todayEvents.islamicDate
        }

        Text {
            Layout.fillWidth: true
            horizontalAlignment: Text.AlignHCenter
            color: Main.textColor
            text: todayEvents.gregorianDate
        }

        Text {
            Layout.fillWidth: true
            horizontalAlignment: Text.AlignHCenter
            color: Main.textColor
            text: qsTr("زمان سپری شده از امسال")
        }

        ProgressBar
        {
            id: progYear
            Layout.fillWidth: true
            from: 1
            to: 365

            value: jalaliDate.getCurrentJalaliDayInYear()
        }


        Text {
            Layout.fillWidth: true
            horizontalAlignment: Text.AlignHCenter
            color: Main.textColor
            text: qsTr("زمان سپری شده از این ماه")
        }

        ProgressBar
        {
            id: progMonth
            Layout.fillWidth: true
            from: 1
            to: 31

            value: jalaliDate.getCurrentJalaliDayInMonth()
        }

        Text {
            Layout.fillWidth: true
            horizontalAlignment: Text.AlignHCenter
            color: Main.textColor
            text: qsTr("زمان سپری شده از امروز")
        }

        ProgressBar
        {
            id: progDay
            Layout.fillWidth: true
            from: 1
            to: 86400000

            value: jalaliDate.getCurrentMillisecondOfDay()
        }
    }


}





/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
