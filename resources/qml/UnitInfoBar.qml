//----------------------------------------------//
//	Author: Pavel Hranáč (xhrana02)				//
//	School: Vysoké učení technické v Brně		//
//	Faculty: Fakulta informačních technologií	//
//	Date: Spring 2018							//
//----------------------------------------------//

import QtQuick 2.7
import QtQuick.Controls 1.4

Item {
    id: infobar

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
        id: hpBar

        width: barWidth
        height: barHeight

        anchors.top: parent.top
        anchors.topMargin: borderWidth
        anchors.left: hpBackground.left
        anchors.leftMargin: borderWidth

        color: hpColor
        border.width: 0
        z: 2
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
        z: 3
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
        id: enBar

        width: barWidth
        height: barHeight

        anchors.bottom: parent.bottom
        anchors.bottomMargin: borderWidth
        anchors.left: enBackground.left
        anchors.leftMargin: borderWidth

        color: enColor
        border.width: 0
        z: 2
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
        z: 3
    }

    function update(x, y, z, hp, maxhp, en, maxen) {
        infobar.visible = true
        infobar.x = x
        infobar.y = y
        infobar.z = z
        hpBar.width = barWidth * hp / maxhp
        enBar.width = barWidth * en / maxen
        hpNumbers.text = hp + "/" + maxhp
        enNumbers.text = en + "/" + maxen
        
        infobar.scale = z * 2.5
        if (z < 0.2) {
            hpNumbers.visible = false
            enNumbers.visible = false
        } else {
            hpNumbers.visible = true
            enNumbers.visible = true
        }
    }

    function hide() {
        infobar.visible = false
    }
}