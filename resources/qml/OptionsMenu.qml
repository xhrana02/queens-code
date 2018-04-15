//----------------------------------------------//
//	Author: Pavel Hranáč (xhrana02)				//
//	School: Vysoké učení technické v Brně		//
//	Faculty: Fakulta informačních technologií	//
//	Date: Spring 2018							//
//----------------------------------------------//

import QtQuick 2.7
import QtQuick.Controls 1.4

Item {
    id: optionsMenu

    Rectangle{
        anchors.fill: parent
        color: "#80808080"
        z: -10
    }

    MenuButton {
        id: optionsButtonName
        x: ((guiRoot.width / 2.618) - 200)
        anchors.top: parent.top
        anchors.topMargin: ((guiRoot.height / 4) - 25)
        styledText: "Player"

        onClicked: {
            showPlayerOptions()
        }
    }

    TextField {
        id: optionsNameInput

        visible: false
        anchors.left: optionsButtonName.right
        anchors.leftMargin: 20
        anchors.top: optionsButtonName.anchors.top
        anchors.topMargin: (optionsButtonName.anchors.topMargin + 8)

        width: 200
        height: 34

        maximumLength: 32
        
        font.pixelSize: 20
        font.family: "Cambria"
        textColor: "#504800"

        text: settings.playerName

        onEditingFinished: {
            settings.playerName = text
        }
    }


    MenuButton {
        id: optionsButtonDisplay
        x: optionsButtonName.x
        anchors.top: optionsButtonName.bottom
        anchors.topMargin: (guiRoot.height / 30)
        styledText: "Display"

        onClicked: {
            showDisplayOptions()
        }
    }

    MenuButtonSmall {
        id: optionsButtonWindowed
        visible: false
        anchors.left: optionsButtonDisplay.right
        anchors.leftMargin: 20
        anchors.top: optionsButtonDisplay.anchors.top
        anchors.topMargin: (optionsButtonDisplay.anchors.topMargin + 8)
        styledText: "windowed"

        onClicked: {
            guiRoot.windowed()
            settings.fullscreen = false
        }
    }
    
    MenuButtonSmall {
        id: optionsButtonFullscreen
        visible: false
        anchors.left: optionsButtonWindowed.right
        anchors.leftMargin: 20
        anchors.top: optionsButtonDisplay.anchors.top
        anchors.topMargin: (optionsButtonDisplay.anchors.topMargin + 8)
        styledText: "fullscreen"
        
        onClicked: {
            guiRoot.fullscreen()
            settings.fullscreen = true
        }
    }

    MenuButton {
        id: optionsButtonBack
        x: optionsButtonName.x
        anchors.bottom: parent.bottom
        anchors.bottomMargin: optionsButtonName.anchors.topMargin
        styledText: "Back"

        onClicked: {
            cleanUI()
            guiRoot.showMainMenu()
        }
    }

    function cleanUI() {
        optionsNameInput.visible = false
        optionsNameInput.focus = false
        optionsButtonWindowed.visible = false
        optionsButtonFullscreen.visible = false
    }

    function showPlayerOptions() {
        cleanUI()
        optionsNameInput.visible = true
        optionsNameInput.focus = true
    }

    function showDisplayOptions() {
        cleanUI()
        optionsButtonWindowed.visible = true
        optionsButtonFullscreen.visible = true
    }
}

