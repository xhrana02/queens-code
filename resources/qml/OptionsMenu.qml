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
    
    property var screenTopMargin: ((guiRoot.height / 6) - 30)
    property var screenBottomMargin: ((guiRoot.height / 6) - 30)
    property var screenLeftMargin: ((guiRoot.width / 6) - 30)
    property var screenRightMargin: ((guiRoot.width / 6) - 30)
    property var bigVerticalMargin: (guiRoot.height / 30)
    property var smallVerticalMargin: (guiRoot.height / 40)
    property var bigHorizontalMargin: (guiRoot.width / 30)
    property var smallHorizontalMargin: (guiRoot.width / 40)
    property var labelsColor: "#FFFCE6"

    FontLoader { id: menuFont; source: "fonts/CinzelDecorative-Regular.ttf" }

    Rectangle{
        anchors.fill: parent
        color: "#B0181818"
        z: -10
    }

    // SECTION BUTTONS
    Column {
        id: optionsSectionButtons

        anchors.top: parent.top
        anchors.topMargin: optionsMenu.screenTopMargin
        anchors.left: parent.left
        anchors.leftMargin: optionsMenu.screenLeftMargin

        spacing: optionsMenu.bigVerticalMargin

        MenuButton {
            id: optionsButtonGame

            styledText: "Game"

            onClicked: {
                showGameOptions()
            }
        }

        MenuButton {
            id: optionsButtonDisplay

            styledText: "Display"

            onClicked: {
                showDisplayOptions()
            }
        }

        MenuButton {
            id: optionsButtonControl

            styledText: "Control"

            onClicked: {
                showControlOptions()
            }
        }

    }
    // SECTION BUTTONS END

    // GAME OPTIONS SECTION
    Grid {
        id: gameOptions

        visible: false
        anchors.top: parent.top
        anchors.topMargin: screenTopMargin + optionsMenu.bigVerticalMargin
        anchors.left: optionsSectionButtons.right
        anchors.leftMargin: optionsMenu.bigHorizontalMargin

        columns: 2
        rows: 2
        spacing: optionsMenu.smallHorizontalMargin
        rowSpacing: optionsMenu.smallVerticalMargin
        horizontalItemAlignment: Grid.AlignLeft
        verticalItemAlignment: Grid.AlignVCenter

        Text {
            id: optionsPlayer1NameLabel

            font.family: menuFont.name
            font.pixelSize: 17
            font.bold: true
            color: optionsMenu.labelsColor

            text: "player 1 default name:"
        }

        TextField {
            id: optionsPlayer1NameInput

            width: 200
            height: 34

            maximumLength: 32
            
            font.family: "Cambria"
            font.pixelSize: 20
            textColor: "#504800"

            text: settings.player1Name
        }

        Text {
            id: optionsPlayer2NameLabel

            font.family: menuFont.name
            font.pixelSize: 17
            font.bold: true
            color: optionsMenu.labelsColor

            text: "player 2 default name:"
        }

        TextField {
            id: optionsPlayer2NameInput

            width: 200
            height: 34

            maximumLength: 32
            
            font.family: "Cambria"
            font.pixelSize: 20
            textColor: "#504800"

            text: settings.player2Name
        }
    }
    // GAME OPTIONS SECTION END

    // DISPLAY OPTIONS SECTION
    Grid {
        id: displayOptions

        visible: false
        anchors.top: parent.top
        anchors.topMargin: screenTopMargin + optionsMenu.bigVerticalMargin
        anchors.left: optionsSectionButtons.right
        anchors.leftMargin: optionsMenu.bigHorizontalMargin

        columns: 3
        rows: 1
        spacing: optionsMenu.smallHorizontalMargin
        rowSpacing: optionsMenu.smallVerticalMargin
        horizontalItemAlignment: Grid.AlignLeft
        verticalItemAlignment: Grid.AlignVCenter

        property bool fullscreen: settings.fullscreen

        Text {
            id: optionsWindowModeLabel

            font.family: menuFont.name
            font.pixelSize: 17
            font.bold: true
            color: optionsMenu.labelsColor

            text: "window mode:"
        }
        
        MenuButtonSmall {
            id: optionsButtonFullscreen

            styledText: "fullscreen"
            
            onClicked: {
                guiRoot.fullscreen()
                displayOptions.fullscreen = true
            }
        }
        
        MenuButtonSmall {
            id: optionsButtonWindowed

            styledText: "windowed"

            onClicked: {
                guiRoot.windowed()
                displayOptions.fullscreen = false
            }
        }
    }
    // DISPLAY OPTIONS SECTION END

    // CONTROL OPTIONS SECTION
    Grid {
        id: controlOptions

        visible: false
        anchors.top: parent.top
        anchors.topMargin: screenTopMargin + optionsMenu.bigVerticalMargin
        anchors.left: optionsSectionButtons.right
        anchors.leftMargin: optionsMenu.bigHorizontalMargin

        columns: 3
        rows: 4
        spacing: optionsMenu.smallHorizontalMargin
        rowSpacing: optionsMenu.smallVerticalMargin
        horizontalItemAlignment: Grid.AlignLeft
        verticalItemAlignment: Grid.AlignVCenter

        // ROTATE
        Text {
            id: optionsRotateSensitivityLabel

            font.family: menuFont.name
            font.pixelSize: 17
            font.bold: true
            color: optionsMenu.labelsColor

            text: "rotate sensitivity:"
        }

        Slider {
            id: optionsRotateSensitivitySlider

            width: 200
            stepSize: 0.05

            value: settings.rotateSensitivity
        }
        
        Text {
            font.family: menuFont.name
            font.pixelSize: 17
            font.bold: true
            color: optionsMenu.labelsColor

            text: optionsRotateSensitivitySlider.value * 100 + "%"
        }

        // PAN MOUSE
        Text {
            id: optionsPanMouseSensitivityLabel

            font.family: menuFont.name
            font.pixelSize: 17
            font.bold: true
            color: optionsMenu.labelsColor

            text: "pan (mouse) sensitivity:"
        }

        Slider {
            id: optionsPanMouseSensitivitySlider

            width: 200
            stepSize: 0.05

            value: settings.panMouseSensitivity
        }
        
        Text {
            font.family: menuFont.name
            font.pixelSize: 17
            font.bold: true
            color: optionsMenu.labelsColor

            text: optionsZoomSensitivitySlider.value * 100 + "%"
        }

        // PAN KEYBOARD
        Text {
            id: optionsPanKeyboardSensitivityLabel

            font.family: menuFont.name
            font.pixelSize: 17
            font.bold: true
            color: optionsMenu.labelsColor

            text: "pan (keyboard) sensitivity:"
        }

        Slider {
            id: optionsPanKeyboardSensitivitySlider

            width: 200
            stepSize: 0.05

            value: settings.panKeyboardSensitivity
        }
        
        Text {
            font.family: menuFont.name
            font.pixelSize: 17
            font.bold: true
            color: optionsMenu.labelsColor

            text: optionsZoomSensitivitySlider.value * 100 + "%"
        }
        
        // ZOOM
        Text {
            id: optionsZoomSensitivityLabel

            font.family: menuFont.name
            font.pixelSize: 17
            font.bold: true
            color: optionsMenu.labelsColor

            text: "zoom sensitivity:"
        }

        Slider {
            id: optionsZoomSensitivitySlider

            width: 200
            stepSize: 0.05

            value: settings.zoomSensitivity
        }
        
        Text {
            font.family: menuFont.name
            font.pixelSize: 17
            font.bold: true
            color: optionsMenu.labelsColor

            text: optionsZoomSensitivitySlider.value * 100 + "%"
        }

    }
    // CONTROL OPTIONS SECTION END

    // CONTROL BUTTONS
    MenuButton {
        id: optionsButtonOK

        anchors.bottom: parent.bottom
        anchors.bottomMargin: optionsMenu.screenBottomMargin
        anchors.left: parent.left
        anchors.leftMargin: optionsMenu.screenLeftMargin

        styledText: "OK"

        onClicked: {
            saveOptions()
            cleanUI()
            guiRoot.closeOptionsMenu()
        }
    }
    
    MenuButton {
        id: optionsButtonCancel

        anchors.bottom: parent.bottom
        anchors.bottomMargin: optionsMenu.screenBottomMargin
        anchors.horizontalCenter: parent.horizontalCenter

        styledText: "Cancel"

        onClicked: {
            revertOptions()
            cleanUI()
            guiRoot.closeOptionsMenu()
        }
    }
    
    MenuButton {
        id: optionsButtonDefault

        anchors.bottom: parent.bottom
        anchors.bottomMargin: optionsMenu.screenBottomMargin
        anchors.right: parent.right
        anchors.rightMargin: optionsMenu.screenRightMargin

        styledText: "Default"

        onClicked: {
            defaultOptions()
        }
    }
    // CONTROL BUTTONS END

    // FUNCTIONS
    function cleanUI() {
        optionsPlayer1NameInput.focus = false
        optionsPlayer2NameInput.focus = false

        gameOptions.visible = false
        displayOptions.visible = false
        controlOptions.visible = false
    }

    function showGameOptions() {
        cleanUI()
        gameOptions.visible = true
    }

    function showDisplayOptions() {
        cleanUI()
        displayOptions.visible = true
    }
    
    function showControlOptions() {
        cleanUI()
        controlOptions.visible = true
    }

    function saveOptions() {
        settings.player1Name = optionsPlayer1NameInput.text
        settings.player2Name = optionsPlayer2NameInput.text
        settings.fullscreen = displayOptions.fullscreen
        settings.rotateSensitivity = optionsRotateSensitivitySlider.value
        settings.panMouseSensitivity = optionsPanMouseSensitivitySlider.value
        settings.panKeyboardSensitivity = optionsPanKeyboardSensitivitySlider.value
        settings.zoomSensitivity = optionsZoomSensitivitySlider.value
        
        ApplicationControl.LoadSettings()
    }

    function revertOptions() {
        optionsPlayer1NameInput.text = settings.player1Name
        optionsPlayer2NameInput.text = settings.player2Name
        displayOptions.fullscreen = settings.fullscreen
        if(settings.fullscreen) {
            guiRoot.fullscreen()
        } else {
            guiRoot.windowed()
        }
        optionsRotateSensitivitySlider.value = settings.rotateSensitivity
        optionsPanMouseSensitivitySlider.value = settings.panMouseSensitivity
        optionsPanKeyboardSensitivitySlider.value = settings.panKeyboardSensitivity
        optionsZoomSensitivitySlider.value = settings.zoomSensitivity
    }

    function defaultOptions() {
        optionsPlayer1NameInput.text = "New player 1"
        optionsPlayer2NameInput.text = "New player 2"
        displayOptions.fullscreen = true
        guiRoot.fullscreen()
        optionsRotateSensitivitySlider.value = 0.5
        optionsPanMouseSensitivitySlider.value  = 0.5
        optionsPanKeyboardSensitivitySlider.value  = 0.5
        optionsZoomSensitivitySlider.value  = 0.5
    }
}

