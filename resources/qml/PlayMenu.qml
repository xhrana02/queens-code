//----------------------------------------------//
//  Author: Pavel Hranáč (xhrana02)             //
//  School: Vysoké učení technické v Brně       //
//  Faculty: Fakulta informačních technologií   //
//  Date: Spring 2018                           //
//----------------------------------------------//

import QtQuick 2.7

Item {
    id: playMenu

    property string selectedMode: "Standard"

    MenuButtonSmall {
        id: playButtonStandard
        anchors.left: playMainContainer.left
        anchors.bottom: playMainContainer.top
        anchors.bottomMargin: -1
        styledText: "Standard"

        Rectangle {
            id: visualStandardSelected
            visible: true
            width: parent.width - 2
            height: 1
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.bottom
            anchors.topMargin: -1
            color: "#EADCA8"
        }

        onClicked: {
            selectGameType("Standard")
        }
    }

    MenuButtonSmall {
        id: playButtonScenario
        anchors.left: playButtonStandard.right
        anchors.leftMargin: 1
        anchors.bottom: playMainContainer.top
        anchors.bottomMargin: -1
        styledText: "Scenario"

        Rectangle {
            id: visualScenarioSelected
            visible: false
            width: parent.width - 2
            height: 1
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.bottom
            anchors.topMargin: -1
            color: "#EADCA8"
        }

        onClicked: {
            selectGameType("Scenario")
        }
    }

    Rectangle {
        id: playMainContainer
        width: (guiRoot.width / 4 + 600)
        height: (guiRoot.height / 4 + 300)
        anchors.centerIn: parent
        z: -1
        
        color: "#F0EDDFAB"
        border.width: 1
        border.color: "#F05F581A"

        Loader {
            id: loaderStandardSetup
            anchors.fill: parent
            source: "PlayStandardSetup.qml"
            visible: true
        }
        
        Loader {
            id: loaderScenarioSetup
            anchors.fill: parent
            source: "PlayScenarioSetup.qml"
            visible: false
        }
    }

    MenuButton {
        id: playButtonStart
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: playMainContainer.bottom
        anchors.topMargin: 25
        styledText: "Start"

        onClicked: {
            startGame()
        }
    }

    MenuButtonSmall {
        id: playButtonBack
        anchors.right: parent.right
        anchors.rightMargin: ((guiRoot.width - 800) * 3 / 8)
        anchors.top: playMainContainer.bottom
        anchors.topMargin: 33
        styledText: "Back"

        onClicked: {
            cleanUI()
            guiRoot.showMainMenu()
        }
    }

    function selectGameType(type) {
        if(selectedMode == type) return

        switch(type){
            case "Standard":
                showStandardSetup()
                break
            case "Scenario":
                showScenarioSetup()
                break
            default:
                guiRoot.consoleWrite("ERROR:PlayMenu.qml - Unknown game type")
                return
        }

        selectedMode = type;
    }

    function startGame() {
        switch(selectedMode){
            case "Standard":
                loaderStandardSetup.item.startGame()
                cleanUI()
                break
            case "Scenario":
                if (loaderScenarioSetup.item.startGame()){
                    cleanUI()
                }
                break
            default:
                guiRoot.consoleWrite("ERROR:PlayMenu.qml - Unknown game type")
                return
        }
    }

    function cleanUI() {
        loaderStandardSetup.item.cleanUI()
        loaderScenarioSetup.item.cleanUI()
    }

    function showStandardSetup() {
        cleanUI()
        loaderStandardSetup.visible    = true
        loaderScenarioSetup.visible    = false
        
        visualStandardSelected.visible = true
        visualScenarioSelected.visible = false
    }

    function showScenarioSetup() {
        cleanUI()
        loaderStandardSetup.visible    = false
        loaderScenarioSetup.visible    = true
        
        visualStandardSelected.visible = false
        visualScenarioSelected.visible = true
    }
}

