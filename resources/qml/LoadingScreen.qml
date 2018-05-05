//----------------------------------------------//
//  Author: Pavel Hranáč (xhrana02)             //
//  School: Vysoké učení technické v Brně       //
//  Faculty: Fakulta informačních technologií   //
//  Date: Spring 2018                           //
//----------------------------------------------//

import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

Rectangle {
    id: loadingScreen

    anchors.fill: parent

    color: "#000000"

    FontLoader { id: menuFont; source: "fonts/CinzelDecorative-Regular.ttf" }

    Text {
        id: loadingText

        anchors.centerIn: parent
        
        color: "#F0E0A8"

        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 30
        font.bold: true
        font.family: menuFont.name

        text: "Loading..."
    }

    ProgressBar {
        id: loadingProgress

        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        height: 32

        style: ProgressBarStyle {
            background: Rectangle {
                color: "#000000"
                border.color: "#303030"
                border.width: 1
        }
        progress: Rectangle {
            color: "#F0E0A8"
            border.color: "#5F581A"
        }
    }
    }

    function updateProgress(progress) {
        loadingProgress.value = progress
    }
}