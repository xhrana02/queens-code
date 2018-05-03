//----------------------------------------------//
//	Author: Pavel Hranáč (xhrana02)				//
//	School: Vysoké učení technické v Brně		//
//	Faculty: Fakulta informačních technologií	//
//	Date: Spring 2018							//
//----------------------------------------------//

import QtQuick 2.7
import QtQuick.Controls 1.4

Rectangle {
    id: creditsBackground

    anchors.fill: parent

    color: "#000000"

    MenuButtonSmall {
        id: creditsButtonBack
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
        id: credits

        anchors.centerIn: parent
        
        spacing: 5

        property var textColor: "#F0E0A8"
        property var textSize: 15

        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            color: credits.textColor
            font.pixelSize: credits.textSize
            text: "Made by Pavel Hranac (xhrana02)"
        }
        Item {
            // force double space
            width: 1
            height: 1
        }
        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            color: credits.textColor
            font.pixelSize: credits.textSize
            text: "Software"
        }
        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            color: credits.textColor
            font.pixelSize: credits.textSize
            text: "CMake (solution builder)"
        }
        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            color: credits.textColor
            font.pixelSize: credits.textSize
            text: "Microsoft Visual Studio 2017 (C++ code)"
        }
        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            color: credits.textColor
            font.pixelSize: credits.textSize
            text: "Microsoft Visulo Studio Code (QML code)"
        }
        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            color: credits.textColor
            font.pixelSize: credits.textSize
            text: "Blender (modeling)"
        }
        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            color: credits.textColor
            font.pixelSize: credits.textSize
            text: "GitHub (source control)"
        }
        Item {
            // force double space
            width: 1
            height: 1
        }
        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            color: credits.textColor
            font.pixelSize: credits.textSize
            text: "Resources"
        }
        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            color: credits.textColor
            font.pixelSize: credits.textSize
            text: "https://texture.ninja/ (grass texture, wall texture)"
        }
        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            color: credits.textColor
            font.pixelSize: credits.textSize
            text: "http://spiralgraphics.biz (ice texture, wizard's balls texture)"
        }
        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            color: credits.textColor
            font.pixelSize: credits.textSize
            text: "http://game-icons.net/ (all ability icons made with this site's icon creator)"
        }
        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            color: credits.textColor
            font.pixelSize: credits.textSize
            text: "https://freesound.org/ (all sound effects)"
        }
    }
}

