import QtQuick 2.4
import QtQuick.Layouts 1.12
import QtMultimedia 5.6
import QtGraphicalEffects 1.12



Item
{
	property int y_button_default: 258
	property int y_button_selected: 149
	property int margin_bottom_default: 50
	property int margin_bottom_selected: 159
	property string button_default: "pics/Menu/Button_off.png"
	property string button_selected: "pics/Menu/Button_on.png"
	property real y_image_default: 66
	property real y_image_selected: 175.4

	Image
	{
		x:33.5
		y:145
		width: 1853
		height: 500
		source: "pics/Menu/Layer_1.png"
		visible: parent.visible
	}

    /* Adding Buttons */
    /* Parameters */
	Image
	{
		visible:parent.visible
		x: 352
		source:{
			if(id_mainmenu.main_menu_pos  === 0){
				y = y_button_selected
				source: button_selected;
			}else{
				y = y_button_default
				source:button_default
            }
        }
		Item
		{
            width: parent.width
            height: parent.height
			Image
			{
                x:90.5
				visible: parent.visible
                width: 97
                height: 97
                source:{
					if(id_mainmenu.main_menu_pos === 0){
						y = y_image_selected
                        source : "pics/Menu/Parameters_white.png"
					}else{
						y = y_image_default
                        source : "pics/Menu/Parameters.png"
                    }
                }
            }
			Text
			{
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottom: parent.bottom
				anchors.bottomMargin: if(id_mainmenu.main_menu_pos === 0)
										  margin_bottom_selected
									  else
										  margin_bottom_default
                y:100
                color: "white"
                width: 274
				visible: parent.visible
				text:  /*qsTr("Parameters")*/id_mainmenu.main_menu_names[0]
				FontLoader { id: parameter_font; source: "Fonts/Roboto-Italic.ttf" }
				font { family: parameter_font.name; pixelSize: 28; }
                horizontalAlignment: Text.AlignHCenter
                font.letterSpacing: 1.0
            }
        }
    }

    /* Diagnostics */
	Image
	{
		visible:parent.visible
		x: 666
        source: {
			if(id_mainmenu.main_menu_pos  === 1){
				y = y_button_selected
				source: button_selected
            } else {
				y = y_button_default
				source: button_default
            }
        }

		Item
		{
            width: parent.width
            height: parent.height

			Image
			{
                x:90.5
				visible: parent.visible
                source:{
					if(id_mainmenu.main_menu_pos === 1){
						y = y_image_selected
                        source : "pics/Menu/Diagnostics_white.png"
                    } else {
						y = y_image_default
                        source : "pics/Menu/Diagnostics.png"
                    }
                }
            }
            Text {
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottom: parent.bottom
                anchors.bottomMargin: {
					if(id_mainmenu.main_menu_pos === 1)
						margin_bottom_selected
					else
						margin_bottom_default
                }
                y:100
                color: "white"
                width: 274
				visible: parent.visible
				text:  /*"Diagnostics"*/id_mainmenu.main_menu_names[1]
				FontLoader { id: diagnostics_font; source: "Fonts/Roboto-Italic.ttf" }
				font { family: diagnostics_font.name; pixelSize: 28; }
				horizontalAlignment: Text.AlignHCenter
                font.letterSpacing: 1.0
            }
        }
    }


    /* Settings */
	Image {
		visible:parent.visible
        x:980
        source: {
			if(id_mainmenu.main_menu_pos === 2){
				y = y_button_selected
				source: button_selected
            } else {
				y = y_button_default
				source : button_default
            }
        }

		Item {
            width: parent.width
            height: parent.height

			Image {
                x:90.5
				visible: parent.visible
                source:{
					if(id_mainmenu.main_menu_pos === 2){
						y = y_image_selected
                        source : "pics/Menu/Settings_white.png"
					} else {
						y = y_image_default
                        source : "pics/Menu/Settings.png"
                    }
                }
            }
			Text {
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottom: parent.bottom
                anchors.bottomMargin: {
					if(id_mainmenu.main_menu_pos === 2){
						margin_bottom_selected
					} else {
						margin_bottom_default
					}
                }
                y:100
                color: "white"
                width: 274
				visible: parent.visible
				text:  /*"Settings"*/id_mainmenu.main_menu_names[2]
				FontLoader { id: settings_font; source: "Fonts/Roboto-Italic.ttf" }
				font { family: settings_font.name; pixelSize: 28; }
				horizontalAlignment: Text.AlignHCenter
                font.letterSpacing: 1.0
            }
        }
    }

    /* Services */
	Image {
		visible: parent.visible
        x: 1294
        source: {
			if (id_mainmenu.main_menu_pos === 3) {
				y = y_button_selected
				source: button_selected
            } else {
				y = y_button_default
				source: button_default
            }
        }

		Item {
            width: parent.width
            height: parent.height

			Image {
                x:90.5
				visible: parent.visible
                source: {
					if (id_mainmenu.main_menu_pos === 3) {
						y = y_image_selected
                        source: "pics/Menu/Service_white.png"
					} else {
						y = y_image_default
                        source: "pics/Menu/Service.png"
                    }
                }
            }

			Text {
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottom: parent.bottom
                anchors.bottomMargin: {
					if(id_mainmenu.main_menu_pos === 3){
						margin_bottom_selected
					} else {
						margin_bottom_default
					}
                }
                color: "white"
                width: 274
				visible: parent.visible
				text: /*"Services"*/id_mainmenu.main_menu_names[3]
				FontLoader { id: services_font; source: "Fonts/Roboto-Italic.ttf" }
				font { family: services_font.name; pixelSize: 28; }
				horizontalAlignment: Text.AlignHCenter
                font.letterSpacing: 1.0
            }
        }
    }
}

