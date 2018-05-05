//----------------------------------------------//
//  Author: Pavel Hranáč (xhrana02)             //
//  School: Vysoké učení technické v Brně       //
//  Faculty: Fakulta informačních technologií   //
//  Date: Spring 2018                           //
//----------------------------------------------//

import QtQuick 2.7

Item {
    id: mainMenu

    anchors.fill: parent

    Column {
        id: centralItems

        FontLoader { id: menuFont; source: "fonts/CinzelDecorative-Regular.ttf" }

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: (guiRoot.height / 3 - 100)

        spacing: (guiRoot.height / 30)

        Text {
            id: titleText
            
            anchors.horizontalCenter: parent.horizontalCenter

            font.family: menuFont.name
            font.pixelSize: 72
            font.letterSpacing: 10
            font.bold: false
            color: "#4D4500"

            text: "Queens Regicide"
        }

        Item {
            // force double space
            width: 1
            height: 1
        }

        MenuButton {
            id: mainButtonPlay
            
            anchors.horizontalCenter: parent.horizontalCenter

            styledText: "Play"

            onClicked: {
                guiRoot.showPlayMenu()
            }
        }

        MenuButton {
            id: mainButtonOptions
            
            anchors.horizontalCenter: parent.horizontalCenter

            styledText: "Options"

            onClicked: {
                guiRoot.showOptionsMenu()
            }
        }
        
        Item {
            // force double space
            width: 1
            height: 1
        }

        MenuButton {
            id: mainButtonQuit
            
            anchors.horizontalCenter: parent.horizontalCenter

            styledText: "Quit"

            onClicked: {
                Qt.quit()
            }
        }
    }

    MenuButtonSmall {
        id: mainButtonCredits
        anchors.left: parent.left
        anchors.leftMargin: 40
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 30
        styledText: "Credits"

        onClicked: {
            guiRoot.showCredits()
        }
    }
}


