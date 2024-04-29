import QtQuick 2.4
import QtQuick.Window 2.1
import QtQuick.Layouts 1.12
//import datacontract.namespace 1.0

Window {

    id:id_dashboard_screen
    visibility:  "FullScreen" /* Use visibility "Windowed" to check in PC .. "FullScreen" for device*/
    property bool  gear_visibility: true
    visible: true
    color: "#000000"


    Loader{
        id: id_animation_loader
        width:id_dashboard_root.width
        height: id_dashboard_root.height
        asynchronous: true
        visible: false
        active: id_animation_image
        sourceComponent: componentToLoad
    }

    Component{
        id:componentToLoad
        Image{
            id: id_animation_image
            anchors.fill: parent
            visible: {
                if(commandLineArgument === "-skip-animation"){
                    visible = false
                    id_welcome_animation.running = false
                    id_dashboard_resources_loader.active = true
                    id_dashboard_resources_loader.visible = true
                    visible: false
                    obj_speedometer.qml_responses(2)
                    obj_enginemeter.qml_responses(2)
                    obj_airpressure1.qml_responses(2)
                    obj_airpressure2.qml_responses(2)
                    obj_telltale.qml_responses(2)
                    obj_menuops.qml_responses(2)
                    obj_centraldashboard.qml_responses(2)
                } else{
                   visible: false
                    return id_animation_loader.status != id_animation_loader.Ready
                }
            }
            source: "pics/IC12_interface_graphics/welcome_screen1.png"
            z:0
            property int currentimage: 1
            NumberAnimation on currentimage {
                id: id_welcome_animation
                from: 1
                to: 1
                duration: 1
                onRunningChanged: {
                    if(!id_welcome_animation.running){
                        console.log("Animation completed")
                        id_dashboard_resources_loader.active = true
                        id_dashboard_resources_loader.visible = true
                        id_animation_image.visible = false
                        obj_speedometer.qml_responses(1)
                        obj_enginemeter.qml_responses(1)
                        obj_airpressure1.qml_responses(1)
                        obj_airpressure2.qml_responses(1)
                        obj_telltale.qml_responses(1)
                        obj_menuops.qml_responses(1)
                        obj_centraldashboard.qml_responses(1)
                        console.log("Enum list :", DataContractIds.DATA_SPEEDOMETER_NEEDLE_ID)
                    }
                    else{

                    }
                }
                running: true
            }
        }
    }
    Loader{
        id: id_dashboard_resources_loader
        width:id_dashboard_root.width
        height: id_dashboard_root.height
        x:0
        y:0
        active:false
        visible: false
        Image {
            id: id_layer_1
            x:0
            y:0
            z: 0
            height: id_dashboard_root.height
            width: id_dashboard_root.width
            source: "pics/IC12_interface_graphics/iC12_layer_1.png"
        }


        Image {
            id: id_layer2
            x: 0
            y: 0
            z: 1
            width: id_dashboard_root.width
            height: id_dashboard_root.height
			visible: id_main_menu_ops.state === "MAIN"
            source: "pics/IC12_interface_graphics/iC12_layer_2.png"

        }


        Speedometers{
            id: id_speedometer
			visible: id_main_menu_ops.state ===  "MAIN"
            z:6
        }

        Enginespeed{
            id: id_enginemeter
			visible: id_main_menu_ops.state === "MAIN"
			z:6
        }

        Airpressure1{
            id: id_airpressure1
			visible: id_main_menu_ops.state=== "MAIN"
			z:6

        }

        Airpressure2{
            id: id_airpressure2
			visible:id_main_menu_ops.state === "MAIN"
			z:6
        }

        Centraldashboard{
            id: id_central_dashboard
            z:10
        }

        Telltales {
            id: id_telltales
            z:11
        }

		MainMenu{
            id: id_main_menu_ops
			z:12

        }

        PopUpWindow{
            id: id_pop_up_window
            z:13
        }

    }

}
