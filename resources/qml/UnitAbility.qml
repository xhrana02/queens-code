//----------------------------------------------//
//  Author: Pavel Hranáč (xhrana02)             //
//  School: Vysoké učení technické v Brně       //
//  Faculty: Fakulta informačních technologií   //
//  Date: Spring 2018                           //
//----------------------------------------------//

import QtQuick 2.7
import QtQuick.Controls 1.4

Item {
    id: abilityRoot

    width: 60
    height: 60

    property int slot
    property string name
    property string iconSource
    property string description
    property bool selectable: false
    property bool selected: false
    property int costHP
    property int costEN

    property var borderColor: "#5F581A"
    property var borderSelectedColor: "#FFFF99"
    property var textColor: "#FFFCE6"

    Rectangle {
        id: abilityIconContainer

        anchors.fill: parent
        
        color: "#00000000"
        border.width: abilityRoot.selectable ? 2 : 0
        border.color: abilityRoot.selected ? abilityRoot.borderSelectedColor : abilityRoot.borderColor
        radius: 1

        Image {
            id: abilityIcon

            anchors.fill: parent
            anchors.margins: 0
            fillMode: Image.Stretch

            source: abilityRoot.iconSource
        }
    }

    Rectangle {
        id: abilityShortcutContainer
        
        anchors.left: abilityIconContainer.left
        anchors.leftMargin: -4
        anchors.top: abilityIconContainer.top
        anchors.topMargin: -4
        
        width: 20
        height: 20

        visible: abilityRoot.selectable

        color: "#F83C3810"
        border.width: 2
        border.color: abilityRoot.selected ? abilityRoot.borderSelectedColor : abilityRoot.borderColor
        radius: 1

        Text {
            id: abilityShortcutText

            anchors.fill: parent
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter

            font.pixelSize: 14
            color: abilityRoot.textColor

            text: abilityRoot.slot
        }

    }

    Rectangle {
        id: abilityDescriptionContainer

        width: 400
        height: abilityDescriptionText.contentHeight + 40;

        anchors.bottom: abilityRoot.top
        anchors.bottomMargin: 10
        anchors.left: abilityRoot.left

        visible: false

        color: "#F8101004"
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
            color: abilityRoot.textColor

            text: abilityRoot.description
        }
    }

    Text {
        id: abilityCostEnText

        anchors.right: abilityIconContainer.right
        anchors.rightMargin: 2
        anchors.bottom: abilityIconContainer.bottom
        anchors.bottomMargin: 2

        visible: abilityRoot.costEN > 0 ? true : false

        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter

        font.pixelSize: 14
        font.bold: true
        style: Text.Outline
        styleColor: "#CC000000"
        color: "#E6E000"

        text: abilityRoot.slot == 1 ? abilityRoot.costEN + "■" : abilityRoot.costEN 
    }

    Text {
        id: abilityCostHpText

        anchors.right: abilityCostEnText.left
        anchors.rightMargin: 2
        anchors.bottom: abilityIconContainer.bottom
        anchors.bottomMargin: 2

        visible: abilityRoot.costHP > 0 ? true : false

        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter

        font.pixelSize: 14
        font.bold: true
        style: Text.Outline
        styleColor: "#CC000000"
        color: "#FF0000"

        text: abilityRoot.costHP 
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
            abilityRoot.select()
            mouse.accepted = true
        }
    }

    function select() {
        if (abilityRoot.selectable) {
            abilitiesBar.unselectAll()
            abilityRoot.selected = true
            ApplicationControl.AbilitySelected(slot)
        }
    }

    function unselect() {
        abilityRoot.selected = false
    }

}