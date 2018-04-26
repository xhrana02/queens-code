//----------------------------------------------//
//	Author: Pavel Hranáč (xhrana02)				//
//	School: Vysoké učení technické v Brně		//
//	Faculty: Fakulta informačních technologií	//
//	Date: Spring 2018							//
//----------------------------------------------//

import QtQuick 2.7
import QtQuick.Controls 1.4

Item {
    id: abilityRoot

    width: 0
    height: 60

    property string name
    property string iconSource
    property string description
    property bool selectable
    property bool selected: false

    property var borderColor: "#5F581A"
    property var borderSelectedColor: "#FFFF99"

    Rectangle {
        id: abilityIconContainer

        anchors.fill: parent
        
        color: "#00000000"
        border.width: abilityRoot.selectable ? 5 : 0
        border.color: abilityRoot.selected ? abilityRoot.borderSelectedColor : abilityRoot.borderColor
        radius: 1

        Image {
            id: abilityIcon

            anchors.fill: parent
            fillMode: Image.Stretch

            source: abilityRoot.iconSource
        }
    }

    Rectangle {
        id: abilityDescriptionContainer

        width: 320
        height: abilityDescriptionText.contentHeight + 20;

        anchors.bottom: abilityRoot.top
        anchors.bottomMargin: 10
        anchors.left: abilityRoot.left

        visible: false

        color: "#CC000000"
        border.width: 3
        border.color: abilityRoot.borderColor
        radius: 1

        Text {
            id: abilityDescriptionText

            anchors.fill: parent
            anchors.margins: 10

            textFormat: Text.StyledText
            wrapMode: Text.Wrap
            font.pixelSize: 13
            color: "#FFFCE6"

            text: abilityRoot.description
        }
    }
    
    MouseArea {
        id: mouseCatcher

        anchors.fill: parent

        hoverEnabled: true
        acceptedButtons: Qt.LeftButton | Qt.RightButton

        onEntered: {
            abilityDescriptionContainer.visible = true
        }

        onExited: {
            abilityDescriptionContainer.visible = false
        }

        onClicked: {
            if (abilityRoot.selectable) {
                abilityRoot.select()
            }
            mouse.accepted = true
        }
    }

    function select() {
        ApplicationControl.AbilitySelected(abilityRoot.name)
        abilitiesBar.unselectAll()
        abilityRoot.selected = true
    }

    function unselect() {
        abilityRoot.selected = false
    }

}