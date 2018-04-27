//----------------------------------------------//
//	Author: Pavel Hranáč (xhrana02)				//
//	School: Vysoké učení technické v Brně		//
//	Faculty: Fakulta informačních technologií	//
//	Date: Spring 2018							//
//----------------------------------------------//

import QtQuick 2.7
import QtQuick.Controls 1.4

Item {
    id: abilitiesBar

    visible: false
    z: 4
    anchors.bottom: parent != undefined ? parent.bottom : undefined
    anchors.bottomMargin: 30
    anchors.horizontalCenter: parent != undefined ? parent.horizontalCenter : undefined

    Row {
        id: abilitiesRow

        anchors.centerIn: parent

        spacing: 8

        UnitAbility {
            id: ability1
            slot: 1
            visible: false
        }

        UnitAbility {
            id: ability2
            slot: 2
            visible: false
        }

        UnitAbility {
            id: ability3
            slot: 3
            visible: false
        }

        UnitAbility {
            id: ability4
            slot: 4
            visible: false
        }

        UnitAbility {
            id: ability5
            slot: 5
            visible: false
        }
    }

    function setAbility(slot, name, iconPath, description, selectable) {
        if(slot == 1) {
            ability1.name = name
            ability1.iconSource = iconPath
            ability1.description = description
            ability1.selectable = selectable
            ability1.visible = true
        }
        if(slot == 2) {
            ability2.name = name
            ability2.iconSource = iconPath
            ability2.description = description
            ability2.selectable = selectable
            ability2.visible = true
        }
        if(slot == 3) {
            ability3.name = name
            ability3.iconSource = iconPath
            ability3.description = description
            ability3.selectable = selectable
            ability3.visible = true
        }
        if(slot == 4) {
            ability4.name = name
            ability4.iconSource = iconPath
            ability4.description = description
            ability4.selectable = selectable
            ability4.visible = true
        }
        if(slot == 5) {
            ability5.name = name
            ability5.iconSource = iconPath
            ability5.description = description
            ability5.selectable = selectable
            ability5.visible = true
        }
    }

    function show() {
        abilitiesBar.visible = true
        ability1.select()
    }

    function hide() {
        unselectAll()
        abilitiesBar.visible = false
    }

    function selectAbility(slot) {
        if(slot == 1) {
            ability1.select()
        }
        if(slot == 2) {
            ability2.select()
        }
        if(slot == 3) {
            ability3.select()
        }
        if(slot == 4) {
            ability4.select()
        }
        if(slot == 5) {
            ability5.select()
        }
    }

    function unselectAll() {
        ability1.unselect()
        ability2.unselect()
        ability3.unselect()
        ability4.unselect()
        ability5.unselect()
    }

}