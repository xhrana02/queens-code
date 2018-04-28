//----------------------------------------------//
//	Author: Pavel Hranáč (xhrana02)				//
//	School: Vysoké učení technické v Brně		//
//	Faculty: Fakulta informačních technologií	//
//	Date: Spring 2018							//
//----------------------------------------------//

import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import Qt.labs.settings 1.0


Item {
    id: guiRoot
    focus: true
    anchors.fill: parent
    width: 1280
    height: 720

    signal fullscreen()
    signal windowed()
    signal gamePause()
    signal gameContinue()
    signal gameEnd()

    property bool gameActive: false

    // Menu background image.
    Image {
        id: menuBackground
        anchors.fill: parent
        source: "images/main_background.jpg"
        fillMode: Image.PreserveAspectCrop
        z: 3
    }

    // Page loaders. Preloads all pages at startup.
    Loader {
        id: loaderMainMenu
        anchors.fill: parent
        source: "MainMenu.qml"
        visible: true
        z: 5
    }

    Loader {
        id: loaderPlayMenu
        anchors.fill: parent
        source: "PlayMenu.qml"
        visible: false
        z: 5
    }

    Loader {
        id: loaderOptionsMenu
        anchors.fill: parent
        source: "OptionsMenu.qml"
        visible: false
        z: 5
    }

    Loader {
        id: loaderGameOverlay
        anchors.fill: parent
        source: "GameOverlay.qml"
        visible: false
        z: 1
    }

    Rectangle {
        id: consoleContainer
        visible: false;
        width: (guiRoot.width / 2 + 400)
        height: (guiRoot.height / 6 + 200)
        color: "#E0EDDFAB"
        border.width: 1
        border.color: "#E05F581A"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom

        z: 10

        TextArea {
            id: consoleOutput
            readOnly: true
            backgroundVisible: false;
            frameVisible: false;
            anchors.fill: parent
            anchors.topMargin: 5
            anchors.bottomMargin: 25
            anchors.leftMargin: 1
            anchors.rightMargin: 1
            wrapMode: Text.WordWrap
            verticalAlignment: Text.AlignTop

            font.family: "Lucida Console"
            font.pixelSize: 13
            textColor: "#504800"
            text: ""
        }

        TextField {
            id: consoleInput
            height: 20
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.margins: 2
            font.family: "Lucida Console"
            font.pixelSize: 13
            textColor: "#504800"

            style: TextFieldStyle {
                background: Rectangle {
                    color: "#60FFFFFF"
                    Rectangle {
                       color: "#60000000" 
                       width: (parent.width + 2)
                       height: 1
                       anchors.horizontalCenter: parent.horizontalCenter
                       anchors.bottom: parent.top
                       anchors.bottomMargin: 1
                    }
                }
            }

            Keys.onEnterPressed: {
                consoleWrite(text)
                text = ""
            }

            Keys.onReturnPressed: {
                consoleWrite(text)
                text = ""
            }
        }
    }

    Settings {
        id: settings
        objectName: "settings"
        property string player1Name: "New player 1"
        property string player2Name: "New player 2"
        property bool fullscreen: true
        property real rotateSensitivity: 0.5
        property real panMouseSensitivity: 0.5
        property real panKeyboardSensitivity: 0.5
        property real zoomSensitivity: 0.5

    }

    Keys.forwardTo: gameActive ? [loaderGameOverlay.item] : [];
    Keys.onPressed: {
        if (event.key == Qt.Key_QuoteLeft) {
            toggleConsoleVisibility()
            event.accepted = true
        }
    }   

    function toggleConsoleVisibility() {
        consoleContainer.visible = !consoleContainer.visible
    }

    function consoleWrite(str) {
        consoleOutput.append(": " + str)
    }

    function cleanUI() {
        loaderMainMenu.visible      = false
        loaderPlayMenu.visible      = false
        loaderOptionsMenu.visible   = false
        loaderGameOverlay.visible   = false

        menuBackground.visible      = false
        if (gameActive) {
            gameEnd()
        }
        gameActive                  = false
    }

    function showMainMenu() {
        cleanUI()
        loaderMainMenu.visible      = true
        menuBackground.visible      = true
    }

    function showPlayMenu() {
        cleanUI()
        loaderPlayMenu.visible      = true
        menuBackground.visible      = true
    }

    function showOptionsMenu() {
        if (!gameActive) {
            cleanUI()
        }
        loaderOptionsMenu.visible   = true
        menuBackground.visible      = true
    }

    function closeOptionsMenu() {
        if (!gameActive) {
            showMainMenu()
        } else {
            loaderOptionsMenu.visible = false
            menuBackground.visible    = false
        }
    }

    function showGameOverlay() {
        cleanUI()
        loaderGameOverlay.visible   = true
        gameActive                  = true
    }

    function setActivePlayer(playerName) {
        loaderGameOverlay.item.setActivePlayer(playerName)
    }
    
    function onUnitSelected(unitName) {
        loaderGameOverlay.item.onUnitSelected(unitName)
    }
    
    function onUnitUnselected() {
        loaderGameOverlay.item.onUnitUnselected()
    }

    function onTurnBegin(turnNumber) {
        loaderGameOverlay.item.onTurnBegin(turnNumber)
    }

    function onAbilityUsed() {
        loaderGameOverlay.item.onAbilityUsed()
    }

    function gamePopup(message) {
        loaderGameOverlay.item.popup(message)
    }


}

