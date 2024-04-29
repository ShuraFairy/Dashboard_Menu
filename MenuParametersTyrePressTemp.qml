import QtQuick 2.0
import QtQuick.Layouts 1.12
import QtMultimedia 5.6
import QtGraphicalEffects 1.12


Item {
    id : id_menu_parameters_tyre_press_temp
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

    property string tyre1_text_color: "white"
    property string tyre2_text_color: "white"
    property string tyre3_text_color: "white"
    property string tyre4_text_color: "white"
    property string tyre5_text_color: "white"
    property string tyre6_text_color: "white"
    property string tyre7_text_color: "white"
    property string tyre8_text_color: "white"
    property string tyre9_text_color: "white"
    property string tyre10_text_color: "white"

    Rectangle{
        id: id_tirepressuretemperature_right_whole
        height: 500
        width : 1462
        x: id_subitems_left.x + 391
        y:id_menulayer.y
        color: "transparent"
		visible: parent.visible
        //Handling Header
        Rectangle{
            id: id_tyrepresstemp_header
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
					text:id_mainmenu.main_menu_names[0]
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
                    FontLoader { id: tyrepresstemp_system_font; source: "Fonts/Roboto-Italic.ttf" }
                    font { family: tyrepresstemp_system_font.name; pixelSize: 23;}
                    font.letterSpacing: 1.0
                }
            }
        }

        Rectangle{
            id: id_tire_data_2_axle_right
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
                id: id_tire_data_2_axle_right_bar
                x:87
                y:27
                height: sourceSize.height
                width: sourceSize.width
                source: "pics/Menu/Bus_layout_2ax__1_.png" // 2 Axles
                visible: true
            }

            Image {
                id: id_tyrepressure_tyre1_yellow
                anchors.right: parent.right
                anchors.rightMargin: 550
                y: 20
                height: sourceSize.height +4
                width: sourceSize.width +12
                source: {
					if (id_mainmenu.param_menu_names[pos0][pos1] === "yellow" || id_mainmenu.param_menu_names[pos0][pos1] === "--") {
                        tyre1_text_color = "yellow"
                        "pics/Menu/tire_menu_yellow.png"
					} else if (id_mainmenu.param_menu_names[pos0][pos1] === "red") {
                        tyre1_text_color = "red"
                        "pics/Menu/tire_menu_red.png"
                    } else {
                        tyre1_text_color = "white"
                        "" // Add a default source if none of the conditions match
                    }
                }
				visible: id_mainmenu.param_menu_names[pos0][pos1] === "yellow" ||
						 id_mainmenu.param_menu_names[pos0][pos1] === "--" ||
						 id_mainmenu.param_menu_names[pos0][pos1] === "red"
            }

            Text {
                id: id_tyre1_temperature
				text: id_mainmenu.param_menu_names[pos0][0]
                anchors.right: parent.right
                anchors.rightMargin: 465
                y: 30
                color: tyre1_text_color
                visible: true
                wrapMode: Text.WordWrap
                FontLoader { id: tyre1_text_font; source: "Fonts/Roboto-Italic.ttf" }
                font { family: tyre1_text_font.name; pixelSize: 24;}
                font.letterSpacing: 1.0
            }

            Image {
                id: id_tyrepressure_tyre2_yellow
                anchors.right: parent.right
                anchors.rightMargin: 550
                y: 210
                height: sourceSize.height + 4
                width: sourceSize.width + 12
                source: {
					if((id_mainmenu.param_menu_names[1][pos1] === "yellow") || (id_mainmenu.param_menu_names[1][pos1] === "--")) {
                        tyre2_text_color = "yellow"
                        "pics/Menu/tire_menu_yellow.png"
					} else if (id_mainmenu.param_menu_names[1][pos1] === "red") {
                        tyre2_text_color = "red"
                        "pics/Menu/tire_menu_red.png"
                    } else {
                        tyre2_text_color = "white"
                        "" // Add a default source if none of the conditions match
                    }
                }
				visible: id_mainmenu.param_menu_names[1][pos1] === "yellow" ||
						 id_mainmenu.param_menu_names[1][pos1] === "--" ||
						 id_mainmenu.param_menu_names[1][pos1] === "red"
            }

            Text {
                id: id_tyre2_temperature
				text: id_mainmenu.param_menu_names[1][0]
                anchors.right: parent.right
                anchors.rightMargin: 465
                y: 220
                color: tyre2_text_color
                visible: true
                wrapMode: Text.WordWrap
                FontLoader { id: tyre2_text_font; source: "Fonts/Roboto-Italic.ttf" }
                font { family: tyre2_text_font.name; pixelSize: 24;}
                font.letterSpacing: 1.0
            }

            Image {
                id: id_tyrepressure_tyre3_yellow
                anchors.left: parent.left
                anchors.leftMargin:  280
                y: 20
                height: sourceSize.height + 4
                width: sourceSize.width + 12
                source: {
					if((id_mainmenu.param_menu_names[2][pos1] === "yellow") || (id_mainmenu.param_menu_names[2][pos1] === "--")){
                        tyre3_text_color = "yellow"
                        "pics/Menu/tire_menu_yellow.png"
					} else if (id_mainmenu.param_menu_names[2][pos1] === "red") {
                        tyre3_text_color = "red"
                        "pics/Menu/tire_menu_red.png"
                    } else {
                        tyre3_text_color = "white"
                        "" // Add a default source if none of the conditions match
                    }
                }
				visible: id_mainmenu.param_menu_names[2][pos1] === "yellow" ||
						 id_mainmenu.param_menu_names[2][pos1] === "--" ||
						 id_mainmenu.param_menu_names[2][pos1] === "red"
            }


            Text {
                id: id_tyre3_temperature
				text: id_mainmenu.param_menu_names[2][0]
                anchors.left: parent.left
                anchors.leftMargin: 420
                y: 65
                color: tyre3_text_color
                visible:true
                wrapMode: Text.WordWrap
                FontLoader { id: tyre3_text_font; source: "Fonts/Roboto-Italic.ttf" }
                font { family: tyre3_text_font.name; pixelSize: 24;}
                font.letterSpacing: 1.0
            }

            Image {
                id: id_tyrepressure_tyre4_yellow
                anchors.left: parent.left
                anchors.leftMargin:  280
                y: 58
                height: sourceSize.height +4
                width: sourceSize.width + 12
                source: {
					if((id_mainmenu.param_menu_names[3][pos1] === "yellow") || (id_mainmenu.param_menu_names[3][pos1] === "--")){
                        tyre4_text_color = "yellow"
                        "pics/Menu/tire_menu_yellow.png"
					} else if (id_mainmenu.param_menu_names[3][pos1] === "red") {
                        tyre4_text_color = "red"
                        "pics/Menu/tire_menu_red.png"
                    } else {
                        tyre4_text_color = "white"
                        "" // Add a default source if none of the conditions match
                    }
                }
				visible: id_mainmenu.param_menu_names[3][pos1] === "yellow" ||
						 id_mainmenu.param_menu_names[3][pos1] === "--" ||
						 id_mainmenu.param_menu_names[3][pos1] === "red"
            }

            Text {
                id: id_tyre4_temperature
				text: id_mainmenu.param_menu_names[3][0]
                anchors.left: parent.left
                anchors.leftMargin: 420
                y: 35
                color:tyre4_text_color
                visible:true
                wrapMode: Text.WordWrap
                FontLoader { id: tyre4_text_font; source: "Fonts/Roboto-Italic.ttf" }
                font { family: tyre4_text_font.name; pixelSize: 24;}
                font.letterSpacing: 1.0
            }




            Image {
                id: id_tyrepressure_tyre5_yellow
                anchors.left: parent.left
                anchors.leftMargin:  280
                y: 172
                height: sourceSize.height + 4
                width: sourceSize.width + 12
                source: {
					if((id_mainmenu.param_menu_names[4][pos1] === "yellow") || (id_mainmenu.param_menu_names[4][pos1] === "--")){
                        tyre5_text_color = "yellow"
                        "pics/Menu/tire_menu_yellow.png"
					} else if (id_mainmenu.param_menu_names[4][pos1] === "red") {
                        tyre5_text_color = "red"
                        "pics/Menu/tire_menu_red.png"
                    } else {
                        tyre5_text_color = "white"
                        "" // Add a default source if none of the conditions match
                    }
                }
				visible: id_mainmenu.param_menu_names[4][pos1] === "yellow" ||
						 id_mainmenu.param_menu_names[4][pos1] === "--" ||
						 id_mainmenu.param_menu_names[4][pos1] === "red"
            }

            Text {
                id: id_tyre5_temperature
				text: id_mainmenu.param_menu_names[4][0]
                anchors.left: parent.left
                anchors.leftMargin: 420
                y: 185
                color: tyre5_text_color
                visible:true
                wrapMode: Text.WordWrap
                FontLoader { id: tyre5_text_font; source: "Fonts/Roboto-Italic.ttf" }
                font { family: tyre5_text_font.name; pixelSize: 24;}
                font.letterSpacing: 1.0
            }

            Image {
                id: id_tyrepressure_tyre6_yellow
                anchors.left: parent.left
                anchors.leftMargin:  280
                y: 210
                height: sourceSize.height + 4
                width: sourceSize.width + 12
                source: {
					if((id_mainmenu.param_menu_names[5][pos1] === "yellow") || (id_mainmenu.param_menu_names[5][pos1] === "--")){
                        tyre6_text_color = "yellow"
                        "pics/Menu/tire_menu_yellow.png"
					} else if (id_mainmenu.param_menu_names[5][pos1] === "red") {
                        tyre6_text_color = "red"
                        "pics/Menu/tire_menu_red.png"
                    } else {
                        tyre6_text_color = "white"
                        "" // Add a default source if none of the conditions match
                    }
                }
				visible: id_mainmenu.param_menu_names[5][pos1] === "yellow" ||
						 id_mainmenu.param_menu_names[5][pos1] === "--" ||
						 id_mainmenu.param_menu_names[5][pos1] === "red"
            }

            Text {
                id: id_tyre6_temperature
				text: id_mainmenu.param_menu_names[5][0]
                anchors.left: parent.left
                anchors.leftMargin: 420
                y: 220
                color: tyre6_text_color
                visible: true
                wrapMode: Text.WordWrap
                FontLoader { id: tyre6_temperature_font; source: "Fonts/Roboto-Italic.ttf" }
                font { family: tyre6_temperature_font.name; pixelSize: 24;}
                font.letterSpacing: 1.0
            }
            //Pressure
            Text {
                id: id_tyre1_pressure
				text: id_mainmenu.right_menu_values_list[0] + id_mainmenu.param_menu_names[pos0][6]
                anchors.right: parent.right
                anchors.rightMargin: 700
                y: 30
                color: tyre1_text_color
                visible: true
                wrapMode: Text.WordWrap
                FontLoader { id: tyre1_pressure_text_font; source: "Fonts/Roboto-Italic.ttf" }
                font { family: tyre1_pressure_text_font.name; pixelSize: 24;}
                font.letterSpacing: 1.0
            }
            Text {
                id: id_tyre2_pressure
				text: id_mainmenu.right_menu_values_list[1] + id_mainmenu.param_menu_names[1][6]
                anchors.right: parent.right
                anchors.rightMargin: 700
                y: 220
                color: tyre2_text_color
                visible: true
                wrapMode: Text.WordWrap
                FontLoader { id: tyre2_pressure_text_font; source: "Fonts/Roboto-Italic.ttf" }
                font { family: tyre2_pressure_text_font.name; pixelSize: 24;}
                font.letterSpacing: 1.0
            }

            ColumnLayout {
                anchors.left: parent.left
                anchors.leftMargin: 140
                y: 35
                Text {
                    id: id_tyre3_pressure
					text: id_mainmenu.right_menu_values_list[2] + id_mainmenu.param_menu_names[2][6]
                    color: tyre3_text_color
                    visible:true
                    wrapMode: Text.WordWrap
                    FontLoader { id: tyre3_pressure_text_font; source: "Fonts/Roboto-Italic.ttf" }
                    font { family: tyre3_text_font.name; pixelSize: 24;}
                    font.letterSpacing: 1.0
                }

                Text {
                    id: id_tyre4_pressure
					text: id_mainmenu.right_menu_values_list[3] + id_mainmenu.param_menu_names[3][6]
                    color: tyre4_text_color
                    visible:true
                    wrapMode: Text.WordWrap
                    FontLoader { id: tyre4_pressure_text_font; source: "Fonts/Roboto-Italic.ttf" }
                    font { family: tyre4_pressure_text_font.name; pixelSize: 24;}
                    font.letterSpacing: 1.0
                }
            }

            ColumnLayout {
                anchors.left: parent.left
                anchors.leftMargin: 140
                y: 190
                Text {
                    id: id_tyre5_pressure
					text: id_mainmenu.right_menu_values_list[4] + id_mainmenu.param_menu_names[4][6]
                    color: tyre5_text_color
                    visible:true
                    wrapMode: Text.WordWrap
                    FontLoader { id: tyre5_pressure_text_font; source: "Fonts/Roboto-Italic.ttf" }
                    font { family: tyre5_pressure_text_font.name; pixelSize: 24;}
                    font.letterSpacing: 1.0
                }



                Text {
                    id: id_tyre6_pressure
					text: id_mainmenu.right_menu_values_list[5] + id_mainmenu.param_menu_names[5][6]
                    color: tyre6_text_color
                    visible: true
                    wrapMode: Text.WordWrap
                    FontLoader { id: tyre6_pressure_font; source: "Fonts/Roboto-Italic.ttf" }
                    font { family: tyre6_pressure_font.name; pixelSize: 24;}
                    font.letterSpacing: 1.0
                }
            }
        }

        //3 Axle
        Rectangle{
            id: id_tire_data_3_axle_right
            x: 30
            y:108
            height: 321
            width : 1462
            clip: true
            color: "transparent"
            visible: {
                if(id_mainmenu.type_of_vehicle === "3")
                {
                    visible : true
                } else {
                    visible : false
                }
            }

            Image {
                id: id_tire_data_3_axle_right_bar
                x:87
                y:25
                height: sourceSize.height
                width: sourceSize.width
                source: "pics/Menu/Bus_layout_3__1_.png" // 3 Axles
                visible: true
            }

            Image {
                id: id_tyrepressure_3axel_tyre1_yellow
                anchors.right: parent.right
                anchors.rightMargin: 255
                y: 18
                height: sourceSize.height + 4
                width: sourceSize.width + 12
                source: {
					if((id_mainmenu.param_menu_names[pos0][pos1] === "yellow") || (id_mainmenu.param_menu_names[pos0][pos1] === "--")) {
                        tyre1_text_color = "yellow"
                        "pics/Menu/tire_menu_yellow.png"
					} else if (id_mainmenu.param_menu_names[pos0][pos1] === "red") {
                        tyre1_text_color = "red"
                        "pics/Menu/tire_menu_red.png"
                    } else {
                        tyre1_text_color = "white"
                        "" // Add a default source if none of the conditions match
                    }
                }
				visible: id_mainmenu.param_menu_names[pos0][pos1] === "yellow" ||
						 id_mainmenu.param_menu_names[pos0][pos1] === "--" ||
						 id_mainmenu.param_menu_names[pos0][pos1] === "red"
            }

            Text {
                id: id_tyre1_3axle_temperature
				text: id_mainmenu.param_menu_names[pos0][0]
                anchors.right: parent.right
                anchors.rightMargin: 170
                y: 30
                color: tyre1_text_color
                visible: true
                wrapMode: Text.WordWrap
                FontLoader { id: tyre1_text_3axle_font; source: "Fonts/Roboto-Italic.ttf" }
                font { family: tyre1_text_3axle_font.name; pixelSize: 24;}
                font.letterSpacing: 1.0
            }

            Image {
                id: id_tyrepressure_3axel_tyre2_yellow
                anchors.right: parent.right
                anchors.rightMargin: 255
                y: 210
                height: sourceSize.height + 5
                width: sourceSize.width + 12
                source: {
					if((id_mainmenu.param_menu_names[1][pos1] === "yellow") || (id_mainmenu.param_menu_names[1][pos1] === "--")) {
                        tyre2_text_color = "yellow"
                        "pics/Menu/tire_menu_yellow.png"
					} else if (id_mainmenu.param_menu_names[1][pos1] === "red") {
                        tyre2_text_color = "red"
                        "pics/Menu/tire_menu_red.png"
                    } else {
                        tyre2_text_color = "white"
                        "" // Add a default source if none of the conditions match
                    }
                }
				visible: id_mainmenu.param_menu_names[1][pos1] === "yellow" ||
						 id_mainmenu.param_menu_names[1][pos1] === "--" ||
						 id_mainmenu.param_menu_names[1][pos1] === "red"
            }

            Text {
                id: id_tyre2_3axle_temperature
				text: id_mainmenu.param_menu_names[1][0]
                anchors.right: parent.right
                anchors.rightMargin:170
                y: 220
                color: tyre2_text_color
                visible: true
                wrapMode: Text.WordWrap
                FontLoader { id: tyre2_3axle_text_font; source: "Fonts/Roboto-Italic.ttf" }
                font { family: tyre2_3axle_text_font.name; pixelSize: 24;}
                font.letterSpacing: 1.0
            }

            Image {
                id: id_tyrepressure_3axel_tyre3_yellow
                anchors.left: parent.left
                anchors.leftMargin: 640
                y: 20
                height: sourceSize.height + 4
                width: sourceSize.width  +12
                source: {
					if((id_mainmenu.param_menu_names[2][pos1] === "yellow") || (id_mainmenu.param_menu_names[2][pos1] === "--")) {
                        tyre3_text_color = "yellow"
                        "pics/Menu/tire_menu_yellow.png"
					} else if (id_mainmenu.param_menu_names[2][pos1] === "red") {
                        tyre3_text_color = "red"
                        "pics/Menu/tire_menu_red.png"
                    } else {
                        tyre3_text_color = "white"
                        "" // Add a default source if none of the conditions match
                    }
                }
				visible: id_mainmenu.param_menu_names[2][pos1] === "yellow" ||
						 id_mainmenu.param_menu_names[2][pos1] === "--" ||
						 id_mainmenu.param_menu_names[2][pos1] === "red"
            }


            Text {
                id: id_tyre3_3axle_temperature
				text: id_mainmenu.param_menu_names[2][0]
                anchors.left: parent.left
                anchors.leftMargin: 775
                y: 65
                color: tyre3_text_color
                visible:true
                wrapMode: Text.WordWrap
                FontLoader { id: tyre3_3axle_text_font; source: "Fonts/Roboto-Italic.ttf" }
                font { family: tyre3_3axle_text_font.name; pixelSize: 24;}
                font.letterSpacing: 1.0
            }

            Image {
                id: id_tyrepressure_3axel_tyre4_yellow
                anchors.left: parent.left
                anchors.leftMargin: 640
                y: 55
                height: sourceSize.height + 4
                width: sourceSize.width + 12
                source: {
					if((id_mainmenu.param_menu_names[3][pos1] === "yellow") || (id_mainmenu.param_menu_names[3][pos1] === "--")) {
                        tyre4_text_color = "yellow"
                        "pics/Menu/tire_menu_yellow.png"
					} else if (id_mainmenu.param_menu_names[pos0][pos1] === "red") {
                        tyre4_text_color = "red"
                        "pics/Menu/tire_menu_red.png"
                    } else {
                        tyre4_text_color = "white"
                        "" // Add a default source if none of the conditions match
                    }
                }
				visible: id_mainmenu.param_menu_names[3][pos1] === "yellow" ||
						 id_mainmenu.param_menu_names[3][pos1] === "--" ||
						 id_mainmenu.param_menu_names[3][pos1] === "red"
            }


            Text {
                id: id_tyre4_3axle_temperature
				text: id_mainmenu.param_menu_names[3][0]
                anchors.left: parent.left
                anchors.leftMargin: 775
                y: 35
                color: tyre4_text_color
                visible:true
                wrapMode: Text.WordWrap
                FontLoader { id: tyre4_3axle_text_font; source: "Fonts/Roboto-Italic.ttf" }
                font { family: tyre4_3axle_text_font.name; pixelSize: 24;}
                font.letterSpacing: 1.0
            }


            Image {
                id: id_tyrepressure_3axel_tyre5_yellow
                anchors.left: parent.left
                anchors.leftMargin: 640
                y: 172
                height: sourceSize.height +4
                width: sourceSize.width + 12
                source: {
					if((id_mainmenu.param_menu_names[4][pos1] === "yellow") || (id_mainmenu.param_menu_names[4][pos1] === "--")) {
                        tyre5_text_color = "yellow"
                        "pics/Menu/tire_menu_yellow.png"
					} else if (id_mainmenu.param_menu_names[4][pos1] === "red") {
                        tyre5_text_color = "red"
                        "pics/Menu/tire_menu_red.png"
                    } else {
                        tyre5_text_color = "white"
                        "" // Add a default source if none of the conditions match
                    }
                }
				visible: id_mainmenu.param_menu_names[4][pos1] === "yellow" ||
						 id_mainmenu.param_menu_names[4][pos1] === "--" ||
						 id_mainmenu.param_menu_names[4][pos1] === "red"
            }

            Text {
                id: id_tyre5_3axle_temperature
				text: id_mainmenu.param_menu_names[4][0]
                anchors.left: parent.left
                anchors.leftMargin: 775
                y: 185
                color:tyre5_text_color
                visible:true
                wrapMode: Text.WordWrap
                FontLoader { id: tyre5_3axle_text_font; source: "Fonts/Roboto-Italic.ttf" }
                font { family: tyre5_3axle_text_font.name; pixelSize: 24;}
                font.letterSpacing: 1.0
            }


            Image {
                id: id_tyrepressure_3axel_tyre6_yellow
                anchors.left: parent.left
                anchors.leftMargin: 640
                y: 210
                height: sourceSize.height + 4
                width: sourceSize.width + 12
                source: {
					if((id_mainmenu.param_menu_names[5][pos1] === "yellow") || (id_mainmenu.param_menu_names[5][pos1] === "--")){
                        tyre6_text_color = "yellow"
                        "pics/Menu/tire_menu_yellow.png"
					} else if (id_mainmenu.param_menu_names[5][pos1] === "red") {
                        tyre6_text_color = "red"
                        "pics/Menu/tire_menu_red.png"
                    } else {
                        tyre6_text_color = "white"
                        "" // Add a default source if none of the conditions match
                    }
                }
				visible: id_mainmenu.param_menu_names[5][pos1] === "yellow" ||
						 id_mainmenu.param_menu_names[5][pos1] === "--" ||
						 id_mainmenu.param_menu_names[5][pos1] === "red"
            }

            Text {
                id: id_tyre6_3axle_temperature
				text: id_mainmenu.param_menu_names[5][0]
                anchors.left: parent.left
                anchors.leftMargin: 775
                y: 210
                color: tyre6_text_color
                visible: true
                wrapMode: Text.WordWrap
                FontLoader { id: tyre6_3axle_temperature_font; source: "Fonts/Roboto-Italic.ttf" }
                font { family: tyre6_3axle_temperature_font.name; pixelSize: 24;}
                font.letterSpacing: 1.0
            }


            Image {
                id: id_tyrepressure_3axel_tyre7_yellow
                anchors.left: parent.left
                anchors.leftMargin: 250
                y: 20
                height: sourceSize.height + 4
                width: sourceSize.width +12
                source: {
					if((id_mainmenu.param_menu_names[6][pos1] === "yellow") || (id_mainmenu.param_menu_names[6][pos1] === "--")){
                        tyre7_text_color = "yellow"
                        "pics/Menu/tire_menu_yellow.png"
					} else if (id_mainmenu.param_menu_names[6][pos1] === "red") {
                        tyre7_text_color = "red"
                        "pics/Menu/tire_menu_red.png"
                    } else {
                        tyre7_text_color = "white"
                        "" // Add a default source if none of the conditions match
                    }
                }
				visible: id_mainmenu.param_menu_names[6][pos1] === "yellow" ||
						 id_mainmenu.param_menu_names[6][pos1] === "--" ||
						 id_mainmenu.param_menu_names[6][pos1] === "red"
            }

            Text {
                id: id_tyre7_3axle_temperature
				text: id_mainmenu.param_menu_names[6][0]
                anchors.left: parent.left
                anchors.leftMargin: 400
                y: 30
                color: tyre7_text_color
                visible:true
                wrapMode: Text.WordWrap
                FontLoader { id: tyre7_3axle_text_font; source: "Fonts/Roboto-Italic.ttf" }
                font { family: tyre7_3axle_text_font.name; pixelSize: 24;}
                font.letterSpacing: 1.0
            }

            Image {
                id: id_tyrepressure_3axel_tyre8_yellow
                anchors.left: parent.left
                anchors.leftMargin: 250
                y: 55
                height: sourceSize.height + 4
                width: sourceSize.width  +12
                source: {
					if((id_mainmenu.param_menu_names[7][pos1] === "yellow") || (id_mainmenu.param_menu_names[7][pos1] === "--")){
                        tyre8_text_color = "yellow"
                        "pics/Menu/tire_menu_yellow.png"
					} else if (id_mainmenu.param_menu_names[7][pos1] === "red") {
                        tyre8_text_color = "red"
                        "pics/Menu/tire_menu_red.png"
                    } else {
                        tyre8_text_color = "white"
                        "" // Add a default source if none of the conditions match
                    }
                }
				visible: id_mainmenu.param_menu_names[7][pos1] === "yellow" ||
						 id_mainmenu.param_menu_names[7][pos1] === "--" ||
						 id_mainmenu.param_menu_names[7][pos1] === "red"
            }

            Text {
                id: id_tyre8_3axle_temperature
				text: id_mainmenu.param_menu_names[7][0]
                anchors.left: parent.left
                anchors.leftMargin: 400
                y: 65
                color: tyre8_text_color
                visible:true
                wrapMode: Text.WordWrap
                FontLoader { id: tyre8_3axle_text_font; source: "Fonts/Roboto-Italic.ttf" }
                font { family: tyre8_3axle_text_font.name; pixelSize: 24;}
                font.letterSpacing: 1.0
            }

            Image {
                id: id_tyrepressure_3axel_tyre9_yellow
                anchors.left: parent.left
                anchors.leftMargin: 250
                y: 172
                height: sourceSize.height + 4
                width: sourceSize.width +12
                source: {
					if((id_mainmenu.param_menu_names[8][pos1] === "yellow") || (id_mainmenu.param_menu_names[8][pos1] === "--")){
                        tyre9_text_color = "yellow"
                        "pics/Menu/tire_menu_yellow.png"
					} else if (id_mainmenu.param_menu_names[8][pos1] === "red") {
                        tyre9_text_color = "red"
                        "pics/Menu/tire_menu_red.png"
                    } else {
                        tyre9_text_color = "white"
                        "" // Add a default source if none of the conditions match
                    }
                }
				visible: id_mainmenu.param_menu_names[8][pos1] === "yellow" ||
						 id_mainmenu.param_menu_names[8][pos1] === "--" ||
						 id_mainmenu.param_menu_names[8][pos1] === "red"
            }

            Text {
                id: id_tyre9_3axle_temperature
				text: id_mainmenu.param_menu_names[8][0]
                anchors.left: parent.left
                anchors.leftMargin: 400
                y: 185
                color: tyre9_text_color
                visible:true
                wrapMode: Text.WordWrap
                FontLoader { id: tyre9_3axle_text_font; source: "Fonts/Roboto-Italic.ttf" }
                font { family: tyre9_3axle_text_font.name; pixelSize: 24;}
                font.letterSpacing: 1.0
            }

            Image {
                id: id_tyrepressure_3axel_tyre10_yellow
                anchors.left: parent.left
                anchors.leftMargin: 250
                y: 210
                height: sourceSize.height + 4
                width: sourceSize.width +12
                source: {
					if((id_mainmenu.param_menu_names[9][pos1] === "yellow") || (id_mainmenu.param_menu_names[9][pos1] === "--")){
                        tyre10_text_color = "yellow"
                        "pics/Menu/tire_menu_yellow.png"
					} else if (id_mainmenu.param_menu_names[9][pos1] === "red") {
                        tyre10_text_color = "red"
                        "pics/Menu/tire_menu_red.png"
                    } else {
                        tyre10_text_color = "white"
                        "" // Add a default source if none of the conditions match
                    }
                }
				visible: id_mainmenu.param_menu_names[9][pos1] === "yellow" ||
						 id_mainmenu.param_menu_names[9][pos1] === "--" ||
						 id_mainmenu.param_menu_names[9][pos1] === "red"
            }

            Text {
                id: id_tyre10_3axle_temperature
				text: id_mainmenu.param_menu_names[9][0]
                anchors.left: parent.left
                anchors.leftMargin: 400
                y: 210
                color: tyre10_text_color
                visible: true
                wrapMode: Text.WordWrap
                FontLoader { id: tyre10_3axle_temperature_font; source: "Fonts/Roboto-Italic.ttf" }
                font { family: tyre10_3axle_temperature_font.name; pixelSize: 24;}
                font.letterSpacing: 1.0
            }

            //Pressure to be handled
            //Pressure
            Text {
                id: id_tyre1_3axle_pressure
				text: id_mainmenu.right_menu_values_list[0] + id_mainmenu.param_menu_names[pos0][6]
                anchors.right: parent.right
                anchors.rightMargin: 425
                y: 30
                color: tyre1_text_color
                visible: true
                wrapMode: Text.WordWrap
                FontLoader { id: tyre1_3axle_pressure_text_font; source: "Fonts/Roboto-Italic.ttf" }
                font { family: tyre1_3axle_pressure_text_font.name; pixelSize: 24;}
                font.letterSpacing: 1.0
            }
            Text {
                id: id_tyre2_3axle_pressure
				text: id_mainmenu.right_menu_values_list[1] + id_mainmenu.param_menu_names[1][6]
                anchors.right: parent.right
                anchors.rightMargin: 425
                y: 220
                color: tyre2_text_color
                visible: true
                wrapMode: Text.WordWrap
                FontLoader { id: tyre2_3axle_pressure_text_font; source: "Fonts/Roboto-Italic.ttf" }
                font { family: tyre2_3axle_pressure_text_font.name; pixelSize: 24;}
                font.letterSpacing: 1.0
            }

            ColumnLayout {
                anchors.left: parent.left
                anchors.leftMargin: 530
                y: 30
                Text {
                    id: id_tyre3_3axle_pressure
					text: id_mainmenu.right_menu_values_list[2] + id_mainmenu.param_menu_names[2][6]
                    color: tyre3_text_color
                    visible:true
                    wrapMode: Text.WordWrap
                    FontLoader { id: tyre3_3axle_pressure_text_font; source: "Fonts/Roboto-Italic.ttf" }
                    font { family: tyre3_3axle_text_font.name; pixelSize: 24;}
                    font.letterSpacing: 1.0
                }

                Text {
                    id: id_tyre4_3axle_pressure
					text: id_mainmenu.right_menu_values_list[3] + id_mainmenu.param_menu_names[3][6]
                    color: tyre4_text_color
                    visible:true
                    wrapMode: Text.WordWrap
                    FontLoader { id: tyre4_3axle_pressure_text_font; source: "Fonts/Roboto-Italic.ttf" }
                    font { family: tyre4_3axle_pressure_text_font.name; pixelSize: 24;}
                    font.letterSpacing: 1.0
                }
            }

            ColumnLayout {
                anchors.left: parent.left
                anchors.leftMargin: 530
                y: 185
                Text {
                    id: id_tyre5_3axle_pressure
					text: id_mainmenu.right_menu_values_list[4] + id_mainmenu.param_menu_names[4][6]
                    color:tyre5_text_color
                    visible:true
                    wrapMode: Text.WordWrap
                    FontLoader { id: tyre5_3axle_pressure_text_font; source: "Fonts/Roboto-Italic.ttf" }
                    font { family: tyre5_3axle_pressure_text_font.name; pixelSize: 24;}
                    font.letterSpacing: 1.0
                }

                Text {
                    id: id_tyre6_3axle_pressure
					text: id_mainmenu.right_menu_values_list[5] + id_mainmenu.param_menu_names[5][6]
                    color: tyre6_text_color
                    visible: true
                    wrapMode: Text.WordWrap
                    FontLoader { id: tyre6_3axle_pressure_font; source: "Fonts/Roboto-Italic.ttf" }
                    font { family: tyre6_pressure_font.name; pixelSize: 24;}
                    font.letterSpacing: 1.0
                }
            }

            ColumnLayout {
                anchors.left: parent.left
                anchors.leftMargin: 140
                y: 30
                Text {
                    id: id_tyre7_3axle_pressure
					text: id_mainmenu.right_menu_values_list[6] + id_mainmenu.param_menu_names[6][6]
                    color: tyre7_text_color
                    visible:true
                    wrapMode: Text.WordWrap
                    FontLoader { id: tyre7_3axle_pressure_text_font; source: "Fonts/Roboto-Italic.ttf" }
                    font { family: tyre7_3axle_text_font.name; pixelSize: 24;}
                    font.letterSpacing: 1.0
                }



                Text {
                    id: id_tyre8_3axle_pressure
					text: id_mainmenu.right_menu_values_list[7] + id_mainmenu.param_menu_names[7][6]
                    color: tyre8_text_color
                    visible:true
                    wrapMode: Text.WordWrap
                    FontLoader { id: tyre8_3axle_pressure_text_font; source: "Fonts/Roboto-Italic.ttf" }
                    font { family: tyre8_3axle_pressure_text_font.name; pixelSize: 24;}
                    font.letterSpacing: 1.0
                }
            }

            ColumnLayout {
                anchors.left: parent.left
                anchors.leftMargin: 140
                y: 185
                Text {
                    id: id_tyre9_3axle_pressure
					text: id_mainmenu.right_menu_values_list[8] + id_mainmenu.param_menu_names[8][6]
                    color: tyre9_text_color
                    visible:true
                    wrapMode: Text.WordWrap
                    FontLoader { id: tyre9_3axle_pressure_text_font; source: "Fonts/Roboto-Italic.ttf" }
                    font { family: tyre9_3axle_pressure_text_font.name; pixelSize: 24;}
                    font.letterSpacing: 1.0
                }

                Text {
                    id: id_tyre10_3axle_pressure
					text: id_mainmenu.right_menu_values_list[9] + id_mainmenu.param_menu_names[9][6]
                    color: tyre10_text_color
                    visible: true
                    wrapMode: Text.WordWrap
                    FontLoader { id: tyre10_3axle_pressure_font; source: "Fonts/Roboto-Italic.ttf" }
                    font { family: tyre10_3axle_pressure_font.name; pixelSize: 24;}
                    font.letterSpacing: 1.0
                }
            }
        }

        Rectangle {
            id: id_tyre_pressure_temp_right_footer
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
