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
    id: standardSetup

    property int widthUnit: (parent.width / 16)
    property int heightUnit: (parent.height / 16)
    
    PlayerSetup {
        id: player1

        anchors.top: parent.top
        anchors.topMargin: heightUnit
        anchors.left: parent.left
        anchors.leftMargin: widthUnit
        anchors.right: parent.right
        anchors.rightMargin: widthUnit

        playerText: "Player 1"
        playerName: settings.player1Name
    }

    Rectangle {
        id: splitter
        
        width: widthUnit * 14
        height: 1

        anchors.centerIn: parent
        anchors.verticalCenterOffset: -(heightUnit)

        color: "#60000000" 
    }

    PlayerSetup {
        id: player2

        anchors.top: splitter.bottom
        anchors.topMargin: heightUnit
        anchors.left: parent.left
        anchors.leftMargin: widthUnit
        anchors.right: parent.right
        anchors.rightMargin: widthUnit
        
        playerText: "Player 2"
        playerName: settings.player2Name
    }


    function player1name(){
        return player1.name2string()
    }

    function player2name(){
        return player2.name2string()
    }

    function player1type(){
        return player1.encodePlayerType()
    }

    function player2type(){
        return player2.encodePlayerType()
    }

    function cleanUI() {
        player1.cleanUI()
        player2.cleanUI()
    }
}

