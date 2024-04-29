import QtQuick 2.0
import QtMultimedia 5.6
import QtGraphicalEffects 1.12


Item {
    id : id_menu_diagnostics_heaters
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
        id: id_heaters_right_whole
        height: 500
        width : 1462
        x: id_subitems_left.x + 391
        y:id_menulayer.y
        color: "transparent"
		visible: parent.visible

        //Handling Header
        Rectangle{
            id: id_heaters_header
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
            id: id_heaters_right
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
                id: id_heaters_right_bar
                x:87
                y:27
                height: sourceSize.height
                width: sourceSize.width
                source: "pics/Menu/Bus_layout_2ax__1_.png" // 2 Axles
                visible: true
            }

            Image {
                id: id_heaters_rect1
                x:920
                y:200
                height: sourceSize.height
                width: sourceSize.width
                source: "pics/Menu/Door__1_.png"
                visible: true
            }

            Image {
                id: id_heaters_rect2
                x:522
                y:200
                height: sourceSize.height
                width: sourceSize.width
                source: "pics/Menu/Door__1_.png"
                visible: true
            }
            Image {
                id: id_heaters_rect3
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
                anchors.leftMargin: 1079
                y: 100
                height: sourceSize.height
                width: sourceSize.width
                source: "pics/Menu/1.png"
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
                anchors.leftMargin: 1009
                y: 150
                height: sourceSize.height
                width: sourceSize.width
                source: "pics/Menu/1.png"
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
                anchors.leftMargin: 880
                y: 70
                height: sourceSize.height
                width: sourceSize.width
                source: "pics/Menu/1.png"
                visible: true
                ColorOverlay{
                    anchors.fill: id_fire_extinguisher3
                    source: id_fire_extinguisher3
					color: id_mainmenu.param_menu_names[2][pos1]
                }
            }





            Image {
                id: id_fire_extinguisher4
                anchors.left:   parent.left
                anchors.leftMargin: 730
                y: 205
                height: sourceSize.height
                width: sourceSize.width
                source: "pics/Menu/1.png"

                visible: true
                ColorOverlay{
                    anchors.fill: id_fire_extinguisher4
                    source: id_fire_extinguisher4
					color: id_mainmenu.param_menu_names[3][pos1]
                }
            }

            Image {
                id: id_fire_extinguisher5
                anchors.left:   parent.left
                anchors.leftMargin: 670
                y: 205
                height: sourceSize.height
                width: sourceSize.width
                source: "pics/Menu/1.png"

                visible: true
                ColorOverlay{
                    anchors.fill: id_fire_extinguisher5
                    source: id_fire_extinguisher5
					color: id_mainmenu.param_menu_names[4][pos1]
                }
            }



            Image {
                id: id_fire_extinguisher6
                anchors.left:   parent.left
                anchors.leftMargin: 466
                y: 205
                height: sourceSize.height
                width: sourceSize.width
                source: "pics/Menu/1.png"

                visible: true
                ColorOverlay{
                    anchors.fill: id_fire_extinguisher6
                    source: id_fire_extinguisher6
					color: id_mainmenu.param_menu_names[5][pos1]
                }
            }
            Image {
                id: id_fire_extinguisher7
                anchors.left:   parent.left
                anchors.leftMargin: 670
                y:40
                height: sourceSize.height
                width: sourceSize.width
                source: "pics/Menu/1.png"

                visible: true
                ColorOverlay{
                    anchors.fill: id_fire_extinguisher7
                    source: id_fire_extinguisher7
					color: id_mainmenu.param_menu_names[6][pos1]
                }
            }

            Image {
                id: id_fire_extinguisher9
                anchors.left: parent.left
                anchors.leftMargin: 158
                y: 205
                height: sourceSize.height
                width: sourceSize.width
                source: "pics/Menu/1.png"

                visible: true
                ColorOverlay{
                    anchors.fill: id_fire_extinguisher9
                    source: id_fire_extinguisher9
					color: id_mainmenu.param_menu_names[8][pos1]
                }
            }



        }


        //3 Axles
        Rectangle{
            id: id_heaters_3_axle_right
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
                id: id_heaters_3_axle_right_bar
                x:87
                y:25
                height: sourceSize.height
                width: sourceSize.width
                source: "pics/Menu/Bus_layout_3__1_.png" // 3 Axles
                visible: true
            }
            Image {
                id: id_heaters_3axle_rect1
                x:1210
                y:200
                height: sourceSize.height
                width: sourceSize.width
                source: "pics/Menu/Door__1_.png"
                visible: true
            }

            Image {
                id: id_heaters_3axle_rect2
                x:856
                y:200
                height: sourceSize.height
                width: sourceSize.width
                source: "pics/Menu/Door__1_.png"
                visible: true
            }
            Image {
                id: id_heaters_3axle_rect3
                x:379
                y:200
                height: sourceSize.height
                width: sourceSize.width
                source: "pics/Menu/Door__1_.png"
                visible: true
            }
            Image {
                id: id_heaters_3axle_rect4
                x:110
                y:200
                height: sourceSize.height
                width: sourceSize.width
                source: "pics/Menu/Door__1_.png"
                visible: true
            }

            Image {
                id: id_fire_3axle_extinguisher1
                anchors.left:   parent.left
                anchors.leftMargin: 1360
                y: 100
                height: sourceSize.height
                width: sourceSize.width
                source: "pics/Menu/1.png"
                visible: true
                ColorOverlay{
                    anchors.fill: id_fire_3axle_extinguisher1
                    source: id_fire_3axle_extinguisher1
					color: id_mainmenu.param_menu_names[0][pos1]
                }
            }

            Image {
                id: id_fire_3axle_extinguisher2
                anchors.left:   parent.left
                anchors.leftMargin: 1310
                y: 150
                height: sourceSize.height
                width: sourceSize.width
                source: "pics/Menu/1.png"
                visible: true
                ColorOverlay{
                    anchors.fill: id_fire_3axle_extinguisher2
                    source: id_fire_3axle_extinguisher2
					color: id_mainmenu.param_menu_names[1][pos1]
                }
            }

            Image {
                id: id_fire_3axle_extinguisher3
                anchors.left:   parent.left
                anchors.leftMargin:1160
                y: 70
                height: sourceSize.height
                width: sourceSize.width
                source: "pics/Menu/1.png"
                visible: true
                ColorOverlay{
                    anchors.fill: id_fire_3axle_extinguisher3
                    source: id_fire_3axle_extinguisher3
					color: id_mainmenu.param_menu_names[2][pos1]
                }
            }





            Image {
                id: id_fire_3axle_extinguisher4
                anchors.left: parent.left
                anchors.leftMargin:1041
                y: 205
                height: sourceSize.height
                width: sourceSize.width
                source: "pics/Menu/1.png"

                visible: true
                ColorOverlay{
                    anchors.fill: id_fire_3axle_extinguisher4
                    source: id_fire_3axle_extinguisher4
					color: id_mainmenu.param_menu_names[3][pos1]
                }
            }

            Image {
                id: id_fire_3axle_extinguisher5
                anchors.left: parent.left
                anchors.leftMargin: 990
                y: 205
                height: sourceSize.height
                width: sourceSize.width
                source: "pics/Menu/1.png"

                visible: true
                ColorOverlay{
                    anchors.fill: id_fire_3axle_extinguisher5
                    source: id_fire_3axle_extinguisher5
					color: id_mainmenu.param_menu_names[4][pos1]
                }
            }



            Image {
                id: id_fire_3axle_extinguisher6
                anchors.left: parent.left
                anchors.leftMargin:807
                y: 205
                height: sourceSize.height
                width: sourceSize.width
                source: "pics/Menu/1.png"

                visible: true
                ColorOverlay{
                    anchors.fill: id_fire_3axle_extinguisher6
                    source: id_fire_3axle_extinguisher6
					color:id_mainmenu.param_menu_names[5][pos1]
                }
            }
            Image {
                id: id_fire_3axle_extinguisher7
                anchors.left: parent.left
                anchors.leftMargin: 766
                y: 40
                height: sourceSize.height
                width: sourceSize.width
                source: "pics/Menu/1.png"

                visible: true
                ColorOverlay{
                    anchors.fill: id_fire_3axle_extinguisher7
                    source: id_fire_3axle_extinguisher7
					color: id_mainmenu.param_menu_names[6][pos1]
                }
            }


            Image {
                id: id_fire_3axle_extinguisher8
                anchors.left: parent.left
                anchors.leftMargin: 466
                y: 205
                height: sourceSize.height
                width: sourceSize.width
                source: "pics/Menu/1.png"

                visible: true
                ColorOverlay{
                    anchors.fill: id_fire_3axle_extinguisher8
                    source: id_fire_3axle_extinguisher8
					color:id_mainmenu.param_menu_names[7][pos1]
                }
            }

            Image {
                id: id_fire_3axle_extinguisher9
                anchors.left: parent.left
                anchors.leftMargin: 130
                y: 205
                height: sourceSize.height
                width: sourceSize.width
                source: "pics/Menu/1.png"

                visible: true
                ColorOverlay{
                    anchors.fill: id_fire_3axle_extinguisher9
                    source: id_fire_3axle_extinguisher9
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

