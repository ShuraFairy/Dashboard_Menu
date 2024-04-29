import QtQuick 2.0
import QtMultimedia 5.6
import QtGraphicalEffects 1.12


Item {
    id : id_menu_diagnostics_heating_sys_valves
    property int pos0: 0
    property int pos1: 1
    property int pos2: 2
    property int pos3: 3
    property int pos4: 4
    property int pos5: 5
    property int pos10: 10
    property int pos11: 11
    property int pos12: 12
    property int pos13: 13

    Rectangle{
        id: id_heating_sys_valves_right_whole
        height: 500
        width : 1462
        x: id_subitems_left.x + 391
        y:id_menulayer.y
        color: "transparent"
		visible: parent.visible

        //Handling Header
        Rectangle{
            id: id_heating_sys_valves_header
            height: 108
            width: parent.width
            visible: true
            color: "transparent"
            Flow {
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.left: parent.left
                anchors.leftMargin: 86.5
                anchors.verticalCenter: parent.verticalCenter
                Text {
					text: id_mainmenu.main_menu_names[1]
                    color: "#21B1D0"
                    wrapMode: Text.WordWrap
                    FontLoader { id: parameter_name_font; source: "Fonts/Roboto-Italic.ttf" }
                    font { family: parameter_name_font.name; pixelSize: 23;}
                    font.letterSpacing: 1.0
                }
                Text {
                    color: "#21B1D0"
                    text: "  >  "
                    FontLoader { id: seperator_font; source: "Fonts/Roboto-Italic.ttf" }
                    font { family: seperator_font.name; pixelSize: 23;}
                    font.letterSpacing: 1.0
                }
                Text {
					text: id_mainmenu.sub_menu_names[id_mainmenu.list_menu_pos]
                    color: "white"
                    wrapMode: Text.WordWrap
                    FontLoader { id: brakepads_name_font; source: "Fonts/Roboto-Italic.ttf" }
                    font { family: brakepads_name_font.name; pixelSize: 23;}
                    font.letterSpacing: 1.0
                }
            }
        }

        Rectangle{
            id: id_heating_sys_valves_right
            x: 30
            y:108
            height: 321
            width : 1462
            clip: true
            visible: {
                if(id_mainmenu.type_of_vehicle === "2")
                {
                    visible : true
                } else {
                    visible : false
                }
            }
            color: "transparent"
            Image {
                id: id_heating_sys_valves_right_bar
                x:87
                y:27
                height: sourceSize.height
                width: sourceSize.width
                source: "pics/Menu/Bus_layout_2ax__1_.png" // 2 Axles
                visible: true
            }

            Image {
                id: id_heating_sys_valves_rect1
                x:920
                y:200
                height: sourceSize.height
                width: sourceSize.width
                source: "pics/Menu/Door__1_.png"
                visible: true
            }

            Image {
                id: id_heating_sys_valves_rect2
                x:522
                y:200
                height: sourceSize.height
                width: sourceSize.width
                source: "pics/Menu/Door__1_.png"
                visible: true
            }
            Image {
                id: id_heating_sys_valves_rect3
                x:138
                y: 200
                height: sourceSize.height
                width: sourceSize.width
                source: "pics/Menu/Door__1_.png"
                visible: true
            }



            Image {
                id: id_heating_sys_valves1
                anchors.left:   parent.left
                anchors.leftMargin: 590
                y: 210
                height: sourceSize.height
                width: sourceSize.width
                source: "pics/Menu/Heating_system_valves.png"

                visible: true
                ColorOverlay{
                    anchors.fill: id_heating_sys_valves1
                    source: id_heating_sys_valves1
					color: id_mainmenu.param_menu_names[0][pos1]
                }
            }

            Image {
                id: id_heating_sys_valves2
                anchors.left:   parent.left
                anchors.leftMargin: 920
                y: 90
                height: sourceSize.height
                width: sourceSize.width
                source: "pics/Menu/Heating_system_valves.png"
                visible: true
                ColorOverlay{
                    anchors.fill: id_heating_sys_valves2
                    source: id_heating_sys_valves2
					color: id_mainmenu.param_menu_names[1][pos1]
                }
            }




            Image {
                id: id_heating_sys_valves4
                anchors.left:   parent.left
                anchors.leftMargin: 410
                y: 210
                height: sourceSize.height
                width: sourceSize.width
                source: "pics/Menu/Heating_system_valves.png"

                visible: true
                ColorOverlay{
                    anchors.fill: id_heating_sys_valves4
                    source: id_heating_sys_valves4
					color: id_mainmenu.param_menu_names[3][pos1]
                }
            }



            Image {
                id: id_heating_sys_valves5
                anchors.left: parent.left
                anchors.leftMargin: 158
                y: 90
                height: sourceSize.height
                width: sourceSize.width
                source: "pics/Menu/Heating_system_valves.png"

                visible: true
                ColorOverlay{
                    anchors.fill: id_heating_sys_valves5
                    source: id_heating_sys_valves5
					color: id_mainmenu.param_menu_names[4][pos1]
                }
            }

            Image {
                id: id_heating_sys_valves7
                anchors.left:   parent.left
                anchors.leftMargin: 410
                y: 40
                height: sourceSize.height
                width: sourceSize.width
                source: "pics/Menu/Heating_system_valves.png"

                visible: true
                ColorOverlay{
                    anchors.fill: id_heating_sys_valves7
                    source: id_heating_sys_valves7
					color: id_mainmenu.param_menu_names[6][pos1]
                }
            }



            Image {
                id: id_heating_sys_valves8
                anchors.left:   parent.left
                anchors.leftMargin: 640
                y:40
                height: sourceSize.height
                width: sourceSize.width
                source: "pics/Menu/Heating_system_valves.png"

                visible: true
                ColorOverlay{
                    anchors.fill: id_heating_sys_valves8
                    source: id_heating_sys_valves8
					color:id_mainmenu.param_menu_names[7][pos1]
                }
            }

        }


        //3 Axles
        Rectangle{
            id: id_heating_sys_valves_3_axle_right
            x: 30
            y:108
            height: 321
            width : 1462
            clip: true
            visible: {
                if(id_mainmenu.type_of_vehicle === "3"){
                    visible : true
                }else{
                    visible:false
                }
            }
            color: "transparent"
            Image {
                id: id_heating_sys_valves_3_axle_right_bar
                x:87
                y:25
                height: sourceSize.height
                width: sourceSize.width
                source: "pics/Menu/Bus_layout_3__1_.png" // 3 Axles
                visible: true
            }
            Image {
                id: id_heating_sys_3axle_rect1
                x:1210
                y:200
                height: sourceSize.height
                width: sourceSize.width
                source: "pics/Menu/Door__1_.png"
                visible: true
            }

            Image {
                id: id_heating_sys_3axle_rect2
                x:856
                y:200
                height: sourceSize.height
                width: sourceSize.width
                source: "pics/Menu/Door__1_.png"
                visible: true
            }
            Image {
                id: id_heating_sys_3axle_rect3
                x:379
                y:200
                height: sourceSize.height
                width: sourceSize.width
                source: "pics/Menu/Door__1_.png"
                visible: true
            }
            Image {
                id: id_heating_sys_3axle_rect4
                x:110
                y:200
                height: sourceSize.height
                width: sourceSize.width
                source: "pics/Menu/Door__1_.png"
                visible: true
            }

            Image {
                id: id_heating_sys_3axle_valves1
                anchors.left: parent.left
                anchors.leftMargin:1071
                y: 210
                height: sourceSize.height
                width: sourceSize.width
                source: "pics/Menu/Heating_system_valves.png"

                visible: true
                ColorOverlay{
                    anchors.fill: id_heating_sys_3axle_valves1
                    source: id_heating_sys_3axle_valves1
					color: id_mainmenu.param_menu_names[0][pos1]
                }
            }





            Image {
                id: id_heating_sys_3axle_valves2
                anchors.left:  parent.left
                anchors.leftMargin: 1220
                y: 100
                height: sourceSize.height
                width: sourceSize.width
                source: "pics/Menu/Heating_system_valves.png"
                visible: true
                ColorOverlay{
                    anchors.fill: id_heating_sys_3axle_valves2
                    source: id_heating_sys_3axle_valves2
					color: id_mainmenu.param_menu_names[1][pos1]
                }
            }



            Image {
                id: id_heating_sys_3axle_valves3
                anchors.left:  parent.left
                anchors.leftMargin: 446
                y: 210
                height: sourceSize.height
                width: sourceSize.width
                source: "pics/Menu/Heating_system_valves.png"
                visible: true
                ColorOverlay{
                    anchors.fill: id_heating_sys_3axle_valves3
                    source: id_heating_sys_3axle_valves3
					color: id_mainmenu.param_menu_names[2][pos1]
                }
            }




            Image {
                id: id_heating_sys_3axle_valves4
                anchors.left: parent.left
                anchors.leftMargin:760
                y: 210
                height: sourceSize.height
                width: sourceSize.width
                source: "pics/Menu/Heating_system_valves.png"

                visible: true
                ColorOverlay{
                    anchors.fill: id_heating_sys_3axle_valves4
                    source: id_heating_sys_3axle_valves4
					color: id_mainmenu.param_menu_names[3][pos1]
                }
            }



            Image {
                id: id_heating_sys_3axle_valves5
                anchors.left: parent.left
                anchors.leftMargin:120
                y: 100
                height: sourceSize.height
                width: sourceSize.width
                source: "pics/Menu/Heating_system_valves.png"

                visible: true
                ColorOverlay{
                    anchors.fill: id_heating_sys_3axle_valves5
                    source: id_heating_sys_3axle_valves5
					color: id_mainmenu.param_menu_names[4][pos1]
                }
            }

            Image {
                id: id_heating_sys_3axle_valves6
                anchors.left: parent.left
                anchors.leftMargin:1000
                y: 210
                height: sourceSize.height
                width: sourceSize.width
                source: "pics/Menu/Heating_system_valves.png"

                visible: true
                ColorOverlay{
                    anchors.fill: id_heating_sys_3axle_valves6
                    source: id_heating_sys_3axle_valves6
					color: id_mainmenu.param_menu_names[5][pos1]
                }
            }

            Image {
                id: id_heating_sys_3axle_valves7
                anchors.left: parent.left
                anchors.leftMargin:760
                y: 40
                height: sourceSize.height
                width: sourceSize.width
                source: "pics/Menu/Heating_system_valves.png"

                visible: true
                ColorOverlay{
                    anchors.fill: id_heating_sys_3axle_valves7
                    source: id_heating_sys_3axle_valves7
					color: id_mainmenu.param_menu_names[6][pos1]
                }
            }



            Image {
                id: id_heating_sys_3axle_valves8
                anchors.left: parent.left
                anchors.leftMargin:1030
                y: 40
                height: sourceSize.height
                width: sourceSize.width
                source: "pics/Menu/Heating_system_valves.png"
                visible: true
                ColorOverlay{
                    anchors.fill: id_heating_sys_3axle_valves8
                    source: id_heating_sys_3axle_valves8
					color: id_mainmenu.param_menu_names[7][pos1]
                }
            }

            Image {
                id: id_heating_sys_3axle_valves9
                anchors.left: parent.left
                anchors.leftMargin: 380
                y: 40
                height: sourceSize.height
                width: sourceSize.width
                source: "pics/Menu/Heating_system_valves.png"
                visible: true
                ColorOverlay{
                    anchors.fill: id_heating_sys_3axle_valves9
                    source: id_heating_sys_3axle_valves9
					color: id_mainmenu.param_menu_names[8][pos1]
                }
            }

        }
        Rectangle {
            id: id_diagnostics_right_footer
            width: 1200
            height: 80
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            color: "transparent"
            Flow {
                anchors.centerIn: parent
                anchors.horizontalCenterOffset: 700
                Text {
                    text: "1"
                    color: "#21B1D0"
                    wrapMode: Text.WordWrap
                    FontLoader { id: diagnostics_selector_font; source: "Fonts/Roboto-Italic.ttf" }
                    font { family: diagnostics_selector_font.name; pixelSize: 25;}
                    font.letterSpacing: 1.0
                }
                Text {
                    color: "#21B1D0"
                    text: "/"
                    FontLoader { id: seperator_font_item; source: "Fonts/Roboto-Italic.ttf" }
                    font { family: seperator_font_item.name; pixelSize: 25;}
                    font.letterSpacing: 1.0
                }
                Text {
                    text: "1"
                    color: "#21B1D0"
                    wrapMode: Text.WordWrap
                    FontLoader { id: diagnostics_total_font; source: "Fonts/Roboto-Italic.ttf" }
                    font { family: diagnostics_total_font.name; pixelSize: 25;}
                    font.letterSpacing: 1.0
                }
            }
        }
    }
}

