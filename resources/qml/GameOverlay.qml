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

    Loader {
        id: loaderGameMenu
        anchors.fill: parent
        source: "GameMenu.qml"
        visible: false
    }

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

    Column {
        id: turnRelatedUI
    
        anchors.top: parent.top
        anchors.topMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 20

        spacing: 10

        MenuButtonSmall {
            id: endTurnButton

            styledText: "<b>end turn</b>"

            onClicked: {
                ApplicationControl.EndTurn()
            }
        }

        Row {
            id: commandPointIndicators

            anchors.horizontalCenter: parent.horizontalCenter

            spacing: 10

            PlayerCommandPointIndicator {
                id: commandPointIndicator1
            }

            PlayerCommandPointIndicator {
                id: commandPointIndicator2
            }

            PlayerCommandPointIndicator {
                id: commandPointIndicator3
            }
        }

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
    
    function onTurnBegin() {
        commandPointIndicator1.used = false
        commandPointIndicator2.used = false
        commandPointIndicator3.used = false
    }

    function onAbilityUsed() {
        if (!commandPointIndicator1.used) {
            commandPointIndicator1.used = true
        }
        else if (!commandPointIndicator2.used) {
            commandPointIndicator2.used = true
        }
        else {
            commandPointIndicator3.used = true
        }
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

