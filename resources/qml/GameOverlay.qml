//----------------------------------------------//
//	Author: Pavel Hranáč (xhrana02)				//
//	School: Vysoké učení technické v Brně		//
//	Faculty: Fakulta informačních technologií	//
//	Date: Spring 2018							//
//----------------------------------------------//

import QtQuick 2.7
import QtQuick.Controls 1.4

Item {
    id: gameOverlay

    FontLoader { id: menuFont; source: "fonts/CinzelDecorative-Regular.ttf" }

    property bool paused: false

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true
        acceptedButtons: Qt.AllButtons
        
        onPositionChanged: {
            ApplicationControl.OnMouseMovement(mouse.buttons, mouse.x, mouse.y)
            mouse.accepted = true
        }
        
        onPressed: {
            ApplicationControl.OnMouseClick(mouse.buttons, mouse.x, mouse.y)
            mouse.accepted = true
        }

        onWheel: {
            ApplicationControl.OnWheelEvent(wheel.angleDelta.y)
            wheel.accepted = true
        }
    }

    Loader {
        id: loaderGameMenu
        anchors.fill: parent
        source: "GameMenu.qml"
        visible: false
    }
    
    Keys.onEscapePressed: {
        toggleGamePause()
    }  

    Keys.onPressed: {
        if(event.isAutoRepeat == false) {
            ApplicationControl.OnKeyPressed(event.nativeScanCode)
        }
    }

    Keys.onReleased: {
        if(event.isAutoRepeat == false) {
            ApplicationControl.OnKeyReleased(event.nativeScanCode)
        }
    }

    function toggleGamePause() {
        if (paused == false) {
            gamePause()
        } else {
            gameContinue()
        }
    }

    function gamePause() {
        guiRoot.gamePause()
        showGameMenu()
        paused = true
    }

    function gameContinue() {
        hideGameMenu()
        guiRoot.gameContinue()
        paused = false
    }

    function cleanUI() {
        loaderGameMenu.visible = false;
        paused = false
    }

    function showGameMenu() {
        loaderGameMenu.visible = true;
    }

    function hideGameMenu() {
        loaderGameMenu.visible = false;
    }
}

