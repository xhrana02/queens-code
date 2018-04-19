//----------------------------------------------//
//	Author: Pavel Hranáč (xhrana02)				//
//	School: Vysoké učení technické v Brně		//
//	Faculty: Fakulta informačních technologií	//
//	Date: Spring 2018							//
//----------------------------------------------//

import QtQuick 2.7
import QtQuick.Controls 1.4

Rectangle {
    anchors.fill: parent
    color: "#D0101010"

    FontLoader { id: menuFont; source: "fonts/CinzelDecorative-Regular.ttf" }

    Column {
        id: gameMenu

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: (guiRoot.height / 3 - 100)

        spacing: (guiRoot.height / 30)
        
        MenuButton {
            id: gameMenuButtonContinue

            anchors.horizontalCenter: parent.horizontalCenter

            styledText: "Continue"

            onClicked: gameOverlay.gameContinue()
        }
    
        Item {
            // force double space
            width: 1
            height: 1
        }

        MenuButton {
            id: gameMenuButtonTEMP

            anchors.horizontalCenter: parent.horizontalCenter

            styledText: "TEMP"

            onClicked: guiRoot.consoleWrite("This button does nothing")
        }

        MenuButton {
            id: gameMenuButtonOptions

            anchors.horizontalCenter: parent.horizontalCenter

            styledText: "Options"

            onClicked: guiRoot.showOptionsMenu()
        }
    
        Item {
            // force double space
            width: 1
            height: 1
        }

        MenuButton {
            id: gameMenuButtonToTitle

            anchors.horizontalCenter: parent.horizontalCenter

            styledText: "To title"

            onClicked: {
                gameOverlay.cleanUI()
                guiRoot.showMainMenu()
            } 
        }

        MenuButton {
            id: gameMenuButtonQuit

            anchors.horizontalCenter: parent.horizontalCenter

            styledText: "Quit"

            onClicked: Qt.quit()
        }
    }
}