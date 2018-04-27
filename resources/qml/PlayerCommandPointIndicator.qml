//----------------------------------------------//
//	Author: Pavel Hranáč (xhrana02)				//
//	School: Vysoké učení technické v Brně		//
//	Faculty: Fakulta informačních technologií	//
//	Date: Spring 2018							//
//----------------------------------------------//

import QtQuick 2.7

Rectangle {
    id: indicatorRoot

    property bool used: true

    width: 32
    height: 32
    radius: width * 0.5

    border.width: 2
    border.color: "#28250B"

    color: used ? "#B30000" : "#309930" 
}