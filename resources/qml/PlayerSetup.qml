//----------------------------------------------//
//  Author: Pavel Hranáč (xhrana02)             //
//  School: Vysoké učení technické v Brně       //
//  Faculty: Fakulta informačních technologií   //
//  Date: Spring 2018                           //
//----------------------------------------------//

import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

Item {
    id: playerSetup

    property string playerText
    property string playerName

    FontLoader { id: menuFont; source: "fonts/CinzelDecorative-Regular.ttf" }

    width: parent.width

    Item {
        id: playerNameItem

        visible: humanButton.checked

        height: 24

        anchors.top: parent.top
        anchors.right: parent.right

        Text {
            width: 80
            height: 24

            anchors.top: parent.top
            anchors.right: playerNameInput.left
            anchors.rightMargin: 15

            color: "#4D4500"
            horizontalAlignment: Text.AlignRight
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: 16
            font.bold: true
            font.family: menuFont.name
            text: "Name:"
        } 

        TextField {
            id: playerNameInput
     
            anchors.top: parent.top       
            anchors.right: parent.right

            width: 140
            height: 24

            maximumLength: 32
            
            font.pixelSize: 16
            font.family: "Cambria"
            textColor: "#504800"

            text: playerSetup.playerName
        }
    }

    Column{
        spacing: 10

        Row{
            id: controlRow
            spacing: 5
            
            Text {
                width: 100
                color: "#4D4500"
                verticalAlignment: Text.AlignVCenter
                font.pixelSize: 16
                font.bold: true
                font.family: menuFont.name
                text: playerSetup.playerText
            } 

            ExclusiveGroup {
                id: controlGroup
            }

            MenuButtonDialog {
                id: humanButton
                styledText: "Human"
                checked: true
                exclusiveGroup: controlGroup
            }
            MenuButtonDialog {
                id: aiButton
                styledText: "AI"
                exclusiveGroup: controlGroup
            }
        }

        Row{
            id: aiRow
            spacing: 5

            visible: aiButton.checked

            Rectangle {
                color: "#00000000"
                width: 100
                height: 1
            }

            ExclusiveGroup {
                id: aiGroup
            }

            MenuButtonDialog {
                styledText: "Easy"
                checked: true
                exclusiveGroup: aiGroup
            }
            MenuButtonDialog {
                styledText: "Normal"
                exclusiveGroup: aiGroup
            }
            MenuButtonDialog {
                styledText: "Hard"
                exclusiveGroup: aiGroup
            }
        }
    }

    function name2string() {
        if(controlGroup.current == humanButton){
            if(playerNameInput.text != "")
            {
                return (playerNameInput.text)
            }
            else
            {
                return "Unnamed Player"
            }
        }
        else
        {
            return (aiGroup.current.styledText + " AI")
        }
    }

    function encodePlayerType() {
        if(controlGroup.current == aiButton)
        {
            if(aiGroup.current.styledText == "Easy")
            {
                return 1
            }
            if(aiGroup.current.styledText == "Normal")
            {
                return 2
            }
            if(aiGroup.current.styledText == "Hard")
            {
                return 3
            }
        }
        return 0
    }

    function cleanUI() {
        playerNameInput.focus = false;
    }
}

