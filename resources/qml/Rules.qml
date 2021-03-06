//----------------------------------------------//
//  Author: Pavel Hranáč (xhrana02)             //
//  School: Vysoké učení technické v Brně       //
//  Faculty: Fakulta informačních technologií   //
//  Date: Spring 2018                           //
//----------------------------------------------//

import QtQuick 2.7
import QtQuick.Controls 1.4

Rectangle {
    id: rulesBackground

    anchors.fill: parent

    color: "#000000"

    MenuButtonSmall {
        id: rulesButtonBack
        anchors.left: parent.left
        anchors.leftMargin: 40
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 30
        styledText: "Back"

        onClicked: {
            guiRoot.showMainMenu()
        }
    }

    Column {
        id: rules

        anchors.centerIn: parent
        
        spacing: 5

        property var textColor: "#F0E0A8"
        property var textSize: 15

        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            color: rules.textColor
            font.pixelSize: 20
            font.bold: true
            font.underline: true
            text: "Game Rules (Standard Game)"
        }
        Item {
            // force double space
            width: 1
            height: 1
        }
        Text {
            color: rules.textColor
            font.pixelSize: rules.textSize
            text: "1. The goal is to kill the enemy Queen (or kill every other unit)."
        }
        Text {
            color: rules.textColor
            font.pixelSize: rules.textSize
            text: "2. Besides their Queen each player has 9 other unique units and each of these units has different abilities."
        }
        Text {
            color: rules.textColor
            font.pixelSize: rules.textSize
            text: "- These units are divided into 3 categories: Fighters, Specialists, Spellcasters."
        }
        Text {
            color: rules.textColor
            font.pixelSize: rules.textSize
            text: "  - Fighters are Knight, Spearman, Brute. They are tougher than the other units and have strong melee attacks."
        }
        Text {
            color: rules.textColor
            font.pixelSize: rules.textSize
            text: "  - Specialists are Ranger, Scout, Agent. Each of them is quite unique."
        }
        Text {
            color: rules.textColor
            font.pixelSize: rules.textSize
            text: "    - Ranger with his superior range and protection against line attacks is the king of ranged combat."
        }
        Text {
            color: rules.textColor
            font.pixelSize: rules.textSize
            text: "    - Scout isn't the biggest threat in terms of damage, but he can get around the map very quickly."
        }
        Text {
            color: rules.textColor
            font.pixelSize: rules.textSize
            text: "    - Agent can kill almost any unit in 1 turn if he's in the right position."
        }
        Text {
            color: rules.textColor
            font.pixelSize: rules.textSize
            text: "  - Spellcasters are Warlock, Priest, Wizard. They possess medium range offensive abilities and close range support abilites."
        }
        Text {
            color: rules.textColor
            font.pixelSize: rules.textSize
            text: "3. The players take turns consisting of up to 3 moves (ability uses)."
        }
        Text {
            color: rules.textColor
            font.pixelSize: rules.textSize
            text: "4. Each unit has Hit Points (HP) and Energy (EN). A unit can't have more EN than its current HP."
        }
        Text {
            color: rules.textColor
            font.pixelSize: rules.textSize
            text: "5a. Each unit regenerates a little bit of EN at the start of its turn."
        }
        Text {
            color: rules.textColor
            font.pixelSize: rules.textSize
            text: "5b. And if it hasn't moved during the turn and isn't Restless, it also regains some HP and EN at the end of the turn."
        }
        Text {
            color: rules.textColor
            font.pixelSize: rules.textSize
            text: "6. There are 3 different types of attacks. Melee, Line, and Indirect."
        }
        Text {
            color: rules.textColor
            font.pixelSize: rules.textSize
            text: "  - Melee attacks can only target the 4 directly neighboring squares."
        }
        Text {
            color: rules.textColor
            font.pixelSize: rules.textSize
            text: "  - Line attacks can only use perpendicular and diagonal lines and are blocked by obstacles."
        }
        Text {
            color: rules.textColor
            font.pixelSize: rules.textSize
            text: "    - Obstacles can be walls, enemy units and ice blocks. Units can shoot trough their allies."
        }
        Text {
            color: rules.textColor
            font.pixelSize: rules.textSize
            text: "  - Indirect attacks can be used on anything in range and ignore obstacles."
        }
        Text {
            color: rules.textColor
            font.pixelSize: rules.textSize
            text: "  - Range of line and indirect attacks is calculated as the actual distance, not a~number of squares."
        }
        Text {
            color: rules.textColor
            font.pixelSize: rules.textSize
            text: "7. The center field contains the throne. The Queen can claim this throne by standing on it, making all enemy units Restless."
        }
        Item {
            // force double space
            width: 1
            height: 1
        }
        Text {
            color: rules.textColor
            font.pixelSize: rules.textSize
            font.italic: true
            text: "Read tooltips of abilities for more information on game mechanics like types of damage, armor, status effects, and more."
        }

        
    }
}

