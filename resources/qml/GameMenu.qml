//----------------------------------------------//
//	Author: Pavel Hranáč (xhrana02)				//
//	School: Vysoké učení technické v Brně		//
//	Faculty: Fakulta informačních technologií	//
//	Date: Spring 2018							//
//----------------------------------------------//

import QtQuick 2.7
import QtQuick.Controls 1.4

Item {
    id: gameMenu

    FontLoader { id: menuFont; source: "fonts/CinzelDecorative-Regular.ttf" }

    Rectangle {
        anchors.fill: parent
        color: "#D0101010"

        MenuButton {
            id: gameMenuButtonContinue
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: (parent.height / 4)
            styledText: "Continue"

            onClicked: gameOverlay.gameContinue()
        }

        MenuButton {
            id: gameMenuButtonTEMP
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: gameMenuButtonContinue.bottom
            anchors.topMargin: (parent.height / 15)
            styledText: "TEMP"

            onClicked: guiRoot.consoleWrite("This button does nothing")
        }

        MenuButton {
            id: gameMenuButtonTEMP2
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: gameMenuButtonTEMP.bottom
            anchors.topMargin: (parent.height / 30)
            styledText: "TEMP2"

            onClicked: guiRoot.consoleWrite("This button does nothing")
        }

        MenuButton {
            id: gameMenuButtonToTitle
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: gameMenuButtonTEMP2.bottom
            anchors.topMargin: (parent.height / 15)
            styledText: "To title"

            onClicked: {
                gameOverlay.cleanUI()
                guiRoot.showMainMenu()
            } 
        }

        MenuButton {
            id: gameMenuButtonQuit
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: gameMenuButtonToTitle.bottom
            anchors.topMargin: (parent.height / 30)
            styledText: "Quit"

            onClicked: Qt.quit()
        }
    }
    
}