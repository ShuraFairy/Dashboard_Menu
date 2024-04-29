import QtQuick 2.0
import QtMultimedia 5.6
import QtGraphicalEffects 1.12


Item {
    id : id_menu_diagnostics_fire_extinguisher
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
        id: id_fire_extinguisher_right_whole
        height: 500
        width : 1462
        x: id_subitems_left.x + 391
        y:id_menulayer.y
        color: "transparent"
		visible: parent.visible

        //Handling Header
        Rectangle{
            id: id_fire_extinguisher_header
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
            id: id_fire_extinguisher_right
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
                id: id_fire_extinguisher_right_bar
                x:87
                y:27
                height: sourceSize.height
                width: sourceSize.width
                source: "pics/Menu/Bus_layout_2ax__1_.png" // 2 Axles
                visible: true
            }
            Image {
                id: id_fire_extinguisher1_rect1
                x:920
                y:200
                height: sourceSize.height
                width: sourceSize.width
                source: "pics/Menu/Door__1_.png"
                visible: true
            }

            Image {
                id: id_fire_extinguisher2_rect1
                x:522
                y:200
                height: sourceSize.height
                width: sourceSize.width
                source: "pics/Menu/Door__1_.png"
                visible: true
            }
            Image {
                id: id_fire_extinguisher3_rect
                x:138
                y: 200
                height: sourceSize.height
                width: sourceSize.width
                source: "pics/Menu/Door__1_.png"
                visible: true
            }





            Image {
                id: id_fire_extinguisher1
                anchors.left:   parent.left
                anchors.leftMargin: 905
                y: 80
                height: sourceSize.height
                width: sourceSize.width
                source: "pics/Menu/Fire_extinguishers_for_mnu__1_.png"
                visible: true
                ColorOverlay{
                    anchors.fill: id_fire_extinguisher1
                    source: id_fire_extinguisher1
					color: id_mainmenu.param_menu_names[0][pos1]
                }
            }

            Image {
                id: id_fire_extinguisher2
                anchors.left:   parent.left
                anchors.leftMargin: 760
                y: 190
                height: sourceSize.height
                width: sourceSize.width
                source: "pics/Menu/Fire_extinguishers_for_mnu__1_.png"
                visible: true
                ColorOverlay{
                    anchors.fill: id_fire_extinguisher2
                    source: id_fire_extinguisher2
					color: id_mainmenu.param_menu_names[1][pos1]
                }
            }

            Image {
                id: id_fire_extinguisher3
                anchors.left:   parent.left
                anchors.leftMargin: 680
                y: 190
                height: sourceSize.height
                width: sourceSize.width
                source: "pics/Menu/Fire_extinguishers_for_mnu__1_.png"

                visible: true
                ColorOverlay{
                    anchors.fill: id_fire_extinguisher3
                    source: id_fire_extinguisher3
					color:id_mainmenu.param_menu_names[2][pos1]
                }
            }
        }


        //3 Axles
        Rectangle{
            id: id_fire_extinguisher_3_axle_right
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
                id: id_fire_extinguisher_3_axle_right_bar
                x:87
                y:25
                height: sourceSize.height
                width: sourceSize.width
                source: "pics/Menu/Bus_layout_3__1_.png" // 3 Axles
                visible: true
            }
            Image {
                id: id_fire_extinguisher_3axle_rect1
                x:1210
                y:200
                height: sourceSize.height
                width: sourceSize.width
                source: "pics/Menu/Door__1_.png"
                visible: true
            }

            Image {
                id: id_fire_extinguisher_3axle_rect2
                x:856
                y:200
                height: sourceSize.height
                width: sourceSize.width
                source: "pics/Menu/Door__1_.png"
                visible: true
            }
            Image {
                id: id_fire_extinguisher_3axle_rect3
                x:379
                y:200
                height: sourceSize.height
                width: sourceSize.width
                source: "pics/Menu/Door__1_.png"
                visible: true
            }
            Image {
                id: id_fire_extinguisher_3axle_rect4
                x:110
                y:200
                height: sourceSize.height
                width: sourceSize.width
                source: "pics/Menu/Door__1_.png"
                visible: true
            }

            Image {
                id: id_fire_extinguisher1_3axle
                x:1205
                y: 70
                height: 59
                width: 25
                source: "pics/Menu/Fire_extinguishers_for_mnu__1_.png"
                visible: true
                ColorOverlay{
                    anchors.fill: id_fire_extinguisher1_3axle
                    source: id_fire_extinguisher1_3axle
					color: id_mainmenu.param_menu_names[0][pos1]
                }
            }


            Image {
                id: id_fire_extinguisher2_3axle
                x:1062
                y: 190
                height: 59
                width: 25
                source: "pics/Menu/Fire_extinguishers_for_mnu__1_.png"
                visible: true
                ColorOverlay{
                    anchors.fill: id_fire_extinguisher2_3axle
                    source: id_fire_extinguisher2_3axle
					color: id_mainmenu.param_menu_names[1][pos1]
                }
            }



            Image {
                id: id_fire_extinguisher_3axle_3
                x:1005
                y: 190
                height: 59
                width: 25
                source: "pics/Menu/Fire_extinguishers_for_mnu__1_.png"
                visible: true
                ColorOverlay{
                    anchors.fill: id_fire_extinguisher_3axle_3
                    source: id_fire_extinguisher_3axle_3
					color: id_mainmenu.param_menu_names[2][pos1]
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

