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

    Item {
        anchors.centerIn: parent
        width: parent.width * 7/8
        height: parent.height * 7/8

        FontLoader { id: menuFont; source: "fonts/CinzelDecorative-Regular.ttf" }

        Text {
            anchors.centerIn: parent

            color: "#4D4500"
            horizontalAlignment: Text.AlignRight
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: 20
            font.bold: true
            font.family: menuFont.name
            text: "Not yet implemented"
        } 
        
    }

    function cleanUI() {
        // Nothing yet
    }
}

