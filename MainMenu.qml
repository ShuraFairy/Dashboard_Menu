import QtQuick 2.0
import QtQuick.Controls 2.12
import com.mettem.menuops 1.0


Item {
    id : id_menuconfig
    property string screen_name: "MAIN"
    property int i : 0
    property int k : 0
    property int l : 0
    property int m : 0
    property int b: 0
    property int rst_cnt: 0
    property bool settings_left_active: true
    property bool settings_right_active: false
    property bool services_left_active: true
    property bool services_right_active: false
    property int pneumatics_no_of_items :0
    property int pneumatics_auxiliary_pos : 0
    property bool pneumatics_inter_axle_visibility :false
    property bool pneumatics_rear_axle_2_visibility : false
    property bool pneumatics_rear_axle_3_visibility: false
    property bool is_back_pressed_menu : false
    property bool timer_bool: false
    property bool bool_reset:false
    property int timer_counter: 0
    property int max_failures_count: 0
    property int max_dtc_error_count: 0
    property bool services_popup_active: false
    property bool password_validity: false
    property bool menu_visibility : false
    property var password_data

    property int pos0: 0
    property int pos1: 1
    property int pos2: 2
    property int pos3: 3
    property int pos4: 4
    property int pos5: 5
    property int pos6: 6
    property int pos7: 7
    property int pos8: 8

	MainMenuWindow{
		id:id_main_menu_window
        z:15
		visible: false
    }

    MenuParameters{
        id:id_menu_parameters
        z:16
        visible: false
    }

    MenuServicesDialog{
        id: id_menu_services_dialog
        z:20
        visible: false
    }

    Qtmenuops {
        objectName: "obj_qtmenuops"
        id: id_mainmenu
    }

//    function handleDiagnosticsScreen(){

//        id_menuconfig.m++
//        if(id_menuconfig.m === 1){
//            id_menu_diagnostics.sub_menu_button_handler()
//            id_menu_diagnostics.submenu_diagnostics_data_handler()
//            id_menu_diagnostics.diagnosticsitems_handle_visibility()
//        }
//        if(id_menuconfig.m === 2){
//            id_menuconfig.m = 0
//        }
//        console.log("Control Coming here Automation")
//    }


	state: id_menuconfig.states[id_mainmenu.screen_state].name

//    function pneumatic_subitems_visibility_handler(){
//        id_menuconfig.l++
//        if(id_menuconfig.l === 1){
//            if(id_mainmenu.type_of_vehicle === "3"){
//                pneumatics_no_of_items = 3
//                pneumatics_auxiliary_pos = 4
//                pneumatics_inter_axle_visibility = true
//                pneumatics_rear_axle_2_visibility = false
//                pneumatics_rear_axle_3_visibility = true
//            } else {
//                pneumatics_no_of_items = 2
//                pneumatics_auxiliary_pos = 3
//                pneumatics_inter_axle_visibility = false
//                pneumatics_rear_axle_2_visibility = true
//                pneumatics_rear_axle_3_visibility = false
//            }
//        }
//        if(id_menuconfig.l === 2){
//            id_menuconfig.l = 0
//        }
//    }

    Image {
        id: id_menulayer
        x:33.5
        y:145
        z:14
        width: 1853
        height: 500
        source: "pics/Menu/Layer_1.png"
        visible: false
    }

    states: [
        State {
			name: "MAIN"
			PropertyChanges { target: id_main_menu_window; visible: false }
            PropertyChanges { target: id_menulayer; visible: false }
            PropertyChanges { target: id_menu_parameters; visible: false }
            PropertyChanges { target: id_menu_services_dialog; visible: false }
        },
        State {
			name: "MENU"
			PropertyChanges { target: id_main_menu_window; visible: true }
            PropertyChanges { target: id_menulayer; visible: true }
            PropertyChanges { target: id_menu_parameters; visible: false }
            PropertyChanges { target: id_menu_services_dialog; visible: false }
        },
        State {
            name: "PARAMETERS"
			PropertyChanges { target: id_main_menu_window; visible: false }
            PropertyChanges { target: id_menulayer; visible: true }
            PropertyChanges { target: id_menu_parameters; visible: true }
            PropertyChanges { target: id_menu_services_dialog; visible: false }
        },
        State {
            name: "DIAGNOSTICS"
			PropertyChanges { target: id_main_menu_window; visible: false }
            PropertyChanges { target: id_menulayer; visible: true }
			PropertyChanges { target: id_menu_parameters; visible: true }
            PropertyChanges { target: id_menu_services_dialog; visible: false }
        },
        State {
            name: "SETTINGS"
			PropertyChanges { target: id_main_menu_window; visible: false }
            PropertyChanges { target: id_menulayer; visible: true }
			PropertyChanges { target: id_menu_parameters; visible: true }
            PropertyChanges { target: id_menu_services_dialog; visible: false }
        },
        State {
			name: "PASSLOCK"
			PropertyChanges { target: id_main_menu_window; visible: true }
            PropertyChanges { target: id_menulayer; visible: true }
            PropertyChanges { target: id_menu_parameters; visible: false }
            PropertyChanges { target: id_menu_services_dialog; visible: true }
        },
        State {
            name: "SERVICES"
			PropertyChanges { target: id_main_menu_window; visible: false }
            PropertyChanges { target: id_menulayer; visible: true }
			PropertyChanges { target: id_menu_parameters; visible: true }
            PropertyChanges { target: id_menu_services_dialog; visible: false }
        }
    ]
}

