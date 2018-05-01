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

    property var hpColor: "#CC0000"
    property var enColor: "#E6E000"
    property var emptyColor: "#000066"
    property var borderColor: "#604020"
    property var textColor: "#CCE6FF"
    property var statusTextColor: "#F0E0A8"

    property var maxValue: 1

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

        width: barWidth
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

        text: "-/-"
        color: textColor
        font.pixelSize: fontSize
        font.bold: true
        style: Text.Outline
        styleColor: emptyColor
        z: 4
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

        width: barWidth
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

        text: "-/-"
        color: textColor
        font.pixelSize: fontSize
        font.bold: true
        style: Text.Outline
        styleColor: emptyColor
        z: 5
    }


    Column {
        id: statusEffects

        anchors.bottom: parent.top
        anchors.bottomMargin: 5
        anchors.horizontalCenter: parent.horizontalCenter

        spacing: 5

        Text {
            id: stunnedStatus

            visible: false

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter

            text: "Stunned"
            color: infoBar.statusTextColor
            font.pixelSize: infoBar.fontSize * 1.5
            font.bold: true
            style: Text.Raised
            styleColor: "#CC000000"
        }
        
        Text {
            id: restlessStatus

            visible: false

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter

            text: "Restless"
            color: infoBar.statusTextColor
            font.pixelSize: infoBar.fontSize * 1.5
            font.bold: true
            style: Text.Raised
            styleColor: "#CC000000"
        }
    }


    function setMax(newMax) {
        infoBar.maxValue = newMax
    }

    function show() {
        infoBar.visible = true
    }

    function hide() {
        infoBar.visible = false
    }

    function updatePosition(x, y, z) {
        infoBar.x = x
        infoBar.y = y
        infoBar.z = z
        infoBar.scale = z * 4.2
        if (z < 0.15) {
            hpNumbers.visible = false
            enNumbers.visible = false
        } else {
            hpNumbers.visible = true
            enNumbers.visible = true
        }
    }
    
    function updateValues(hp, en) {
        hpBar.width = infoBar.barWidth * hp / infoBar.maxValue
        enBar.width = infoBar.barWidth * en / infoBar.maxValue
        hpNumbers.text = hp + "/" + infoBar.maxValue
        enNumbers.text = en + "/" + infoBar.maxValue
    }
    
    function updateTheoryValues(hpTheory, enTheory, fluctuation) {
        hpBarTheory.width = infoBar.barWidth * hpTheory / infoBar.maxValue
        enBarTheory.width = infoBar.barWidth * enTheory / infoBar.maxValue
        hpBar.opacity = 0.45 + 0.4 * fluctuation;
        enBar.opacity = 0.25 + 0.6 * fluctuation;
    }

    function updateStatus(isStunned, isRestless){
        stunnedStatus.visible = isStunned
        restlessStatus.visible = isRestless
    }
}