import QtQuick 2.0
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.12

Item {
    id:id_menu_parameters_engine
	visible: true

    Rectangle{
        id: id_engineitems_right_whole
        height: 500
        width : 1462
        x: id_subitems_left.x + 391
        y: id_menulayer.y
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

		Rectangle
		{
            id: id_engineitems_right
            height: 321
            width : 1462
            x:350.5
            y:100
            anchors.horizontalCenter: parent.horizontalCenter
            clip: true
            color: "transparent"
			ListView
			{
				anchors.fill: parent
				model: id_mainmenu.param_menu_names
				snapMode: ListView.SnapOneItem
				smooth: false
				cacheBuffer: 642 //6 items
				highlightFollowsCurrentItem: true
				currentIndex: id_mainmenu.param_menu_pos
				move: Transition {
					NumberAnimation{ properties: "x,y"; duration: 10}
				}
				highlightMoveDuration: 10
				highlightMoveVelocity: -1
				highlightResizeDuration: 10
				highlightResizeVelocity: -1

				delegate: Item
				{
					width: 1462
					height: 107
					anchors.horizontalCenter: if(modelData[2] === "3")
												anchors.horizontalCenter = parent.horizontalCenter
					Image
					{
						anchors.centerIn: parent
						y:parent.y + 40
						height: sourceSize.height
						width: sourceSize.width
						source:"pics/Menu/Illumination.png"
						visible:index === id_mainmenu.param_menu_pos && (id_mainmenu.screen_state === 3 || id_mainmenu.screen_state === 4)
					}
					Column
					{
						spacing: 5
						anchors.centerIn: parent
						visible: id_mainmenu.screen_state === 4
						Text {
							id: id_fire_extinguisher_system_error_code_1_text
							anchors.horizontalCenter: parent.horizontalCenter
							text: modelData[0]
							color: "white"
							visible: parent.visible
							FontLoader { id: fire_extinguisher_system_error_code_1_text_right_font; source: "Fonts/Roboto-Italic.ttf" }
							font { family: fire_extinguisher_system_error_code_1_text_right_font.name; pixelSize: 19;}
							font.letterSpacing: 1.0
						}
						Text {
							id: id_fire_extinguisher_system_error_code_1_description
							anchors.horizontalCenter: parent.horizontalCenter
							text: modelData[1]
							color: "white"
							visible: parent.visible
							FontLoader { id: fire_extinguisher_system_error_code_1_description_right_font; source: "Fonts/Roboto-Italic.ttf" }
							font { family: fire_extinguisher_system_error_code_1_description_right_font.name; pixelSize: 19;}
							font.letterSpacing: 1.0
						}
						Text {
							id: id_fire_extinguisher_system_error_code_1_recommendation
							anchors.horizontalCenter: parent.horizontalCenter
							text: modelData[3]
							color: "white"
							visible: parent.visible
							FontLoader { id: fire_extinguisher_system_error_code_1_recommendation_right_font; source: "Fonts/Roboto-Italic.ttf" }
							font { family: fire_extinguisher_system_error_code_1_recommendation_right_font.name; pixelSize: 19;}
							font.letterSpacing: 1.0
						}
						Text {
							id: id_fire_extinguisher_system_error_code_1_repetations
							anchors.horizontalCenter: parent.horizontalCenter
							text: modelData[4]
							color: "white"
							visible: parent.visible
							FontLoader { id: fire_extinguisher_system_error_code_1_repetations_right_font; source: "Fonts/Roboto-Italic.ttf" }
							font { family: fire_extinguisher_system_error_code_1_repetations_right_font.name; pixelSize: 19;}
							font.letterSpacing: 1.0
						}
					}
					Rectangle
					{
						height: parent.height
						width : if(modelData[2] !== "3")
									400
								else
									parent.width
						color: "transparent"
						visible: id_mainmenu.screen_state !== 4
						Text {
							text: modelData[0]
							width: if(modelData[2] !== "3")
									{
										anchors.left = parent.left
										anchors.leftMargin = 85
										wrapMode = Text.WordWrap
										anchors.verticalCenter = parent.verticalCenter
										verticalAlignment = Text.AlignTop
										width = parent.width
									}
									else
								   {
										horizontalAlignment = Text.AlignHCenter
										anchors.centerIn = parent
										width = parent.width
								   }
							color: "white"
							visible: parent.visible
							FontLoader { id: coolanttemp_text_font; source: "Fonts/Roboto-Italic.ttf" }
							font { family: coolanttemp_text_font.name; pixelSize: 29;}
							//verticalAlignment: Text.AlignTop // or Text.AlignBottom
							font.letterSpacing: 1.0
						}
					}
					Rectangle
					{
						visible: id_mainmenu.screen_state !== 4
						Image
						{
							x: parent.x + 478
							y: parent.y + 30
							visible: modelData[1] !== "" && modelData[2] !== "14"
							source: modelData[1]
						}
						Rectangle
						{
							visible: modelData[2] === "1"
							Image
							{
								id: id_progressbar_rect_engine
								Text
								{
									id: id_temp
									visible: false
									text: parseInt(id_mainmenu.right_menu_values_list[index])
								}
								x:542
								y:parent.y + 46
								width: 368
								height: 13
								source: "pics/Menu/Small_illumination.png"
								Image {
									id: cliprect
									anchors.bottom: parent.bottom
									anchors.top: parent.top
									anchors.left: parent.left
									width: {
										if(id_mainmenu.right_menu_values_list[index] === "--" || parseInt(id_temp.text) <= parseInt(modelData[3])){
											width: 0
										} else if (parseInt(id_temp.text) < parseInt(modelData[4])){
											width: parent.width * ((parseInt(id_temp.text) - parseInt(modelData[3]))
																   / (parseInt(modelData[4]) - parseInt(modelData[3])))
										} else if (parseInt(id_temp.text) >= parseInt(modelData[4])){
											width: parent.width
										}
									}
									height: sourceSize.height
									source: "pics/Menu/Runner_line.png"
									Image {
										id: id_runner_bluedot_coolant_temp
										visible: true
										x: cliprect.width - 3
										height: sourceSize.height
										y:parent.y + 1.5
										source: "pics/Menu/Runner_bluebot.png"
									}
								}
							}
							Text {
								id: id_enginedata_minvalue
								x:543
								y:parent.y + 71
								text: modelData[3]
								color: "#21B1D0"
								visible: parent.visible
								FontLoader { id: enginedata_text_min_font; source: "Fonts/Roboto-Italic.ttf" }
								font { family: enginedata_text_min_font.name; pixelSize: 21;}
								font.letterSpacing: 1.0
							}
							Text {
								id: id_enginedata_midvalue
								x: 543 + id_progressbar_rect_engine.width * (parseInt(modelData[5]) - parseInt(modelData[3]))
								   / (parseInt(modelData[4]) - parseInt(modelData[3]))
								y: parent.y + 71
								text: modelData[5]
								color: "#21B1D0"
								visible: modelData[5] !== ""
								FontLoader { id: enginedata_text_mid_font; source: "Fonts/Roboto-Italic.ttf" }
								font { family: enginedata_text_mid_font.name; pixelSize: 21;}
								font.letterSpacing: 1.0
							}
							Text {
								id: id_enginedata_maxvalue
								x:888
								y:parent.y + 71
								text: modelData[4]
								color: "#21B1D0"
								visible: parent.visible
								FontLoader { id: enginedata_text_max_font; source: "Fonts/Roboto-Italic.ttf" }
								font { family: enginedata_text_max_font.name; pixelSize: 21;}
								font.letterSpacing: 1.0
							}
						}
						Text
						{
							id: id_enginedata_value
							x:	if (modelData[2] === "1")
									x:935
								else
									x:731
							y:parent.y + 30
							text: id_mainmenu.right_menu_values_list[index] + modelData[6]
							color: "white"
							visible: modelData[2] !== "3" && modelData[2] !== "14"
							FontLoader { id: enginedata_text_right_font; source: "Fonts/Roboto-Italic.ttf" }
							font { family: enginedata_text_right_font.name; pixelSize: 30;}
							font.letterSpacing: 1.0
						}
						Image {
							x: parent.x + 731
							y:parent.y + 30
							visible: parent.visible && modelData[2] === "14"
							source: modelData[1]

							ColorOverlay{
								anchors.fill: parent
								source: parent
								color: modelData[6]
							}
						}
					}
				}
			}

		}

        Rectangle {
            id: id_parameter_right_footer
            width: 1200
            height: 80
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            color: "transparent"
            Item {
                anchors.centerIn: parent
                width: parent.width
				Image
				{
                    height: sourceSize.height
                    width: sourceSize.width
                    anchors.centerIn: parent
                    anchors.horizontalCenterOffset: -20
                    source: "pics/Menu/Arrow_down.png"
                }
				Image
				{
                    height: sourceSize.height
                    width: sourceSize.width
                    anchors.centerIn: parent
                    anchors.horizontalCenterOffset: 20
                    source: "pics/Menu/Arrow_up.png"
                }

                Flow {
                    anchors.centerIn: parent
                    anchors.horizontalCenterOffset: 700
                    Text {
                        text: {
							if(id_mainmenu.screen_state === 3 || id_mainmenu.screen_state === 4){
								text: id_mainmenu.param_menu_pos + 1
                            }else{
								text: "0"
                            }
                        }
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
						text: id_mainmenu.param_menu_names.length
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
}
