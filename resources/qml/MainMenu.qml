//----------------------------------------------//
//	Author: Pavel Hranáč (xhrana02)				//
//	School: Vysoké učení technické v Brně		//
//	Faculty: Fakulta informačních technologií	//
//	Date: Spring 2018							//
//----------------------------------------------//

import QtQuick 2.7

Item {
    id: mainMenu

    Rectangle {
        id: titleText
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: (guiRoot.height / 3 - 100)
        width: 800
        height: 100
        color: "#00000000"
        Text {
            FontLoader { id: menuFont; source: "fonts/CinzelDecorative-Regular.ttf" }
            font.family: menuFont.name
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            wrapMode: Text.WordWrap
            verticalAlignment: Text.AlignTop
            color: "#5F581A"
            font.pixelSize: 72
            font.letterSpacing: 10
            font.bold: false
            text: "Queens Regicide"
        }
    }

    MenuButton {
        id: mainButtonPlay
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: titleText.bottom
        anchors.topMargin: (guiRoot.height / 15)
        styledText: "Play"

        onClicked: guiRoot.showPlayMenu()
    }

    MenuButton {
        id: mainButtonOptions
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: mainButtonPlay.bottom
        anchors.topMargin: (guiRoot.height / 30)
        styledText: "Options"

        onClicked: guiRoot.showOptionsMenu()
    }

    MenuButton {
        id: mainButtonQuit
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: mainButtonOptions.bottom
        anchors.topMargin: (guiRoot.height / 15)
        styledText: "Quit"

        onClicked: Qt.quit()
    }
}

