//----------------------------------------------//
//	Author: Pavel Hranáč (xhrana02)				//
//	School: Vysoké učení technické v Brně		//
//	Faculty: Fakulta informačních technologií	//
//	Date: Spring 2018							//
//----------------------------------------------//

import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

Item {
    id: scenarioSetup

    FontLoader { id: menuFont; source: "fonts/CinzelDecorative-Regular.ttf" }

    property string selectedScenario: "none"
    property string selectedDescription
    
    TableView {
        id: scenariosTable

        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: descriptionContainer.top
        anchors.margins: 20

        model: ListModel {
            id: scenariosList

            ListElement {
                name: "Training Duel"
                difficulty: "Easy"
                description: "Tutorial scenario where you can get a feel for the controls and mechanics of the game."
            }

            ListElement {
                name: "Chess"
                difficulty: "Hard"
                description: "Chess adaptation.<br>King =>> Queen<br>Queen =>> Warlock<br>Rook =>> Brute<br>Bishop =>> Priest<br>Knight =>> Agent<br>Pawn =>> Spearman"
            }
        }

        TableViewColumn {
            role: "name"
            title: "Name"
            movable: false
            resizable: false
            width: 300
        }

        TableViewColumn {
            role: "difficulty"
            title: "Difficulty"
            movable: false
            resizable: false
            width: 200
        }

        itemDelegate: Item {
            Text {
                anchors.verticalCenter: parent.verticalCenter
                font.pixelSize: 15
                font.family: menuFont.name
                color: "#4D4500"
                text: styleData.value
            }
        }

        onClicked: {
            scenarioSetup.selectedScenario = scenariosList.get(row).name
            scenarioSetup.selectedDescription = scenariosList.get(row).description
        }

    }

    Rectangle {
        id: descriptionContainer

        width: parent.width
        height: 200
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        
        color: "#00000000"
        border.width: 1
        border.color: "#E05F581A"

        TextArea {
            id: descriptionText
            readOnly: true
            backgroundVisible: false;
            frameVisible: false;
            anchors.fill: parent
            anchors.margins: 20

            wrapMode: Text.WordWrap
            verticalAlignment: Text.AlignTop
            font.pixelSize: 13
            textColor: "#504800"
            textFormat: TextEdit.RichText

            text: scenarioSetup.selectedDescription
        }
    }
    
    function startGame() {
        if (scenarioSetup.selectedScenario != "none") {
            guiRoot.consoleWrite("Starting a custom scenario game:")
            ApplicationControl.NewScenarioGame(scenarioSetup.selectedScenario)
            return true
        }
        return false
    }

    function cleanUI() {
        scenariosTable.selection.clear()    
        scenarioSetup.selectedScenario = "none"
    }
}

