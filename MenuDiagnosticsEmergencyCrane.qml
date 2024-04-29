import QtQuick 2.0
import QtMultimedia 5.6
import QtGraphicalEffects 1.12


Item {
    id : id_menu_diagnostics_emergency_cranes
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
        id: id_emergency_cranes_right_whole
        height: 500
        width : 1462
        x: id_subitems_left.x + 391
        y:id_menulayer.y
        color: "transparent"
        visible: id_menu_diagnostics.emergency_cranes_items_visibility

        //Handling Header
        Rectangle{
            id: id_emergency_cranes_header
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
            id: id_emergency_cranes_right
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
            color:"transparent"
            
            Image {
                id: id_emergency_cranes_right_bar
                x:87
                y:27
                height: sourceSize.height
                width: sourceSize.width
                source: "pics/Menu/Bus_layout_2ax__1_.png" // 2 Axles
                visible: true
            }

            Image {
                id:id_door_emergency_cranes_inside_door3
                x:138
                y: 200
                height: sourceSize.height
                width: sourceSize.width
                source: "pics/Menu/Door__1_.png"
                visible: true
            }

            Image {
                id: id_door_emergency_cranes_inside_door2
                x:522
                y:200
                height: sourceSize.height
                width: sourceSize.width
                source: "pics/Menu/Door__1_.png"
                visible: true
            }

            Image {
                id: id_door_emergency_cranes_inside_door1
                x:920
                y:200
                height: sourceSize.height
                width: sourceSize.width
                source: "pics/Menu/Door__1_.png"
                visible: true
            }

            Image {
                id: id_emergency_cranes_door1_inside
                x:962
                y:206
                height: sourceSize.height
                width: sourceSize.width
                source: "pics/Menu/Emergence cranes.png"
                visible: true
                ColorOverlay{
                    anchors.fill: id_emergency_cranes_door1_inside
                    source: id_emergency_cranes_door1_inside
					color: id_mainmenu.param_menu_names[0][pos1]
                }
            }

            Image {
                id: id_emergency_cranes_door1_outside
                x:962
                y:275
                height: sourceSize.height
                width: sourceSize.width
                source: "pics/Menu/Emergence cranes.png"
                visible: true
                ColorOverlay{
                    anchors.fill: id_emergency_cranes_door1_outside
                    source: id_emergency_cranes_door1_outside
					color: id_mainmenu.param_menu_names[1][pos1]
                }
            }
            Image {
                id: id_emergency_cranes_door2_inside
                x:564
                y: 206
                height: sourceSize.height
                width: sourceSize.width
                source: "pics/Menu/Emergence cranes.png"
                visible: true
                ColorOverlay{
                    anchors.fill: id_emergency_cranes_door2_inside
                    source: id_emergency_cranes_door2_inside
					color: id_mainmenu.param_menu_names[2][pos1]
                }
            }


            Image {
                id: id_emergency_cranes_door2_outside
                x:564
                y: 275
                height: sourceSize.height
                width: sourceSize.width
                source: "pics/Menu/Emergence cranes.png"
                visible: true
                ColorOverlay{
                    anchors.fill: id_emergency_cranes_door2_outside
                    source: id_emergency_cranes_door2_outside
					color: id_mainmenu.param_menu_names[3][pos1]
                }
            }


            Image {
                id: id_emergency_cranes_door3_inside
                x:180
                y: 206
                height: sourceSize.height
                width: sourceSize.width
                source: "pics/Menu/Emergence cranes.png"
                visible: true
                ColorOverlay{
                    anchors.fill: id_emergency_cranes_door3_inside
                    source: id_emergency_cranes_door3_inside
					color: id_mainmenu.param_menu_names[4][pos1]
                }
            }

            Image {
                id: id_emergency_cranes_door3_outside
                x:180
                y: 275
                height: sourceSize.height
                width: sourceSize.width
                source: "pics/Menu/Emergence cranes.png"
                visible: true
                ColorOverlay{
                    anchors.fill: id_emergency_cranes_door3_outside
                    source: id_emergency_cranes_door3_outside
					color: id_mainmenu.param_menu_names[5][pos1]
                }
            }





        }


        //3 Axles
        Rectangle{
            id: id_emergency_cranes_3_axle_right
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
                id: id_emergency_cranes_3_axle_right_bar
                x:87
                y:25
                width: sourceSize.width
                source: "pics/Menu/Bus_layout_3__1_.png" // 3 Axles
                visible: true
            }

            Image {
                id: id_door_emergency_cranes_3axle_inside_door1
                x:1210
                y:200
                height: sourceSize.height
                width: sourceSize.width
                source: "pics/Menu/Door__1_.png"
                visible: true
            }

            Image {
                id: id_door_emergency_cranes_3axle_inside_door2
                x:856
                y:200
                height: sourceSize.height
                width: sourceSize.width
                source: "pics/Menu/Door__1_.png"
                visible: true
            }
            Image {
                id: id_door_emergency_cranes_3axle_inside_door3
                x:379
                y:200
                height: sourceSize.height
                width: sourceSize.width
                source: "pics/Menu/Door__1_.png"
                visible: true
            }
            Image {
                id: id_door_emergency_cranes_3axle_inside_door4
                x:110
                y:200
                height: sourceSize.height
                width: sourceSize.width
                source: "pics/Menu/Door__1_.png"
                visible: true
            }

            Image {
                id: id_emergency_cranes_3axle_door1_inside
                x:1260
                y: 206
                height: sourceSize.height
                width: sourceSize.width
                source: "pics/Menu/Emergence cranes.png"
                visible: true
                ColorOverlay{
                    anchors.fill: id_emergency_cranes_3axle_door1_inside
                    source: id_emergency_cranes_3axle_door1_inside
					color: id_mainmenu.param_menu_names[0][pos1]
                }
            }

            Image {
                id: id_emergency_cranes_3axle_door1_outside
                x:1260
                y:275
                height: sourceSize.height
                width: sourceSize.width
                source: "pics/Menu/Emergence cranes.png"
                visible: true
                ColorOverlay{
                    anchors.fill: id_emergency_cranes_3axle_door1_outside
                    source: id_emergency_cranes_3axle_door1_outside
					color: id_mainmenu.param_menu_names[1][pos1]
                }
            }

            Image {
                id: id_emergency_cranes_3axle_door2_inside
                x:898
                y:206
                height: sourceSize.height
                width: sourceSize.width
                source: "pics/Menu/Emergence cranes.png"
                visible: true
                ColorOverlay{
                    anchors.fill: id_emergency_cranes_3axle_door2_inside
                    source: id_emergency_cranes_3axle_door2_inside
					color: id_mainmenu.param_menu_names[2][pos1]
                }
            }

            Image {
                id: id_emergency_cranes_3axle_door2_outside
                x:898
                y:275
                height: sourceSize.height
                width: sourceSize.width
                source: "pics/Menu/Emergence cranes.png"
                visible: true
                ColorOverlay{
                    anchors.fill: id_emergency_cranes_3axle_door2_outside
                    source: id_emergency_cranes_3axle_door2_outside
					color: id_mainmenu.param_menu_names[3][pos1]
                }
            }

            Image {
                id: id_emergency_cranes_3axle_door3_inside
                x:421
                y:206
                height: sourceSize.height
                width: sourceSize.width
                source: "pics/Menu/Emergence cranes.png"
                visible: true
                ColorOverlay{
                    anchors.fill: id_emergency_cranes_3axle_door3_inside
                    source: id_emergency_cranes_3axle_door3_inside
					color: id_mainmenu.param_menu_names[4][pos1]
                }
            }
            Image {
                id: id_emergency_cranes_3axle_door3_outside
                x:421
                y:275
                height: sourceSize.height
                width: sourceSize.width
                source: "pics/Menu/Emergence cranes.png"
                visible: true
                ColorOverlay{
                    anchors.fill: id_emergency_cranes_3axle_door3_outside
                    source: id_emergency_cranes_3axle_door3_outside
					color: id_mainmenu.param_menu_names[5][pos1]
                }
            }
            Image {
                id: id_emergency_cranes_3axle_door4_inside
                x:161
                y:206
                height: sourceSize.height
                width: sourceSize.width
                source: "pics/Menu/Emergence cranes.png"
                visible: true
                ColorOverlay{
                    anchors.fill: id_emergency_cranes_3axle_door4_inside
                    source: id_emergency_cranes_3axle_door4_inside
					color: id_mainmenu.param_menu_names[6][pos1]
                }
            }
            Image {
                id: id_emergency_cranes_3axle_door4_outside
                x:161
                y:275
                height: sourceSize.height
                width: sourceSize.width
                source: "pics/Menu/Emergence cranes.png"
                visible: true
                ColorOverlay{
                    anchors.fill: id_emergency_cranes_3axle_door4_outside
                    source: id_emergency_cranes_3axle_door4_outside
					color: id_mainmenu.param_menu_names[7][pos1]
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

