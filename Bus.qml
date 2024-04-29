import QtQuick 2.9
import QtQuick.Layouts 1.12
import com.mettem.telltales 1.0
import QtMultimedia 5.6
import QtGraphicalEffects 1.12


Item {
    property int  leftdoorfrompos
    property int  leftdoortopos
    property int  rightdoorfrompos
    property int  rightdoortopos

    property int  leftdoor2frompos
    property int  leftdoor2topos
    property int  rightdoor2frompos
    property int  rightdoor2topos

    property int  leftdoor3frompos
    property int  leftdoor3topos
    property int  rightdoor3frompos
    property int  rightdoor3topos

    property int  leftdoor4frompos
    property int  leftdoor4topos
    property int  rightdoor4frompos
    property int  rightdoor4topos

    property int  leftdoor_duration
    property bool leftdoor_running: false
    property int  rightdoor_duration
    property bool rightdoor_running: false
    property string prevStatusLeftDoor1: ""
    property string prevStatusRightDoor1: ""
    property string prevStatusLeftDoor2: ""
    property string prevStatusRightDoor2: ""
    property string prevStatusLeftDoor3: ""
    property string prevStatusRightDoor3: ""
    property string prevStatusLeftDoor4: ""
    property string prevStatusRightDoor4: ""

    readonly property int xValDoor1LeftMax : 1187 - 10
    readonly property int xValDoor1LeftMin : 1157 - 10
    readonly property int xValDoor1RightMax : 1247 - 10
    readonly property int xValDoor1RightMin : 1217 - 10
    readonly property int xValDoor1Error: 1172 - 10
    readonly property int xValDoor2LeftMax : 951 - 10
    readonly property int xValDoor2LeftMin : 921 - 10
    readonly property int xValDoor2RightMax : 1011 -10
    readonly property int xValDoor2RightMin : 981 - 10
    readonly property int xValDoor2Error: 936 - 10
    readonly property int xValDoor3LeftMax : 717 - 10
    readonly property int xValDoor3LeftMin : 687 - 10
    readonly property int xValDoor3RightMax : 777 - 10
    readonly property int xValDoor3RightMin : 747 - 10
    readonly property int xValDoor3Error: 702 - 10

    readonly property string bus_three_axles: "3"
    readonly property string bus_two_axles: "2"


    /*************************** Bus **********************/
        Image {
            id:id_bus
            x:(obj_menuops.type_of_vehicle === bus_three_axles) ? 620:635
            y:(obj_menuops.type_of_vehicle === bus_three_axles) ? 441:408
            visible: true
            source: obj_menuops.type_of_vehicle === bus_three_axles ?
                        "/pics/IC12_interface_graphics/buses/bus_with_four_doors/bus_articulated_without_doors.png":
                        "pics/IC12_interface_graphics/buses/bus_with_three_doors/iC12_bus_without_doors.png"
        }

                /******************************Door 1 Changes*************************************************/
                Rectangle{
                        Image {
                            id: id_door1_static
                            visible:id_telltales.bus_door1[0][3] === "STATIC"
                            x:{
                                if(id_telltales.bus_door1[0][3] === "STATIC" &&
                                        (id_telltales.bus_door1[0][2] === "CLOSED" || id_telltales.bus_door1[0][2] === "REQUEST"))
                                {
                                    x : (obj_menuops.type_of_vehicle === bus_three_axles) ? 1217 : xValDoor1LeftMax
                                }
                                else
                                {
                                    if(id_telltales.bus_door1[0][3] === "STATIC"  &&
                                            (id_telltales.bus_door1[0][2] === "ERROR" || id_telltales.bus_door1[0][2] === "OBSTACLE_DETECT")){
                                    x : (obj_menuops.type_of_vehicle === bus_three_axles) ? 1200: xValDoor1Error
                                    }
                                }
                            }
                            y: (obj_menuops.type_of_vehicle === bus_three_axles) ? id_bus.y + 20 :id_bus.y + 25
                            source: (obj_menuops.type_of_vehicle === bus_three_axles) ? "/pics/IC12_interface_graphics/buses/bus_with_four_doors"+id_telltales.bus_door1[0][0]:
                                        "/pics/IC12_interface_graphics/buses/bus_with_three_doors"+id_telltales.bus_door1[0][0]

                        }
                    }

                function leftDoor1Changes() {

                    if(prevStatusLeftDoor1 !== id_telltales.bus_door1[0][2])
                    {


                        if(id_telltales.bus_door1[0][2] === "OPENED" && id_telltales.bus_door1[0][3] === "DYNAMIC"){
                            leftdoorfrompos =  obj_menuops.type_of_vehicle === bus_three_axles ? 1198 : xValDoor1LeftMin
                            leftdoortopos   = leftdoorfrompos
                            leftdoor_duration = 1
                            leftdoor_running = true
                            leftAnimImg.start()
                        } else if (id_telltales.bus_door1[0][2] === "OPENING" && id_telltales.bus_door1[0][3] === "DYNAMIC"){
                            leftdoorfrompos = obj_menuops.type_of_vehicle === bus_three_axles ? 1217 : xValDoor1LeftMax
                            leftdoortopos   = obj_menuops.type_of_vehicle === bus_three_axles ? 1198 : xValDoor1LeftMin
                            leftdoor_duration = 2000
                            leftdoor_running = true
                            leftAnimImg.start()

                        }  else if (id_telltales.bus_door1[0][2] === "CLOSING" && id_telltales.bus_door1[0][3] === "DYNAMIC"){
                            leftdoorfrompos = obj_menuops.type_of_vehicle === bus_three_axles ? 1198 : xValDoor1LeftMin
                            leftdoortopos   = obj_menuops.type_of_vehicle === bus_three_axles ? 1217 : xValDoor1LeftMax
                            leftdoor_duration = 2000
                            leftdoor_running = true
                            leftAnimImg.start()
                        } else{
                            //do Nothing
                        }
                        prevStatusLeftDoor1 = id_telltales.bus_door1[0][2];
                    }
                }

                Image {
                    id: id_door1_left_dynamic
                    visible:id_telltales.bus_door1[0][3] === "DYNAMIC"
                    x: (obj_menuops.type_of_vehicle === bus_three_axles) ? 1217 : 1187
                    y: (obj_menuops.type_of_vehicle === bus_three_axles) ? id_bus.y + 20 :id_bus.y + 25
                    source: (obj_menuops.type_of_vehicle === bus_three_axles) ?
                                "/pics/IC12_interface_graphics/buses/bus_with_four_doors"+id_telltales.bus_door1[0][0]:
                                "/pics/IC12_interface_graphics/buses/bus_with_three_doors"+id_telltales.bus_door1[0][0]
                    NumberAnimation on x {
                        id:leftAnimImg
                        from:leftdoorfrompos
                        to:leftdoortopos
                        duration: leftdoor_duration
                        running: true
                    }
                }

                function rightDoor1Changes() {
                    if (prevStatusRightDoor1 !== id_telltales.bus_door1[0][2])
                    {
                        if(id_telltales.bus_door1[0][2] === "OPENED" && id_telltales.bus_door1[0][3] === "DYNAMIC")
                        {
                            rightdoorfrompos = (obj_menuops.type_of_vehicle === bus_three_axles) ? 1258 : xValDoor1RightMax
                            rightdoortopos   = rightdoorfrompos
                            rightdoor_duration = 1
                            rightdoor_running = true
                            rightAnimimg.start()

                        } else if (id_telltales.bus_door1[0][2] === "OPENING" && id_telltales.bus_door1[0][3] === "DYNAMIC"){
                            rightdoorfrompos = obj_menuops.type_of_vehicle === bus_three_axles ? 1239 : xValDoor1RightMin
                            rightdoortopos   = obj_menuops.type_of_vehicle === bus_three_axles ? 1258 : xValDoor1RightMax
                            rightdoor_duration = 2000
                            rightdoor_running = true
                            rightAnimimg.start()
                        }
                        else if (id_telltales.bus_door1[0][2] === "CLOSING" && id_telltales.bus_door1[0][3] === "DYNAMIC"){
                            rightdoorfrompos = obj_menuops.type_of_vehicle === bus_three_axles ? 1258 : xValDoor1RightMax
                            rightdoortopos   = obj_menuops.type_of_vehicle === bus_three_axles ? 1239 : xValDoor1RightMin
                            rightdoor_duration = 2000
                            rightdoor_running = true
                            rightAnimimg.start()
                        }
                        else{
                            //Do Nothing
                        }
                        prevStatusRightDoor1 = id_telltales.bus_door1[0][2]
                    }
                }


                Rectangle{
                    Image {
                        id: id_door1_right_dynamic
                        visible:id_telltales.bus_door1[0][3] === "DYNAMIC"
                        x: (obj_menuops.type_of_vehicle === bus_three_axles) ? 1239 :1217
                        y: (obj_menuops.type_of_vehicle === bus_three_axles) ? id_bus.y + 20 :id_bus.y + 25
                        source: (obj_menuops.type_of_vehicle === bus_three_axles) ?
                                    "/pics/IC12_interface_graphics/buses/bus_with_four_doors"+id_telltales.bus_door1[0][1]:
                                    "/pics/IC12_interface_graphics/buses/bus_with_three_doors"+id_telltales.bus_door1[0][1]
                        NumberAnimation on x {
                            id:rightAnimimg
                            from: rightdoorfrompos
                            to:rightdoortopos
                            duration: rightdoor_duration
                            running: true
                        }
                    }
                }

                /******************************Door 2 Changes*************************************************/

                Rectangle{
                    Image {
                        id: id_door2_static
                        visible:id_telltales.bus_door2[0][3] === "STATIC"
                        x:{
                            if(id_telltales.bus_door2[0][3] === "STATIC" &&
                                    (id_telltales.bus_door2[0][2] === "CLOSED" || id_telltales.bus_door2[0][2] === "REQUEST"))
                            {
                                x :obj_menuops.type_of_vehicle === bus_three_axles ? 1071 : xValDoor2LeftMax
                            }
                            else
                            {
                                if(id_telltales.bus_door2[0][3] === "STATIC"  &&
                                        (id_telltales.bus_door2[0][2] === "ERROR" || id_telltales.bus_door2[0][2] === "OBSTACLE_DETECT")){
                                    x : (obj_menuops.type_of_vehicle === bus_three_axles) ? 1054 : xValDoor2Error
                                }
                            }
                        }
                        y: (obj_menuops.type_of_vehicle === bus_three_axles) ? id_bus.y + 20 :id_bus.y + 25
                        source: (obj_menuops.type_of_vehicle === bus_three_axles) ? "/pics/IC12_interface_graphics/buses/bus_with_four_doors"+id_telltales.bus_door2[0][0]:
                                    "/pics/IC12_interface_graphics/buses/bus_with_three_doors"+id_telltales.bus_door2[0][0]
                    }
                }


                function leftDoor2Changes() {
                    leftdoor2frompos = 0
                    leftdoor2topos   = 0
                    if(prevStatusLeftDoor2 !== id_telltales.bus_door2[0][2])
                    {
                        if(id_telltales.bus_door2[0][2] === "OPENED" && id_telltales.bus_door2[0][3] === "DYNAMIC"){
                            leftdoor2frompos =  obj_menuops.type_of_vehicle === bus_three_axles ? 1052 : xValDoor2LeftMin
                            leftdoor2topos   = leftdoor2frompos
                            leftdoor_duration = 1
                            leftdoor_running = true
                            leftAnimImg2.start()
                        }
                        else if (id_telltales.bus_door2[0][2] === "OPENING" && id_telltales.bus_door2[0][3] === "DYNAMIC"){
                            leftdoor2frompos = obj_menuops.type_of_vehicle === bus_three_axles ? 1071 : xValDoor2LeftMax
                            leftdoor2topos   = obj_menuops.type_of_vehicle === bus_three_axles ? 1052 : xValDoor2LeftMin
                            leftdoor_duration = 2000
                            leftdoor_running = true
                            leftAnimImg2.start()
                        }  else if (id_telltales.bus_door2[0][2] === "CLOSING" && id_telltales.bus_door2[0][3] === "DYNAMIC"){
                            leftdoor2frompos = obj_menuops.type_of_vehicle === bus_three_axles ? 1052 : xValDoor2LeftMin
                            leftdoor2topos   = obj_menuops.type_of_vehicle === bus_three_axles ? 1071 : xValDoor2LeftMax
                            leftdoor_duration = 2000
                            leftdoor_running = true
                            leftAnimImg2.start()
                        } else{
                            //do Nothing
                        }
                        prevStatusLeftDoor2 = id_telltales.bus_door2[0][2];
                    }
                }


                Image {
                    id: id_door2_left_dynamic
                    visible:id_telltales.bus_door2[0][3] === "DYNAMIC"
                    x:obj_menuops.type_of_vehicle === bus_three_axles ? 1071 : 952
                    y:(obj_menuops.type_of_vehicle === bus_three_axles) ? id_bus.y + 20 :id_bus.y + 25

                    source: (obj_menuops.type_of_vehicle === bus_three_axles) ?
                                "/pics/IC12_interface_graphics/buses/bus_with_four_doors"+id_telltales.bus_door2[0][0]:
                                "/pics/IC12_interface_graphics/buses/bus_with_three_doors"+id_telltales.bus_door2[0][0]
                    NumberAnimation on x {
                        id:leftAnimImg2
                        from: leftdoor2frompos
                        to: leftdoor2topos
                        duration: leftdoor_duration
                        running: true
                    }
                    Component.onCompleted: {
                        //console.log("The Value coming here is path and type", id_telltales.bus_door2[0][0])
                    }
                }

                function rightDoor2Changes() {
                    rightdoor2frompos = 0
                    rightdoor2topos   = 0
                    if (prevStatusRightDoor2 !== id_telltales.bus_door2[0][2])
                    {
                        if(id_telltales.bus_door2[0][2] === "OPENED" && id_telltales.bus_door2[0][3] === "DYNAMIC")
                        {
                            rightdoor2frompos = obj_menuops.type_of_vehicle === bus_three_axles ? 1112 : xValDoor2RightMax
                            rightdoor2topos   = rightdoor2frompos
                            rightdoor_duration = 1
                            rightdoor_running = true
                            rightAnimimg2.start()
                        } else if (id_telltales.bus_door2[0][2] === "OPENING" && id_telltales.bus_door2[0][3] === "DYNAMIC"){
                            rightdoor2frompos = obj_menuops.type_of_vehicle === bus_three_axles ? 1093 : xValDoor2RightMin
                            rightdoor2topos   = obj_menuops.type_of_vehicle === bus_three_axles ? 1112 : xValDoor2RightMax
                            rightdoor_duration = 2000
                            rightdoor_running = true
                            rightAnimimg2.start()
                        }
                        else if (id_telltales.bus_door2[0][2] === "CLOSING" && id_telltales.bus_door2[0][3] === "DYNAMIC"){
                            rightdoor2frompos = obj_menuops.type_of_vehicle === bus_three_axles ? 1112 : xValDoor2RightMax
                            rightdoor2topos   = obj_menuops.type_of_vehicle === bus_three_axles ? 1093 : xValDoor2RightMin
                            rightdoor_duration = 2000
                            rightdoor_running = true
                            rightAnimimg2.start()
                        }
                        else{
                            //Do Nothing
                        }
                        prevStatusRightDoor2 = id_telltales.bus_door2[0][2]
                    }
                }

                Image {
                    id: id_door2_right_dynamic
                    visible:id_telltales.bus_door2[0][3] === "DYNAMIC"
                    x:(obj_menuops.type_of_vehicle === bus_three_axles) ? 1093 : 981
                    y:(obj_menuops.type_of_vehicle === bus_three_axles) ? id_bus.y + 20 :id_bus.y + 25
                    source: (obj_menuops.type_of_vehicle === bus_three_axles) ?
                                "/pics/IC12_interface_graphics/buses/bus_with_four_doors"+id_telltales.bus_door2[0][1]:
                                "/pics/IC12_interface_graphics/buses/bus_with_three_doors"+id_telltales.bus_door2[0][1]
                    NumberAnimation on x {
                        id:rightAnimimg2
                        from: rightdoor2frompos
                        to: rightdoor2topos
                        duration: rightdoor_duration
                        running: true
                    }
                }

                /************************************Door 3 Changes*********************************************/


                Rectangle{
                    Image {
                        id: id_door3_static
                        visible:id_telltales.bus_door3[0][3] === "STATIC"
                        x:{
                            if(id_telltales.bus_door3[0][3] === "STATIC" &&
                                    (id_telltales.bus_door3[0][2] === "CLOSED" ||id_telltales.bus_door3[0][2] === "REQUEST"))
                            {
                                x :obj_menuops.type_of_vehicle === bus_three_axles ? 805 : xValDoor3LeftMax
                            }
                            else
                            {
                                if(id_telltales.bus_door3[0][3] === "STATIC"  &&
                                        (id_telltales.bus_door3[0][2] === "ERROR" || id_telltales.bus_door3[0][2] === "OBSTACLE_DETECT")){
                                    x : obj_menuops.type_of_vehicle === bus_three_axles ? 787 : (xValDoor3LeftMax - 15)
                                }
                            }
                        }
                        y: obj_menuops.type_of_vehicle === bus_three_axles ? id_bus.y + 20 : id_bus.y + 25
                        source: obj_menuops.type_of_vehicle === bus_three_axles ? "/pics/IC12_interface_graphics/buses/bus_with_four_doors"+id_telltales.bus_door3[0][0]:
                                    "/pics/IC12_interface_graphics/buses/bus_with_three_doors"+id_telltales.bus_door3[0][0]
                    }
                }

                function leftDoor3Changes() {
                    leftdoor3frompos = 0
                    leftdoor3topos   = 0
                    if(prevStatusLeftDoor3 !== id_telltales.bus_door3[0][2])
                    {
                        if(id_telltales.bus_door3[0][2] === "OPENED" && id_telltales.bus_door3[0][3] === "DYNAMIC"){
                            leftdoor3frompos =  obj_menuops.type_of_vehicle === bus_three_axles ? 785 : xValDoor3LeftMin
                            leftdoor3topos   = leftdoor3frompos
                            leftdoor_duration = 1
                            leftdoor_running = true
                            leftAnimImg3.start()
                        }
                        else if (id_telltales.bus_door3[0][2] === "OPENING" && id_telltales.bus_door3[0][3] === "DYNAMIC"){
                            leftdoor3frompos = obj_menuops.type_of_vehicle === bus_three_axles ? 805 : xValDoor3LeftMax
                            leftdoor3topos   = obj_menuops.type_of_vehicle === bus_three_axles ? 785 : xValDoor3LeftMin
                            leftdoor_duration = 2000
                            leftdoor_running = true
                            leftAnimImg3.start()
                        }  else if (id_telltales.bus_door3[0][2] === "CLOSING" && id_telltales.bus_door3[0][3] === "DYNAMIC"){
                            leftdoor3frompos = obj_menuops.type_of_vehicle === bus_three_axles ? 785 : xValDoor3LeftMin
                            leftdoor3topos   = obj_menuops.type_of_vehicle === bus_three_axles ? 805 : xValDoor3LeftMax
                            leftdoor_duration = 2000
                            leftdoor_running = true
                            leftAnimImg3.start()
                        } else{
                            //do Nothing
                        }
                        prevStatusLeftDoor3 = id_telltales.bus_door3[0][2];
                    }
                }


                Image {
                    id: id_door3_left_dynamic
                    visible:id_telltales.bus_door3[0][3] === "DYNAMIC"
                    x:(obj_menuops.type_of_vehicle === bus_three_axles) ? 805 : 717
                    y:(obj_menuops.type_of_vehicle === bus_three_axles) ? id_bus.y +20 : id_bus.y + 25
                    source: (obj_menuops.type_of_vehicle === bus_three_axles) ?
                                "/pics/IC12_interface_graphics/buses/bus_with_four_doors"+id_telltales.bus_door3[0][0]:
                                "/pics/IC12_interface_graphics/buses/bus_with_three_doors"+id_telltales.bus_door3[0][01]
                    NumberAnimation on x {
                        id:leftAnimImg3
                        from: leftdoor3frompos
                        to: leftdoor3topos
                        duration: leftdoor_duration
                        running: true
                    }
                }

                function rightDoor3Changes() {
                    rightdoor3frompos = 0
                    rightdoor3topos   = 0
                    if (prevStatusRightDoor3 !== id_telltales.bus_door3[0][2])
                    {
                        if(id_telltales.bus_door3[0][2] === "OPENED" && id_telltales.bus_door3[0][3] === "DYNAMIC")
                        {
                            rightdoor3frompos = (obj_menuops.type_of_vehicle === bus_three_axles) ? 845 : xValDoor3RightMax
                            rightdoor3topos   = rightdoor3frompos
                            rightdoor_duration = 1
                            rightdoor_running = true
                            rightAnimimg3.start()

                        } else if (id_telltales.bus_door3[0][2] === "OPENING" && id_telltales.bus_door3[0][3] === "DYNAMIC"){
                            rightdoor3frompos = (obj_menuops.type_of_vehicle === bus_three_axles) ? 826 : xValDoor3RightMin
                            rightdoor3topos   = (obj_menuops.type_of_vehicle === bus_three_axles) ? 845 : xValDoor3RightMax
                            rightdoor_duration = 2000
                            rightdoor_running = true
                            rightAnimimg3.start()
                        }
                        else if (id_telltales.bus_door3[0][2] === "CLOSING" && id_telltales.bus_door3[0][3] === "DYNAMIC"){
                            rightdoor3frompos = (obj_menuops.type_of_vehicle === bus_three_axles) ? 845 : xValDoor3RightMax
                            rightdoor3topos   = (obj_menuops.type_of_vehicle === bus_three_axles) ? 826 : xValDoor3RightMin
                            rightdoor_duration = 2000
                            rightdoor_running = true
                            rightAnimimg3.start()
                        }
                        else{
                            //Do Nothing
                        }
                        prevStatusRightDoor3 = id_telltales.bus_door3[0][2]
                    }
                }

                Image {
                    id: id_door3_right_dynamic
                    visible:id_telltales.bus_door3[0][3] === "DYNAMIC"
                    x:(obj_menuops.type_of_vehicle === bus_three_axles) ? 826 : 747
                    y:(obj_menuops.type_of_vehicle === bus_three_axles) ? id_bus.y+20 : id_bus.y + 25
                    source: (obj_menuops.type_of_vehicle === bus_three_axles) ?
                                "/pics/IC12_interface_graphics/buses/bus_with_four_doors"+id_telltales.bus_door3[0][1]:
                                "/pics/IC12_interface_graphics/buses/bus_with_three_doors"+id_telltales.bus_door3[0][1]
                    NumberAnimation on x {
                        id:rightAnimimg3
                        from: rightdoor3frompos
                        to: rightdoor3topos
                        duration: rightdoor_duration
                        running: true
                    }
                }
                /************************************Door 4 Changes*********************************************/

                Rectangle{
                    Image {
                        id: id_door4_static
                        visible:id_telltales.bus_door4[0][3] === "STATIC" && obj_menuops.type_of_vehicle === bus_three_axles
                        x:{
                            if(id_telltales.bus_door4[0][3] === "STATIC" &&
                                    (id_telltales.bus_door4[0][2] === "CLOSED" || id_telltales.bus_door4[0][2] === "REQUEST"))
                            {
                                x : 675
                            }
                            else
                            {
                                if(id_telltales.bus_door4[0][3] === "STATIC"  &&
                                        (id_telltales.bus_door4[0][2] === "ERROR" || id_telltales.bus_door4[0][2] === "OBSTACLE_DETECT")){
                                    x : 658
                                }
                            }
                        }
                        y: id_bus.y+20
                        source: obj_menuops.type_of_vehicle === bus_three_axles ? "/pics/IC12_interface_graphics/buses/bus_with_four_doors"+id_telltales.bus_door4[0][0]:
                                    "/pics/IC12_interface_graphics/buses/bus_with_three_doors"+id_telltales.bus_door4[0][0]
                    }
                }

                function leftDoor4Changes() {
                    leftdoor4frompos = 0
                    leftdoor4topos   = 0
                    if(prevStatusLeftDoor4 !== id_telltales.bus_door4[0][2])
                    {
                        if(id_telltales.bus_door4[0][2] === "OPENED" && id_telltales.bus_door4[0][3] === "DYNAMIC"){
                            leftdoor4frompos =  658
                            leftdoor4topos   = leftdoor4frompos
                            leftdoor_duration = 1
                            leftdoor_running = true
                            leftAnimImg4.start()
                        }
                        else if (id_telltales.bus_door4[0][2] === "OPENING" && id_telltales.bus_door4[0][3] === "DYNAMIC"){
                            leftdoor4frompos = 675
                            leftdoor4topos   = 658
                            leftdoor_duration = 2000
                            leftdoor_running = true
                            leftAnimImg4.start()
                        }  else if (id_telltales.bus_door4[0][2] === "CLOSING" && id_telltales.bus_door4[0][3] === "DYNAMIC"){
                            leftdoor4frompos = 658
                            leftdoor4topos   = 675
                            leftdoor_duration = 2000
                            leftdoor_running = true
                            leftAnimImg4.start()
                        } else{
                            //do Nothing
                        }
                        prevStatusLeftDoor4 = id_telltales.bus_door4[0][2];
                    }
                }


                Image {
                    id: id_door4_left_dynamic
                    visible:id_telltales.bus_door4[0][3] === "DYNAMIC" && obj_menuops.type_of_vehicle === bus_three_axles
                    x:675
                    y:id_bus.y+20
                    source: "/pics/IC12_interface_graphics/buses/bus_with_four_doors"+id_telltales.bus_door4[0][0]
                    NumberAnimation on x {
                        id:leftAnimImg4
                        from: leftdoor4frompos
                        to: leftdoor4topos
                        duration: leftdoor_duration
                        running: true
                    }
                }

                function rightDoor4Changes() {
                    rightdoor4frompos = 0
                    rightdoor4topos   = 0
                    if (prevStatusRightDoor4 !== id_telltales.bus_door4[0][2])
                    {
                        if(id_telltales.bus_door4[0][2] === "OPENED" && id_telltales.bus_door4[0][3] === "DYNAMIC")
                        {
                            rightdoor4frompos = 719
                            rightdoor4topos   = rightdoor4frompos
                            rightdoor_duration = 1
                            rightdoor_running = true
                            rightAnimimg4.start()

                        } else if (id_telltales.bus_door4[0][2] === "OPENING" && id_telltales.bus_door4[0][3] === "DYNAMIC"){
                            rightdoor4frompos = 697
                            rightdoor4topos   = 719
                            rightdoor_duration = 2000
                            rightdoor_running = true
                            rightAnimimg4.start()
                        }
                        else if (id_telltales.bus_door4[0][2] === "CLOSING" && id_telltales.bus_door4[0][3] === "DYNAMIC"){
                            rightdoor4frompos = 719
                            rightdoor4topos   = 697
                            rightdoor_duration = 2000
                            rightdoor_running = true
                            rightAnimimg4.start()
                        }
                        else{
                            //Do Nothing
                        }
                        prevStatusRightDoor4 = id_telltales.id_telltales.bus_door4[0][2]
                    }
                }

                Image {
                    id: id_door4_right_dynamic
                    visible:id_telltales.bus_door4[0][3] === "DYNAMIC" && obj_menuops.type_of_vehicle === bus_three_axles
                    x:697
                    y:id_bus.y+20
                    source: "/pics/IC12_interface_graphics/buses/bus_with_four_doors"+id_telltales.bus_door4[0][1]

                    NumberAnimation on x {
                        id:rightAnimimg4
                        from: rightdoor4frompos
                        to: rightdoor4topos
                        duration: rightdoor_duration
                        running: true
                    }
                }

}
