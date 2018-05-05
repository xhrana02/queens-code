//----------------------------------------------//
//	Author: Pavel Hranáč (xhrana02)				//
//	School: Vysoké učení technické v Brně		//
//	Faculty: Fakulta informačních technologií	//
//	Date: Spring 2018							//
//----------------------------------------------//

import QtQuick 2.7
import QtQuick.Controls 1.4

Item {
    id: infoBar

    width: 120
    height: 38

    property var barWidth: 120
    property var barHeight: 16

    property var borderWidth: 2
    property var fontSize: 12
    FontLoader { id: menuFont; source: "fonts/CinzelDecorative-Regular.ttf" }

    property var maxValue: 1
    property var unitName: "Unknown Unit"

    property var hpColor: "#CC0000"
    property var enColor: "#E6E000"
    property var emptyColor: "#000066"
    property var borderColor: "#604020"
    property var textColor: "#CCE6FF"
    property var statusTextColor: "#F0E0A8"
    property var textLetterSpacing: 3
    property var hpFlyingNumbersScale: 1
    property var enFlyingNumbersScale: 1

    property var currentHP: 1
    property var currentEN: 1
    property var currentArmor: 0
    property var deltaHP: 0
    property var deltaEN: 0
    property var stunnedTurns: 0
    property var restlessTurns: 0
    property var blessedTurns: 0
    property var shieldedTurns: 0

    transformOrigin: Item.Center

    // HEALTH
    Rectangle {
        id: hpBackground

        width: barWidth + borderWidth * 2
        height: barHeight + borderWidth * 2

        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter

        color: emptyColor
        border.width: borderWidth
        border.color: borderColor
        z: 1
    }

    Rectangle {
        id: hpBarTheory

        width: barWidth
        height: barHeight

        anchors.top: parent.top
        anchors.topMargin: borderWidth
        anchors.left: parent.left

        color: hpColor
        border.width: 0
        z: 2
    }

    Rectangle {
        id: hpBar

        width: infoBar.barWidth * infoBar.currentHP / infoBar.maxValue
        height: barHeight

        anchors.top: parent.top
        anchors.topMargin: borderWidth
        anchors.left: parent.left

        color: hpColor
        border.width: 0
        z: 3
    }

    Text {
        id: hpNumbers

        width: barWidth
        height: barHeight

        anchors.top: parent.top
        anchors.topMargin: ((barHeight - fontSize) / 2) - 1
        anchors.horizontalCenter: parent.horizontalCenter
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter

        text: infoBar.currentHP + "/" + infoBar.maxValue
        color: textColor
        font.pixelSize: fontSize
        font.letterSpacing: infoBar.textLetterSpacing
        font.bold: true
        style: Text.Outline
        styleColor: emptyColor
        z: 4
    }

    Text {
        id: hpFlyingNumbers

        anchors.right: parent.horizontalCenter
        anchors.rightMargin: 4

        z: 8
        
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter

        opacity: 0
        color: infoBar.hpColor
        font.pixelSize: infoBar.fontSize * infoBar.hpFlyingNumbersScale
        font.bold: true
        style: Text.Raised
        styleColor: "#CC000000"
        text: infoBar.deltaHP > 0 ? "+" + infoBar.deltaHP : infoBar.deltaHP

        ParallelAnimation {
            id: hpFlyingNumbersAnimation

            YAnimator {
                id: hpFlyingNumbersAnimationYpos

                target: hpFlyingNumbers
                easing.type: Easing.Linear
                from: -20
                to: -80
                duration: 2000 * infoBar.hpFlyingNumbersScale
            }
            OpacityAnimator {
                id: hpFlyingNumbersAnimationOpacity

                target: hpFlyingNumbers
                easing.type: Easing.InQuint
                from: 1
                to: 0
                duration: 2000 * infoBar.hpFlyingNumbersScale
            }
        }
    }

    // ENERGY
    Rectangle {
        id: enBackground

        width: barWidth + borderWidth * 2
        height: barHeight + borderWidth * 2

        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter

        color: emptyColor
        border.width: borderWidth
        border.color: borderColor
        z: 1
    }

    Rectangle {
        id: enBackgroundLimited

        width: hpBar.width
        height: barHeight

        anchors.bottom: parent.bottom
        anchors.bottomMargin: borderWidth
        anchors.left: parent.left

        color: "#505033"
        z: 2
    }
    
    Rectangle {
        id: enBarTheory

        width: barWidth
        height: barHeight

        anchors.bottom: parent.bottom
        anchors.bottomMargin: borderWidth
        anchors.left: parent.left

        color: enColor
        border.width: 0
        z: 3
    }

    Rectangle {
        id: enBar

        width: infoBar.barWidth * infoBar.currentEN / infoBar.maxValue
        height: barHeight

        anchors.bottom: parent.bottom
        anchors.bottomMargin: borderWidth
        anchors.left: parent.left

        color: enColor
        border.width: 0
        z: 4
    }

    Text {
        id: enNumbers

        width: barWidth
        height: barHeight

        anchors.bottom: parent.bottom
        anchors.bottomMargin: ((barHeight - fontSize) / 2) + 1
        anchors.horizontalCenter: parent.horizontalCenter
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter

        text: infoBar.currentEN + "/" + infoBar.maxValue
        color: textColor
        font.pixelSize: fontSize
        font.letterSpacing: infoBar.textLetterSpacing
        font.bold: true
        style: Text.Outline
        styleColor: emptyColor
        z: 5
    }

    Text {
        id: enFlyingNumbers

        anchors.left: parent.horizontalCenter
        anchors.leftMargin: 4

        z: 7

        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter

        opacity: 0
        color: infoBar.enColor
        font.pixelSize: infoBar.fontSize * infoBar.enFlyingNumbersScale
        font.bold: true
        style: Text.Raised
        styleColor: "#CC000000"
        text: infoBar.deltaEN > 0 ? "+" + infoBar.deltaEN : infoBar.deltaEN

        ParallelAnimation {
            id: enFlyingNumbersAnimation

            YAnimator {
                id: enFlyingNumbersAnimationYpos

                target: enFlyingNumbers
                easing.type: Easing.Linear
                from: 0
                to: -60
                duration: 2000 * infoBar.enFlyingNumbersScale
            }
            OpacityAnimator {
                id: enFlyingNumbersAnimationOpacity

                target: enFlyingNumbers
                easing.type: Easing.InQuint
                from: 1
                to: 0
                duration: 2000 * infoBar.enFlyingNumbersScale
            }
        }
    }

    // EXTRA INFO
    Text {
        id: unitNameText

        anchors.bottom: parent.top
        anchors.bottomMargin: 2
        anchors.horizontalCenter: parent.horizontalCenter

        visible: false

        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter

        text: infoBar.unitName
        color: infoBar.statusTextColor
        font.pixelSize: infoBar.fontSize * 1.25
        font.letterSpacing: infoBar.textLetterSpacing
        font.bold: true
        style: Text.Raised
        styleColor: "#CC000000"
    }

    Column {
        id: statusEffects

        anchors.top: parent.bottom
        anchors.topMargin: 2
        anchors.horizontalCenter: parent.horizontalCenter

        spacing: 2

        Text {
            id: stunnedStatus

            visible: infoBar.stunnedTurns > 0 ? true : false

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter

            color: infoBar.statusTextColor
            font.pixelSize: infoBar.fontSize * 1.1
            font.letterSpacing: infoBar.textLetterSpacing
            style: Text.Raised
            styleColor: "#CC000000"

            text: "Stunned [" + infoBar.stunnedTurns + "]"
        }
        
        Text {
            id: restlessStatus

            visible: infoBar.restlessTurns > 0 ? true : false

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter

            color: infoBar.statusTextColor
            font.pixelSize: infoBar.fontSize * 1.1
            font.letterSpacing: infoBar.textLetterSpacing
            style: Text.Raised
            styleColor: "#CC000000"

            text: "Restless [" + infoBar.restlessTurns + "]"
        }
        
        Text {
            id: blessedStatus

            visible: infoBar.blessedTurns > 0 ? true : false

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter

            color: infoBar.statusTextColor
            font.pixelSize: infoBar.fontSize * 1.1
            font.letterSpacing: infoBar.textLetterSpacing
            style: Text.Raised
            styleColor: "#CC000000"

            text: "Blessing [" + infoBar.blessedTurns + "]"
        }
        
        Text {
            id: shieldedStatus

            visible: infoBar.shieldedTurns > 0 ? true : false

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter

            color: infoBar.statusTextColor
            font.pixelSize: infoBar.fontSize * 1.1
            font.letterSpacing: infoBar.textLetterSpacing
            style: Text.Raised
            styleColor: "#CC000000"

            text: "Demon Shield [" + infoBar.shieldedTurns + "]"
        }
    }

    Image {
        id: armorInfo

        anchors.right: parent.left
        anchors.rightMargin: -15
        anchors.verticalCenter: parent.verticalCenter
        visible: armorValue.text != "0" ? true : false

        z: 6

        width: 50
        height: 50
        fillMode: Image.Stretch

        source: "icons/InfoBarArmor.png"

        Text {
            id: armorValue

            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.verticalCenter
            anchors.bottomMargin: -5
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            
            color: "#FFFFFF"
            font.pixelSize: infoBar.fontSize * 1.25
            font.bold: true
            style: Text.Outline
            styleColor: "#CC000000"

            text: infoBar.currentArmor
        }
    }


    function setUnitConstants(name, maxHP) {
        unitName = name
        infoBar.maxValue = maxHP
        infoBar.currentHP = maxHP
        infoBar.currentEN = maxHP
    }

    function show() {
        infoBar.visible = true
    }

    function hide() {
        infoBar.visible = false
    }

    function showExtraInfo() {
        hpNumbers.visible = true
        enNumbers.visible = true
        unitNameText.visible = true
        statusEffects.visible = true
    }

    function hideExtraInfo() {
        hpNumbers.visible = false
        enNumbers.visible = false
        unitNameText.visible = false
        statusEffects.visible = false
    }

    function updatePosition(x, y, depth, size) {
        infoBar.x = x
        infoBar.y = y
        infoBar.z = depth
        infoBar.scale = size

        if (size > 0.6) {
            showExtraInfo()
        } else {
            hideExtraInfo()
        }
    }
    
    function updateValues(hp, en, armor) {
        if (hp != infoBar.currentHP) {
            infoBar.deltaHP = hp - infoBar.currentHP
            infoBar.hpFlyingNumbersScale = (1.5 + (Math.abs(infoBar.deltaHP) * 0.1))
            hpFlyingNumbersAnimation.restart()
        }
        if (en != infoBar.currentEN) {
            infoBar.deltaEN = en - infoBar.currentEN
            infoBar.enFlyingNumbersScale = (1.5 + (Math.abs(infoBar.deltaEN) * 0.05))
            enFlyingNumbersAnimation.restart()
        }
        infoBar.currentHP = hp
        infoBar.currentEN = en
        infoBar.currentArmor = armor
    }
    
    function updateTheoryValues(hpTheory, enTheory, fluctuation) {
        hpBarTheory.width = infoBar.barWidth * hpTheory / infoBar.maxValue
        enBarTheory.width = infoBar.barWidth * enTheory / infoBar.maxValue
        hpBar.opacity = 0.45 + 0.4 * fluctuation;
        enBar.opacity = 0.25 + 0.6 * fluctuation;
    }

    function updateStatus(stunned, restless, blessed, shielded){
        infoBar.stunnedTurns = stunned
        infoBar.restlessTurns = restless
        infoBar.blessedTurns = blessed
        infoBar.shieldedTurns = shielded
    }
}