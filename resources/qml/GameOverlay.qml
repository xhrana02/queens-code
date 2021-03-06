//----------------------------------------------//
//  Author: Pavel Hranáč (xhrana02)             //
//  School: Vysoké učení technické v Brně       //
//  Faculty: Fakulta informačních technologií   //
//  Date: Spring 2018                           //
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

        Rectangle {
            id: gameOverScreen
            anchors.fill: parent
            color: "#88484840"
            visible: false
        }

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
                font.pixelSize: 18
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
            font.pixelSize: 30
            font.bold: true
            textFormat: Text.StyledText
            style: Text.Outline
            styleColor: "#CC000000"

            ParallelAnimation {
                id: popupAnimation

                YAnimator {
                    id: popupAnimationYpos

                    target: popupText
                    easing.type: Easing.InQuint
                    from: 150
                    to: -100
                    duration: 6000
                }
                
                OpacityAnimator {
                    id: popupAnimationOpacity

                    target: popupText
                    easing.type: Easing.InQuint
                    from: 1
                    to: 0
                    duration: 6000
                }

            }
        }

        Text {
            id: isAiThinkingText

            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 30

            visible: false

            color: gameOverlay.textColor
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 32
            font.letterSpacing: 4
            font.bold: true
            font.family: menuFont.name
            style: Text.Raised
            styleColor: "#CC000000"

            text: "AI is thinking..."
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

                anchors.right: parent.right

                styledText: "<b>end turn</b>"

                onClicked: {
                    ApplicationControl.EndTurn()
                }
            }

            Row {
                id: commandPointIndicators

                anchors.horizontalCenter: endTurnButton.horizontalCenter

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

            Text {
                id: commandPointsLeftText

                anchors.right: parent.right

                property int pointsLeft: 0

                color: gameOverlay.textColor
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 18
                font.bold: true
                font.family: menuFont.name
                style: Text.Raised
                styleColor: "#CC000000"

                text: pointsLeft + " commands left"
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

    function onTurnBegin(turnNumber, isAi) {
        commandPointIndicator1.used = false
        commandPointIndicator2.used = false
        commandPointIndicator3.used = false
        commandPointsLeftText.pointsLeft = 3
        turnCounter.turnNumber = turnNumber
        gameUI_topRight.visible = !isAi
    }

    function onAbilityUsed() {
        if (!commandPointIndicator1.used) {
            commandPointIndicator1.used = true
            commandPointsLeftText.pointsLeft = 2
        }
        else if (!commandPointIndicator2.used) {
            commandPointIndicator2.used = true
            commandPointsLeftText.pointsLeft = 1
        }
        else {
            commandPointIndicator3.used = true
            commandPointsLeftText.pointsLeft = 0
        }
    }

    function popup(message) {
        popupText.text = message
        popupAnimation.restart()
    }
    
    function onGameOver() {
        gameOverScreen.visible = true
        activePlayerName.font.pixelSize = 40
    }
    
    function isAiThinking(isThinking) {
        isAiThinkingText.visible = isThinking
    }

    function cleanUI() {
        loaderGameMenu.visible = false
        gameUI.visible = true
        paused = false
        gameOverScreen.visible = false
        activePlayerName.font.pixelSize = 22
    }

    function showGameMenu() {
        loaderGameMenu.visible = true
        gameUI.visible = false
    }

    function hideGameMenu() {
        loaderGameMenu.visible = false
        gameUI.visible = true
    }
}

