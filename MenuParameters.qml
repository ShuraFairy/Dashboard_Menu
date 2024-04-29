import QtQuick 2.0
import QtQuick.Layouts 1.12
import QtMultimedia 5.6
import QtGraphicalEffects 1.12
//import QtMobility.contacts 1.1


Item {
	property int enum_param: parseInt(id_mainmenu.param_menu_names[0][2])

	MenuParametersEngine
	{
        id: id_menu_parameters_engine
		visible: parent.enum_param < 5 || parent.enum_param === 14
    }

    MenuParametersTyrePressTemp{
        id : id_menu_parameters_tyre_press_temp
		visible: parent.enum_param === 6
    }

    MenuParametersBrakepads{
        id : id_menu_parameters_brake_pads
		visible: parent.enum_param === 5
    }

	MenuDiagnosticsDoorSensor{
		id : id_menu_diagnostics_door_sensor
		visible: parent.enum_param === 7
	}

	MenuDiagnosticsDoorValve{
		id: id_menu_diagnostics_door_valve
		visible: parent.enum_param === 8
	}

	MenuDiagnosticsEmergencyCrane{
		id: id_menu_diagnostics_emergency_crane
		visible: parent.enum_param === 9
	}

	MenuDiagnosticsEmergencyHammers{
		id: id_menu_diagnostics_emergency_hammers
		visible: parent.enum_param === 10
	}

	MenuDiagnosticsFireExtinguishers{
		id: id_menu_diagnostics_fire_extinguishers
		visible: parent.enum_param === 11
	}

	MenuDiagnosticsHeaters{
		id: id_menu_diagnostics_heaters
		visible: parent.enum_param === 12
	}

	MenuDiagnosticsHeatingSystemValves{
		id: id_menu_diagnostics_heating_system_valves
		visible: parent.enum_param === 13
	}




	Rectangle
	{
        id: id_subscreen
		Rectangle
		{
            id: id_parameters
            x: id_menulayer.x
            y: id_menulayer.y
            visible: true
			Rectangle
			{
                id: id_subitems_left
                height: 499
                width : 391
                clip: true
                visible: true
                color: "transparent"
				Image
				{
                    id: id_subitems
                    height: 499
                    width : sourceSize.width
                    visible: true
                    source: "pics/Menu/bar_background.png"
					Rectangle
					{
                        id: id_parameter_left
                        height: 428
                        width : 391
                        clip: true
                        color: "transparent"
						ListView
						{
                            id: id_listview_parameters
							anchors.fill: parent
							model: id_mainmenu.sub_menu_names
							snapMode: ListView.SnapOneItem
							smooth: false
							cacheBuffer: 782
							highlightFollowsCurrentItem: true
							currentIndex: id_mainmenu.list_menu_pos
							move: Transition {
								NumberAnimation{ properties: "x,y"; duration: 10}
							}
							highlightMoveDuration: 10
							highlightMoveVelocity: -1
							highlightResizeDuration: 10
							highlightResizeVelocity: -1
							delegate: Item
							{
								height:107
								width: id_parameter_left.width
								Text
								{
									anchors.left: parent.left
									anchors.leftMargin: 50
									anchors.verticalCenter: parent.verticalCenter
									color: "white"
									wrapMode: Text.WordWrap
									visible: true
									width: 320
									text: modelData
									FontLoader { id: engine_items_font; source: "Fonts/Roboto-Italic.ttf" }
									font { family: engine_items_font.name; pixelSize: 29;}
									verticalAlignment: Text.AlignTop // or Text.AlignBottom
									font.letterSpacing: 1.0
								}
								Image
								{
									id: id_engine_menu
									height:107
									width: 391
									source: "pics/Menu/bar.png"
									visible:index === id_mainmenu.list_menu_pos
								}
							}
							focus: true
						}
                    }
                    Rectangle {
                        id: id_parameter_left_footer
                        width: 391
                        height: 80
                        anchors.bottom: parent.bottom
                        color: "transparent"
                        Item {
                            anchors.centerIn: parent
                            width: parent.width
                            Image {
                                id: id_scroll_down
                                visible: true
                                height: sourceSize.height
                                width: sourceSize.width
                                anchors.centerIn: parent
                                anchors.horizontalCenterOffset: -20
                                source: "pics/Menu/Arrow_down.png"
                            }
                            Image {
                                id: id_scroll_up
                                visible: true
                                height: sourceSize.height
                                width: sourceSize.width
                                anchors.centerIn: parent
                                anchors.horizontalCenterOffset: 20
                                source: "pics/Menu/Arrow_up.png"
                            }

                            Flow {
                                anchors.centerIn: parent
                                anchors.horizontalCenterOffset: 120
                                Text {
									text: id_mainmenu.list_menu_pos + 1
                                    color: "#21B1D0"
                                    wrapMode: Text.WordWrap
                                    FontLoader { id: parameter_selector_font; source: "Fonts/Roboto-Italic.ttf" }
                                    font { family: parameter_selector_font.name; pixelSize: 25;}
                                    font.letterSpacing: 1.0
                                }
                                Text {
                                    color: "#21B1D0"
                                    text: "/"
                                    FontLoader { id: seperator_font; source: "Fonts/Roboto-Italic.ttf" }
                                    font { family: seperator_font.name; pixelSize: 25;}
                                    font.letterSpacing: 1.0
                                }
                                Text {
									text: id_mainmenu.sub_menu_names.length
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
        }
    }
}



