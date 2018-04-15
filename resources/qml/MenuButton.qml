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
    id: buttonid
    
    property string styledText

    width: (225 > (textid.width + 30)) ? 220 : textid.width + 30
    height: 50
    style: ButtonStyle {
        background: Rectangle {
            border.width: 2
            border.color: buttonid.hovered ? "#7F7948" : "#5F581A"
            gradient: Gradient {
                GradientStop { position: 0 ; color: buttonid.pressed ?  "#978D6A" : "#A89D76"}
                GradientStop { position: 0.25 ; color: buttonid.pressed ? "#D8CA97" : "#F0E0A8"}
                GradientStop { position: 0.75 ; color: buttonid.pressed ? "#D8CA97" : "#F0E0A8"}
                GradientStop { position: 1 ; color: buttonid.pressed ? "#978D6A" : "#A89D76"}
            }

            
        }
    }

    Text {
        id: textid
        FontLoader { id: menuFont; source: "fonts/CinzelDecorative-Regular.ttf" }
        color: buttonid.hovered ? "#716A33" : "#4D4500"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        wrapMode: Text.WordWrap
        verticalAlignment: Text.AlignTop
        font.pixelSize: 20
        font.bold: true
        font.family: menuFont.name
        text: parent.styledText
    }
}