import QtQuick 2.0
import QtMultimedia 5.6
import QtGraphicalEffects 1.12


Item {
    id : id_menu_parameters_brake_pads
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

    property string brakepaddswear_tyre1_text_color: "white"
    property string brakepaddswear_tyre2_text_color: "white"
    property string brakepaddswear_tyre3_text_color: "white"
    property string brakepaddswear_tyre4_text_color: "white"
    property string brakepaddswear_tyre5_text_color: "white"
    property string brakepaddswear_tyre6_text_color: "white"

	property variant value_brakepads_1 : id_mainmenu.right_menu_values_list[0].split(':')
	property variant value_brakepads_2 : id_mainmenu.right_menu_values_list[1].split(':')
	property variant value_brakepads_3 : id_mainmenu.right_menu_values_list[2].split(':')
	property variant value_brakepads_4 : id_mainmenu.right_menu_values_list[3].split(':')
	property variant value_brakepads_5 : id_mainmenu.right_menu_values_list[4].split(':')
	property variant value_brakepads_6 : id_mainmenu.right_menu_values_list[5].split(':')

	Rectangle{
        id: id_brakepads_right_whole
        height: 500
        width : 1462
        x: id_subitems_left.x + 391
        y:id_menulayer.y
        color: "transparent"
		visible: parent.visible

        //Handling Header
		Rectangle{
			id: id_engine_header
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
					text: id_mainmenu.main_menu_names[id_mainmenu.main_menu_pos]
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
					FontLoader { id: engine_name_font; source: "Fonts/Roboto-Italic.ttf" }
					font { family: engine_name_font.name; pixelSize: 23;}
					font.letterSpacing: 1.0
				}
			}
		}

        Rectangle{
            id: id_brakepaddswear_right
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
                id: id_brakepaddswear_right_bar
                x:87
                y:27
                height: sourceSize.height
                width: sourceSize.width
                source: "pics/Menu/Bus_layout_2ax__1_.png"  // 2 Axles
                visible: true
            }

            Image {
                id: id_brakepaddswear_tyre1_yellow
                anchors.right: parent.right
                anchors.rightMargin: 550
                y: 20
                height: sourceSize.height+ 4
                width: sourceSize.width  + 12
                source: {
					if (value_brakepads_1[1] === "yellow") {
                        brakepaddswear_tyre1_text_color = "yellow"
                        return "pics/Menu/tire_menu_yellow.png"
                    } else {
                        brakepaddswear_tyre1_text_color = "white"
                        return ""
                    }
                }
				visible: (value_brakepads_1[1] === "yellow")
            }

            Text {
                id: id_brakepaddswear_two_axle_first
				text: value_brakepads_1[0]
                anchors.right: parent.right
                anchors.rightMargin: 465
				y: 30
                color: brakepaddswear_tyre1_text_color
                visible: true
                wrapMode: Text.WordWrap
                FontLoader { id: brakepaddswear_two_axle_first_text_font; source: "Fonts/Roboto-Italic.ttf" }
                font { family:brakepaddswear_two_axle_first_text_font.name; pixelSize: 24;}
                font.letterSpacing: 1.0
            }

            Image {
                id: id_brakepaddswear_tyre2_yellow
                anchors.right: parent.right
                anchors.rightMargin: 550
                y: 210
                height: sourceSize.height + 4
                width: sourceSize.width + 12
                source: {
					if (value_brakepads_2[1] === "yellow") {
                        brakepaddswear_tyre2_text_color = "yellow"
                        return "pics/Menu/tire_menu_yellow.png"
                    } else {
                        brakepaddswear_tyre2_text_color = "white"
                        return ""
                    }
                }
				visible: (value_brakepads_2[1] === "yellow")
            }

            Text {
                id: id_brakepaddswear_two_axle_second
				text: value_brakepads_2[0]
                anchors.right: parent.right
                anchors.rightMargin: 465
                y: 220
                color: brakepaddswear_tyre2_text_color
                visible: true
                wrapMode: Text.WordWrap
                FontLoader { id: brakepaddswear_two_axle_second_text_font; source: "Fonts/Roboto-Italic.ttf" }
                font { family: brakepaddswear_two_axle_second_text_font.name; pixelSize: 24;}
                font.letterSpacing: 1.0
            }

            Image {
                id: id_brakepaddswear_tyre3_yellow
                anchors.left: parent.left
                anchors.leftMargin:  280
                y: 20
                height: sourceSize.height + 4
                width: sourceSize.width + 12
                source: {
					if (value_brakepads_3[1] === "yellow") {
                        brakepaddswear_tyre3_text_color = "yellow"
                        return "pics/Menu/tire_menu_yellow.png"
                    } else {
                        brakepaddswear_tyre3_text_color = "white"
                        return ""
                    }
                }
				visible: (value_brakepads_3[1] === "yellow")
            }

            Image {
                id: id_brakepaddswear_tyre3_2_yellow
                anchors.left: parent.left
                anchors.leftMargin:  280
                y: 58
                height: sourceSize.height + 4
                width: sourceSize.width + 12
                source: {
					if (value_brakepads_3[1] === "yellow") {
                        brakepaddswear_tyre3_text_color = "yellow"
                        return "pics/Menu/tire_menu_yellow.png"
                    } else {
                        brakepaddswear_tyre3_text_color = "white"
                        return ""
                    }
                }
				visible: (value_brakepads_3[1] === "yellow")
            }


            Text {
                id: id_brakepaddswear_two_axle_third
                anchors.left: parent.left
                anchors.leftMargin: 420
                y: 30
				text: value_brakepads_3[0]
                color: brakepaddswear_tyre3_text_color
                visible:true
                wrapMode: Text.WordWrap
                FontLoader { id: brakepaddswear_two_axle_third_text_font; source: "Fonts/Roboto-Italic.ttf" }
                font { family: brakepaddswear_two_axle_third_text_font.name; pixelSize: 24;}
                font.letterSpacing: 1.0
            }

            Image {
                id: id_brakepaddswear_tyre4_yellow
                anchors.left: parent.left
                anchors.leftMargin:  280
                y: 172
                height: sourceSize.height + 4
                width: sourceSize.width + 12
                source: {
					if (value_brakepads_4[1] === "yellow") {
                        brakepaddswear_tyre4_text_color = "yellow"
                        return "pics/Menu/tire_menu_yellow.png"
                    } else {
                        brakepaddswear_tyre4_text_color = "white"
                        return ""
                    }
                }
				visible: (value_brakepads_4[1] === "yellow")
            }


            Image {
                id: id_brakepaddswear_tyre4_2_yellow
                anchors.left: parent.left
                anchors.leftMargin:  280
                y: 210
                height: sourceSize.height + 4
                width: sourceSize.width + 12
                source: {
					if (value_brakepads_4[1] === "yellow") {
                        brakepaddswear_tyre4_text_color = "yellow"
                        return "pics/Menu/tire_menu_yellow.png"
                    } else {
                        brakepaddswear_tyre4_text_color = "white"
                        return ""
                    }
                }
				visible: (value_brakepads_4[1] === "yellow")
            }


            Text {
                id: id_brakepaddswear_two_axle_fourth
                anchors.left: parent.left
                anchors.leftMargin: 420
                y: 220
				text: value_brakepads_4[0]
                color: brakepaddswear_tyre4_text_color
                visible:true
                wrapMode: Text.WordWrap
                FontLoader { id: brakepaddswear_two_axle_fourth_text_font; source: "Fonts/Roboto-Italic.ttf" }
                font { family: brakepaddswear_two_axle_fourth_text_font.name; pixelSize: 24;}
                font.letterSpacing: 1.0
            }
        }

        //3 Axles
        Rectangle{
            id: id_brakepads_3_axle_right
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
                id: id_brakepads_3_axle_right_bar
                x:87
                y:25
                height: sourceSize.height
                width: sourceSize.width
                source: "pics/Menu/Bus_layout_3__1_.png" // 3 Axles
                visible: true
            }

            Image {
                id: id_brakepaddswear_tyre1_3axle_yellow
                anchors.right: parent.right
                anchors.rightMargin: 255
                y: 18
                height: sourceSize.height + 4
                width: sourceSize.width + 12
                source: {
					if (value_brakepads_1[1] === "yellow") {
                        brakepaddswear_tyre1_text_color = "yellow"
                        return "pics/Menu/tire_menu_yellow.png"
                    } else {
                        brakepaddswear_tyre1_text_color = "white"
                        return ""
                    }
                }
				visible: (value_brakepads_1[1] === "yellow")
            }

            Text {
                id: id_brakepads_3axle_first
                text: value_brakepads_1[0]
                anchors.right: parent.right
                anchors.rightMargin: 180
                y: 30
                color: brakepaddswear_tyre1_text_color
                visible: true
                wrapMode: Text.WordWrap
                FontLoader { id: first_brakepads_3axle_font; source: "Fonts/Roboto-Italic.ttf" }
                font { family: first_brakepads_3axle_font.name; pixelSize: 24;}
                font.letterSpacing: 1.0
            }

            Image {
                id: id_brakepaddswear_tyre2_3axle_yellow
                anchors.right: parent.right
                anchors.rightMargin: 255
                y: 210
                height: sourceSize.height + 4
                width: sourceSize.width + 12
                source: {
					if (value_brakepads_2[1] === "yellow") {
                        brakepaddswear_tyre2_text_color = "yellow"
                        return "pics/Menu/tire_menu_yellow.png"
                    } else {
                        brakepaddswear_tyre2_text_color = "white"
                        return ""
                    }
                }
				visible: (value_brakepads_2[1] === "yellow")
            }

            Text {
                id: id_brakepads_3axle_second
				text: value_brakepads_2[0]
                anchors.right: parent.right
                anchors.rightMargin:180
                y: 220
                color: brakepaddswear_tyre2_text_color
                visible: true
                wrapMode: Text.WordWrap
                FontLoader { id: second_brakepads_3axle_font; source: "Fonts/Roboto-Italic.ttf" }
                font { family: second_brakepads_3axle_font.name; pixelSize: 24;}
                font.letterSpacing: 1.0
            }

            Image {
                id: id_brakepaddswear_tyre3_3axle_yellow
                anchors.left: parent.left
                anchors.leftMargin: 640
                y: 20
                height: sourceSize.height + 4
                width: sourceSize.width + 12
                source: {
					if (value_brakepads_3[1] === "yellow") {
                        brakepaddswear_tyre3_text_color = "yellow"
                        return "pics/Menu/tire_menu_yellow.png"
                    } else {
                        brakepaddswear_tyre3_text_color = "white"
                        return ""
                    }
                }
				visible: (value_brakepads_3[1] === "yellow")
            }

            Image {
                id: id_brakepaddswear_tyre4_3axle_yellow
                anchors.left: parent.left
                anchors.leftMargin: 640
                y: 55
                height: sourceSize.height + 4
                width: sourceSize.width + 12
                source: {
					if (value_brakepads_3[1] === "yellow") {
                        brakepaddswear_tyre3_text_color = "yellow"
                        return "pics/Menu/tire_menu_yellow.png"
                    } else {
                        brakepaddswear_tyre3_text_color = "white"
                        return ""
                    }
                }
				visible: (value_brakepads_3[1] === "yellow")
            }

            Text {
                id: id_brakepads_3axle_third
				text: value_brakepads_3[0]
                anchors.left: parent.left
                anchors.leftMargin: 775
                y: 30
                color: brakepaddswear_tyre3_text_color
                visible:true
                wrapMode: Text.WordWrap
                FontLoader { id: third_brakepads_3axle_font; source: "Fonts/Roboto-Italic.ttf" }
                font { family: third_brakepads_3axle_font.name; pixelSize: 24;}
                font.letterSpacing: 1.0
            }


            Image {
                id: id_brakepaddswear_tyre5_3axle_yellow
                anchors.left: parent.left
                anchors.leftMargin: 640
                y: 172
                height: sourceSize.height + 4
                width: sourceSize.width + 12
                source: {
					if (value_brakepads_4[1] === "yellow") {
                        brakepaddswear_tyre4_text_color = "yellow"
                        return "pics/Menu/tire_menu_yellow.png"
                    } else {
                        brakepaddswear_tyre4_text_color = "white"
                        return ""
                    }
                }
				visible: (value_brakepads_4[1] === "yellow")
            }

            Image {
                id: id_brakepaddswear_tyre6_3axle_yellow
                anchors.left: parent.left
                anchors.leftMargin: 640
                y: 210
                height: sourceSize.height + 4
                width: sourceSize.width + 12
                source: {
					if (value_brakepads_4[1] === "yellow") {
                        brakepaddswear_tyre4_text_color = "yellow"
                        return "pics/Menu/tire_menu_yellow.png"
                    } else {
                        brakepaddswear_tyre4_text_color = "white"
                        return ""
                    }
                }
				visible: (value_brakepads_4[1] === "yellow")
            }

            Text {
                id: id_brakepads_3axle_fourth
				text: value_brakepads_4[0]
                anchors.left: parent.left
                anchors.leftMargin: 775
                y: 220
                color: brakepaddswear_tyre4_text_color
                visible:true
                wrapMode: Text.WordWrap
                FontLoader { id: fourth_brakepads_3axle_font; source: "Fonts/Roboto-Italic.ttf" }
                font { family: fourth_brakepads_3axle_font.name; pixelSize: 24;}
                font.letterSpacing: 1.0
            }

            Image {
                id: id_brakepaddswear_tyre7_3axle_yellow
                anchors.left: parent.left
                anchors.leftMargin: 250
                y: 20
                height: sourceSize.height +4
                width: sourceSize.width + 12
                source: {
					if (value_brakepads_5[1] === "yellow") {
                        brakepaddswear_tyre5_text_color = "yellow"
                        return "pics/Menu/tire_menu_yellow.png"
                    } else {
                        brakepaddswear_tyre5_text_color = "white"
                        return ""
                    }
                }
				visible: (value_brakepads_5[1] === "yellow")
            }

            Image {
                id: id_brakepaddswear_tyre8_3axle_yellow
                anchors.left: parent.left
                anchors.leftMargin: 250
                y: 55
                height: sourceSize.height + 4
                width: sourceSize.width + 12
                source: {
					if (value_brakepads_5[1] === "yellow") {
                        brakepaddswear_tyre5_text_color = "yellow"
                        return "pics/Menu/tire_menu_yellow.png"
                    } else {
                        brakepaddswear_tyre5_text_color = "white"
                        return ""
                    }
                }
				visible: (value_brakepads_5[1] === "yellow")
            }

            Text {
                id: id_brakepads_3axle_fifth
				text: value_brakepads_5[0]
                anchors.left: parent.left
                anchors.leftMargin: 400
                y: 30
                color: brakepaddswear_tyre5_text_color
                visible: true
                wrapMode: Text.WordWrap
                FontLoader { id: fifth_brakepads_3axle_font; source: "Fonts/Roboto-Italic.ttf" }
                font { family: fifth_brakepads_3axle_font.name; pixelSize: 24;}
                font.letterSpacing: 1.0
            }

            Image {
                id: id_brakepaddswear_tyre9_3axle_yellow
                anchors.left: parent.left
                anchors.leftMargin: 250
                y: 172
                height: sourceSize.height + 4
                width: sourceSize.width + 12
                source: {
					if (value_brakepads_6[1] === "yellow") {
                        brakepaddswear_tyre6_text_color = "yellow"
                        return "pics/Menu/tire_menu_yellow.png"
                    } else {
                        brakepaddswear_tyre6_text_color = "white"
                        return ""
                    }
                }
				visible: (value_brakepads_6[1] === "yellow")
            }

            Image {
                id: id_brakepaddswear_tyre10_3axle_yellow
                anchors.left: parent.left
                anchors.leftMargin: 250
                y: 210
                height: sourceSize.height + 4
                width: sourceSize.width +12
                source: {
					if (value_brakepads_6[1] === "yellow") {
                        brakepaddswear_tyre6_text_color = "yellow"
                        return "pics/Menu/tire_menu_yellow.png"
                    } else {
                        brakepaddswear_tyre6_text_color = "white"
                        return ""
                    }
                }
				visible: (value_brakepads_6[1] === "yellow")
            }

            Text {
                id: id_brakepads_3axle_sixth
				text: value_brakepads_6[0]
                anchors.left: parent.left
                anchors.leftMargin: 400
                y: 220
                color: brakepaddswear_tyre6_text_color
                visible:true
                wrapMode: Text.WordWrap
                FontLoader { id: sixth_brakepads_3axle_font; source: "Fonts/Roboto-Italic.ttf" }
                font { family: sixth_brakepads_3axle_font.name; pixelSize: 24;}
                font.letterSpacing: 1.0
            }
        }

        Rectangle {
            id: id_brakepads_right_footer
            width: 1200
            height: 80
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            color: "transparent"
            Flow {
                anchors.centerIn: parent
                anchors.horizontalCenterOffset: 700
                //anchors.verticalCenterOffset: 165
                Text {
                    text: "1"
                    color: "#21B1D0"
                    wrapMode: Text.WordWrap
                    FontLoader { id: parameter_selector_font; source: "Fonts/Roboto-Italic.ttf" }
                    font { family: parameter_selector_font.name; pixelSize: 25;}
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
                    FontLoader { id: parameter_total_font; source: "Fonts/Roboto-Italic.ttf" }
                    font { family: parameter_total_font.name; pixelSize: 25;}
                    font.letterSpacing: 1.0
                }
            }
        }
    }
}

