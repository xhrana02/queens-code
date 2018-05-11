//----------------------------------------------//
//  Author: Pavel Hranáč (xhrana02)             //
//  School: Vysoké učení technické v Brně       //
//  Faculty: Fakulta informačních technologií   //
//  Date: Spring 2018                           //
//----------------------------------------------//

import QtQuick 2.7
import QtQuick.Controls 1.4

Rectangle {
    id: controlsBackground

    anchors.fill: parent

    color: "#000000"

    MenuButtonSmall {
        id: controlsButtonBack
        anchors.left: parent.left
        anchors.leftMargin: 40
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 30
        styledText: "Back"

        onClicked: {
            guiRoot.showMainMenu()
        }
    }

    Column {
        id: controls

        anchors.centerIn: parent
        
        spacing: 5

        property var textColor: "#F0E0A8"
        property var textSize: 15

        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            color: controls.textColor
            font.pixelSize: 20
            font.bold: true
            font.underline: true
            text: "Controls"
        }
        Item {
            // force double space
            width: 1
            height: 1
        }
        Text {
            color: controls.textColor
            font.pixelSize: controls.textSize
            text: "Camera panning - Shift+MMB, WASD, Arrow keys"
        }
        Text {
            color: controls.textColor
            font.pixelSize: controls.textSize
            text: "Camera rotation - MMB, Num8462"
        }
        Text {
            color: controls.textColor
            font.pixelSize: controls.textSize
            text: "Camera zoom - Wheel scroll, Num+-"
        }
        Text {
            color: controls.textColor
            font.pixelSize: controls.textSize
            text: "Unit selection - LMB"
        }
        Text {
            color: controls.textColor
            font.pixelSize: controls.textSize
            text: "Ability usage - RMB"
        }
        Text {
            color: controls.textColor
            font.pixelSize: controls.textSize
            text: "Ability selection - Keyboard numbers or by mouse"
        }
        Item {
            // force double space
            width: 1
            height: 1
        }
        Text {
            color: controls.textColor
            font.pixelSize: controls.textSize
            font.italic: true
            text: "LMB - Left Mouse Button, MMB - Middle Mouse Button, RMB - Right Mouse Button."
        }

        
    }
}

