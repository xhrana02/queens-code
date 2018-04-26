//----------------------------------------------//
//	Author: Pavel Hranáč (xhrana02)				//
//	School: Vysoké učení technické v Brně		//
//	Faculty: Fakulta informačních technologií	//
//	Date: Spring 2018							//
//----------------------------------------------//

import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

Button {
    id: buttonRoot

    property string styledText

    checkable: true

    width: (108 > (textid.width + 20)) ? 108 : textid.width + 20
    height: 24
    style: ButtonStyle {
        background: Rectangle {
            border.width: 1
            border.color: buttonRoot.hovered ? "#7F7948" : "#F05F581A"
            color: buttonRoot.pressed ? "#D5CEB1" : buttonRoot.checked ? "#D5CEB1" : "#EDE5C5"
        }
    }

    Text {
        id: textid
        FontLoader { id: menuFont; source: "fonts/CinzelDecorative-Regular.ttf" }
        color: buttonRoot.hovered ? "#716A33" : "#4D4500"
        anchors.horizontalCenter: buttonRoot.horizontalCenter
        anchors.verticalCenter: buttonRoot.verticalCenter
        wrapMode: Text.WordWrap
        verticalAlignment: Text.AlignTop
        font.pixelSize: 16
        font.family: menuFont.name
        text: buttonRoot.styledText
    }    
}