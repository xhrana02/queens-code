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
    property var textColor: "#F0E0A8"

    property bool paused: false

    Loader {
        id: loaderGameMenu
        z: 10
        anchors.fill: parent
        source: "GameMenu.qml"
        visible: false
    }

    // MOUSE EVENTS
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

    Item {
        id: gameUI

        anchors.fill: parent

        // LEFT SIDE
        Column {
            id: gameUI_topLeft
        
            anchors.top: parent.top
            anchors.topMargin: 20
            anchors.left: parent.left
            anchors.leftMargin: 20

            spacing: 10

            Text {
                id: activePlayerName

                anchors.left: parent.left

                color: gameOverlay.textColor
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 22
                font.bold: true
                font.family: menuFont.name
                textFormat: Text.StyledText
                style: Text.Raised
                styleColor: "#CC000000"
            }

            Text {
                id: turnCounter

                anchors.left: parent.left

                property int turnNumber: 0

                color: gameOverlay.textColor
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 20
                font.bold: true
                font.family: menuFont.name
                style: Text.Raised
                styleColor: "#CC000000"

                text: "turn " + turnNumber
            }

            Text {
                id: selectedUnitIndicator

                anchors.left: parent.left

                color: gameOverlay.textColor
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 20
                font.bold: true
                font.family: menuFont.name
                style: Text.Raised
                styleColor: "#CC000000"
            }
        }

        // MIDDLE
        Text {
            id: popupText

            anchors.horizontalCenter: parent.horizontalCenter

            color: gameOverlay.textColor
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 22
            font.bold: true
            font.family: menuFont.name
            textFormat: Text.StyledText
            style: Text.Raised
            styleColor: "#CC000000"

            ParallelAnimation {
                id: popupAnimation

                YAnimator {
                    id: popupAnimationYpos

                    target: popupText
                    easing.type: Easing.InQuint
                    from: 100
                    to: -100
                    duration: 5000
                }
                
                OpacityAnimator {
                    id: popupAnimationOpacity

                    target: popupText
                    easing.type: Easing.InQuint
                    from: 1
                    to: 0
                    duration: 5000
                }

            }
        }

        // RIGHT SIDE
        Column {
            id: gameUI_topRight
        
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

                spacing: 15

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
    }
    
    
    // KEYBOARD EVENTS
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

    // FUNCTIONS
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
    
    function setActivePlayer(playerName) {
        activePlayerName.text = playerName
    }

    function onUnitSelected(unitName) {
        selectedUnitIndicator.text = unitName + " selected"
    }
    
    function onUnitUnselected() {
        selectedUnitIndicator.text = ""
    }

    function onTurnBegin(turnNumber) {
        commandPointIndicator1.used = false
        commandPointIndicator2.used = false
        commandPointIndicator3.used = false
        turnCounter.turnNumber = turnNumber
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

    function popup(message) {
        popupText.text = message
        popupAnimation.restart()
    }

    function cleanUI() {
        loaderGameMenu.visible = false;
        gameUI.visible = true;
        paused = false
    }

    function showGameMenu() {
        loaderGameMenu.visible = true;
        gameUI.visible = false;
    }

    function hideGameMenu() {
        loaderGameMenu.visible = false;
        gameUI.visible = true;
    }
}

