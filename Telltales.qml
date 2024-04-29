import QtQuick 2.9
import QtQuick.Layouts 1.12
import com.mettem.telltales 1.0
import QtMultimedia 5.6
import QtGraphicalEffects 1.12


Item {

    Bus{
		id:id_bus_
    }

    Qttelltales{
        objectName: "obj_qttelltales"
        id: id_telltales

        onBus_door1_changed: {
            id_bus_.leftDoor1Changes();
            id_bus_.rightDoor1Changes();
        }

        onBus_door2_changed: {
            id_bus_.leftDoor2Changes();
            id_bus_.rightDoor2Changes();
        }

        onBus_door3_changed: {
            id_bus_.leftDoor3Changes();
            id_bus_.rightDoor3Changes();
        }

        onBus_door4_changed: {
            id_bus_.leftDoor4Changes();
            id_bus_.rightDoor4Changes();
        }

        onTelltale_pos_76_changed: {
            handle_source_data()
        }

        onTelltale_pos_75_changed: {
            handle_source_data()
        }

        onDialguage1_Changed: {
            handle_source_data()
        }

        onDialguage2_Changed: {
            handle_source_data()
        }
    }



    property int airpressguage1: 0;
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

    property string source_data_indicator1
    property string source_data_indicator2

    function handle_source_data(){

        if(id_telltales.telltale_pos_75[pos0][pos1] === "true")
        {
            source_data_indicator1 =  "pics/IC12_interface_graphics/iC12_brake_circut_1_red.png"
        }else{
            source_data_indicator1 =  "pics/IC12_interface_graphics/iC12_brake_circut_1.png"
        }

        if(id_telltales.telltale_pos_76[pos0][pos1] === "true")
        {
            source_data_indicator2 = "pics/IC12_interface_graphics/iC12_brake_circut_2_red.png"
        }else{
            source_data_indicator2 = "pics/IC12_interface_graphics/iC12_brake_circut_2.png"
        }
    }

    Image {
        id: id_indicator1
        x: 266
        y: 658
        source: source_data_indicator1
        visible:source_data_indicator1 !== "undefined"
    }

    Image {
        id: id_indicator2
        x:1614
        y:658
        source: source_data_indicator2
        visible:source_data_indicator2 !== "undefined"
    }

    Image
    {
        id: id_fuel_ind
        x:338
        y:355
        height: 45
        width: 45
        visible: true
        source: {
            if(id_telltales.telltale_pos_77[pos0][pos1] === "false"){
                                   source: "pics/TellTales/G/White/G01_w.png"
                               } else{
                                   source: id_telltales.telltale_pos_77[pos0][pos0]
                               }
        }
        ColorOverlay{
            anchors.fill: id_fuel_ind
            source: id_fuel_ind
            color: if(id_telltales.telltale_pos_77[pos0][pos1] === "false"){
                       coflor: "#B6E3F2"
                   } else{
                       color: id_telltales.telltale_pos_77[pos0][pos2]
                   }
        }
    }

    Image
    {
        id: id_CoolTemp
        x:1457
        y:355
        height: 45
        width: 45
        visible:true
        source: {
            if(id_telltales.telltale_pos_78[pos0][pos1] === "false"){
                color: "pics/TellTales/F/White/F03_w.png"
            } else{
                color: id_telltales.telltale_pos_78[pos0][pos0]
            }
        }
        ColorOverlay{
            anchors.fill: id_CoolTemp
            source: id_CoolTemp
            color: {
                if(id_telltales.telltale_pos_78[pos0][pos1] === "false"){
                    color: "#B6E3F2"
                } else{
                    color: id_telltales.telltale_pos_78[pos0][pos2]
                }
            }
        }
    }

    Image
    {
        id: id_engine_speed_battery
        x:1457
        y:410
        height: 45
        width: 45
        visible: true
        source: {
            if(id_telltales.telltale_pos_80[pos0][pos1] === "false"){
                source: "pics/TellTales/M/White/M01_w.png"
            } else{
                source: id_telltales.telltale_pos_80[pos0][pos0]
            }
        }
        ColorOverlay{
            anchors.fill: id_engine_speed_battery
            source: id_engine_speed_battery
            color: {
                if(id_telltales.telltale_pos_80[pos0][pos1] === "false"){
                    color: "#B6E3F2"
                } else{
                    visible: id_telltales.telltale_pos_80[pos0][pos2]
                }
            }
        }
    }


    Image{
        id: id_telltale_01
        x:694
        y:205
        visible:id_telltales.telltale_pos_1[pos0][pos1] === "true"
        source: (id_telltales.telltale_pos_1[pos0][pos0] !== undefined) ? id_telltales.telltale_pos_1[0][0] : null

        ColorOverlay{
            anchors.fill: id_telltale_01
            source: id_telltale_01
            color: (id_telltales.telltale_pos_1[pos0][pos2] !== undefined) ? id_telltales.telltale_pos_1[0][2] : "transparent" // Set defaultcolor to transparent if undefined
        }
    }

    Image{
        id: id_telltale_02
        x:754
        y:205
        visible: id_telltales.telltale_pos_2[0][pos1] === "true"
        source: (id_telltales.telltale_pos_2[0][pos0] !== undefined) ? id_telltales.telltale_pos_2[0][0] : null

        ColorOverlay{
            anchors.fill: id_telltale_02
            source: id_telltale_02
            color: (id_telltales.telltale_pos_2[0][pos2] !== undefined) ? id_telltales.telltale_pos_2[0][2] : "transparent" // Set defaultcolor to transparent if undefined
        }
    }

    Image{
        id: id_telltale_03
        x:814
        y:205
        visible:id_telltales.telltale_pos_3[0][1] === "true"
        source: (id_telltales.telltale_pos_3[0][0] !== undefined) ? id_telltales.telltale_pos_3[0][0] : null

        ColorOverlay{
            anchors.fill: id_telltale_03
            source: id_telltale_03
            color: (id_telltales.telltale_pos_3[0][2] !== undefined) ? id_telltales.telltale_pos_3[0][2] : "transparent" // Set defaultcolor to transparent if undefined
        }
    }

    Image{
        id: id_telltale_04
        x:874
        y:205
        visible:id_telltales.telltale_pos_4[0][1] === "true"
        source: (id_telltales.telltale_pos_4[0][0] !== undefined) ? id_telltales.telltale_pos_4[0][0] : null

        ColorOverlay{
            anchors.fill: id_telltale_04
            source: id_telltale_04
            color: (id_telltales.telltale_pos_4[0][2] !== undefined) ? id_telltales.telltale_pos_4[0][2] : "transparent" // Set defaultcolor to transparent if undefined
        }
    }
    Image{
        id: id_telltale_05
        x:934
        y:205
        visible:id_telltales.telltale_pos_5[0][1] === "true"
        source: (id_telltales.telltale_pos_5[0][0] !== undefined) ? id_telltales.telltale_pos_5[0][0] : null

        ColorOverlay{
            anchors.fill: id_telltale_05
            source: id_telltale_05
            color: (id_telltales.telltale_pos_5[0][2] !== undefined) ? id_telltales.telltale_pos_5[0][2] : "transparent" // Set defaultcolor to transparent if undefined
        }
    }
    Image{
        id: id_telltale_06
        x:994
        y:205
        visible:id_telltales.telltale_pos_6[0][1] === "true"
        source: (id_telltales.telltale_pos_6[0][0] !== undefined) ? id_telltales.telltale_pos_6[0][0] : null

        ColorOverlay{
            anchors.fill: id_telltale_06
            source: id_telltale_06
            color: (id_telltales.telltale_pos_6[0][2] !== undefined) ? id_telltales.telltale_pos_6[0][2] : "transparent" // Set defaultcolor to transparent if undefined
        }
    }

    Image{
        id: id_telltale_07
        x:1054
        y:205
        visible:id_telltales.telltale_pos_7[0][1] === "true"
        source: (id_telltales.telltale_pos_7[0][0] !== undefined) ? id_telltales.telltale_pos_7[0][0] : null

        ColorOverlay{
            anchors.fill: id_telltale_07
            source: id_telltale_07
            color: (id_telltales.telltale_pos_7[0][2] !== undefined) ? id_telltales.telltale_pos_7[0][2] : "transparent" // Set defaultcolor to transparent if undefined
        }
    }

    Image{
        id: id_telltale_08
        x:1114
        y:205
        visible:id_telltales.telltale_pos_8[0][1] === "true"
        source: (id_telltales.telltale_pos_8[0][0] !== undefined) ? id_telltales.telltale_pos_8[0][0] : null

        ColorOverlay{
            anchors.fill: id_telltale_08
            source: id_telltale_08
            color: (id_telltales.telltale_pos_8[0][2] !== undefined) ? id_telltales.telltale_pos_8[0][2] : "transparent" // Set defaultcolor to transparent if undefined
        }
    }
    Image{
        id: id_telltale_09
        x:1174
        y:205
        visible:id_telltales.telltale_pos_9[0][1] === "true"
        source: (id_telltales.telltale_pos_9[0][0] !== undefined) ? id_telltales.telltale_pos_9[0][0] : null

        ColorOverlay{
            anchors.fill: id_telltale_09
            source: id_telltale_09
            color: (id_telltales.telltale_pos_9[0][2] !== undefined) ? id_telltales.telltale_pos_9[0][2] : "transparent" // Set defaultcolor to transparent if undefined
        }
    }

    ////* Row 2 //////

    Image{
        id: id_telltale_10
        x:634
        y:146
        visible: id_telltales.telltale_pos_10[0][1] === "true"
        source: if(id_telltales.telltale_pos_10[0][2] === "yellow"){"/pics/TellTales/A/White/A24_y.png"}

        ColorOverlay{
            anchors.fill: id_telltale_10
            source: id_telltale_10
            color: (id_telltales.telltale_pos_10[0][2] !== undefined) ? id_telltales.telltale_pos_10[0][2] : "transparent" // Set defaultcolor to transparent if undefined
        }
    }

    Image{
        id: id_telltale_11
        x:694
        y:146
        visible:id_telltales.telltale_pos_11[0][1] === "true"
        source: (id_telltales.telltale_pos_11[0][0] !== undefined) ? id_telltales.telltale_pos_11[0][0] : null

        ColorOverlay{
            anchors.fill: id_telltale_11
            source: id_telltale_11
            color: (id_telltales.telltale_pos_11[0][2] !== undefined) ? id_telltales.telltale_pos_11[0][2] : "transparent" // Set defaultcolor to transparent if undefined
        }
    }

    Image{
        id: id_telltale_12
        x:754
        y:146
        visible:id_telltales.telltale_pos_12[0][1] === "true"
        source: (id_telltales.telltale_pos_12[0][0] !== undefined) ? id_telltales.telltale_pos_12[0][0] : null

        ColorOverlay{
            anchors.fill: id_telltale_12
            source: id_telltale_12
            color: (id_telltales.telltale_pos_12[0][2] !== undefined) ? id_telltales.telltale_pos_12[0][2] : "transparent" // Set defaultcolor to transparent if undefined
        }
    }

    Image{
        id: id_telltale_13
        x:814
        y:146
        visible:id_telltales.telltale_pos_13[0][1] === "true"
        source: (id_telltales.telltale_pos_13[0][0] !== undefined) ? id_telltales.telltale_pos_13[0][0] : null

        ColorOverlay{
            anchors.fill: id_telltale_13
            source: id_telltale_13
            color: (id_telltales.telltale_pos_13[0][2] !== undefined) ? id_telltales.telltale_pos_13[0][2] : "transparent" // Set defaultcolor to transparent if undefined
        }
    }

    Image{
        id: id_telltale_14
        x:874
        y:146
        visible:id_telltales.telltale_pos_14[0][1] === "true"
        source: (id_telltales.telltale_pos_14[0][0] !== undefined) ? id_telltales.telltale_pos_14[0][0] : null

        ColorOverlay{
            anchors.fill: id_telltale_14
            source: id_telltale_14
            color: (id_telltales.telltale_pos_14[0][2] !== undefined) ? id_telltales.telltale_pos_14[0][2] : "transparent" // Set defaultcolor to transparent if undefined
        }
    }

    Image{
        id: id_telltale_15
        x:934
        y:146
        visible:id_telltales.telltale_pos_15[0][1] === "true"
        source: {
            if(id_telltales.telltale_pos_15[0][2] === "yellow") source: "/pics/TellTales/I/I30_y.png"
            else if(id_telltales.telltale_pos_15[0][2] === "red") source: "/pics/TellTales/I/I30_r.png"
        }

        ColorOverlay{
            anchors.fill: id_telltale_15
            source: id_telltale_15
            color: (id_telltales.telltale_pos_15[0][2] !== undefined) ? id_telltales.telltale_pos_15[0][2] : "transparent" // Set defaultcolor to transparent if undefined
        }
    }

    Image{
        id: id_telltale_16
        x:994
        y:146
        visible:id_telltales.telltale_pos_16[0][1] === "true"
        source: (id_telltales.telltale_pos_16[0][0] !== undefined) ? id_telltales.telltale_pos_16[0][0] : null

        ColorOverlay{
            anchors.fill: id_telltale_16
            source: id_telltale_16
            color: (id_telltales.telltale_pos_16[0][2] !== undefined) ? id_telltales.telltale_pos_16[0][2] : "transparent" // Set defaultcolor to transparent if undefined
        }
    }

    Image{
        id: id_telltale_17
        x:1054
        y:146
        visible:id_telltales.telltale_pos_17[0][1] === "true"
        source: (id_telltales.telltale_pos_17[0][0] !== undefined) ? id_telltales.telltale_pos_17[0][0] : null

        ColorOverlay{
            anchors.fill: id_telltale_17
            source: id_telltale_17
            color: (id_telltales.telltale_pos_17[0][2] !== undefined) ? id_telltales.telltale_pos_17[0][2] : "transparent" // Set defaultcolor to transparent if undefined
        }
    }

    Image{
        id: id_telltale_18
        x:1114
        y:146
        visible:id_telltales.telltale_pos_18[0][1] === "true"
        source: (id_telltales.telltale_pos_18[0][0] !== undefined) ? id_telltales.telltale_pos_18[0][0] : null

        ColorOverlay{
            anchors.fill: id_telltale_18
            source: id_telltale_18
            color: (id_telltales.telltale_pos_18[0][2] !== undefined) ? id_telltales.telltale_pos_18[0][2] : "transparent" // Set defaultcolor to transparent if undefined
        }
    }

    Image{
        id: id_telltale_19
        x:1174
        y:146
        visible:id_telltales.telltale_pos_19[0][1] === "true"
        source: (id_telltales.telltale_pos_19[0][0] !== undefined) ? id_telltales.telltale_pos_19[0][0] : null

        ColorOverlay{
            anchors.fill: id_telltale_19
            source: id_telltale_19
            color: (id_telltales.telltale_pos_19[0][2] !== undefined) ? id_telltales.telltale_pos_19[0][2] : "transparent" // Set defaultcolor to transparent if undefined
        }
    }

    Image{
        id: id_telltale_20
        x:1234
        y:146
        visible:id_telltales.telltale_pos_20[0][1] === "true"
        source: if(id_telltales.telltale_pos_20[0][2] === "red"){"/pics/TellTales/B/White/B26_r.png"}

        ColorOverlay{
            anchors.fill: id_telltale_20
            source: id_telltale_20
            color: (id_telltales.telltale_pos_20[0][2] !== undefined) ? id_telltales.telltale_pos_20[0][2] : "transparent" // Set defaultcolor to transparent if undefined
        }
    }


    //Row 3 //


    Image{
        id: id_telltale_21
        x:574
        y:87
        visible:id_telltales.telltale_pos_21[0][1] === "true"
        source: (id_telltales.telltale_pos_21[0][0] !== undefined) ? id_telltales.telltale_pos_21[0][0] : null

        ColorOverlay{
            anchors.fill: id_telltale_21
            source: id_telltale_21
            color: (id_telltales.telltale_pos_21[0][2] !== undefined) ? id_telltales.telltale_pos_21[0][2] : "transparent" // Set defaultcolor to transparent if undefined
        }
    }


    Image{
        id: id_telltale_22
        x:634
        y:87
        visible:id_telltales.telltale_pos_22[0][1] === "true"
        source: (id_telltales.telltale_pos_22[0][0] !== undefined) ? id_telltales.telltale_pos_22[0][0] : null

        ColorOverlay{
            anchors.fill: id_telltale_22
            source: id_telltale_22
            color: (id_telltales.telltale_pos_22[0][2] !== undefined) ? id_telltales.telltale_pos_22[0][2] : "transparent" // Set defaultcolor to transparent if undefined
        }
    }


    Image{
        id: id_telltale_23
        x:694
        y:87
        visible:id_telltales.telltale_pos_23[0][1] === "true"
        source: (id_telltales.telltale_pos_23[0][0] !== undefined) ? id_telltales.telltale_pos_23[0][0] : null

        ColorOverlay{
            anchors.fill: id_telltale_23
            source: id_telltale_23
            color: (id_telltales.telltale_pos_23[0][2] !== undefined) ? id_telltales.telltale_pos_23[0][2] : "transparent" // Set defaultcolor to transparent if undefined
        }
    }


    Image{
        id: id_telltale_24
        x:754
        y:87
        visible:id_telltales.telltale_pos_24[0][1] === "true"
        source: (id_telltales.telltale_pos_24[0][0] !== undefined) ? id_telltales.telltale_pos_24[0][0] : null

        ColorOverlay{
            anchors.fill: id_telltale_24
            source: id_telltale_24
            color: (id_telltales.telltale_pos_24[0][2] !== undefined) ? id_telltales.telltale_pos_24[0][2] : "transparent" // Set defaultcolor to transparent if undefined
        }
    }


    Image{
        id: id_telltale_25
        x:814
        y:87
        visible:id_telltales.telltale_pos_25[0][1] === "true"
        source: (id_telltales.telltale_pos_25[0][0] !== undefined) ? id_telltales.telltale_pos_25[0][0] : null

        ColorOverlay{
            anchors.fill: id_telltale_25
            source: id_telltale_25
            color: (id_telltales.telltale_pos_25[0][2] !== undefined) ? id_telltales.telltale_pos_25[0][2] : "transparent" // Set defaultcolor to transparent if undefined
        }
    }


    Image{
        id: id_telltale_26
        x:874
        y:87
        visible:id_telltales.telltale_pos_26[0][1] === "true"
        source: (id_telltales.telltale_pos_26[0][0] !== undefined) ? id_telltales.telltale_pos_26[0][0] : null

        ColorOverlay{
            anchors.fill: id_telltale_26
            source: id_telltale_26
            color: (id_telltales.telltale_pos_26[0][2] !== undefined) ? id_telltales.telltale_pos_26[0][2] : "transparent" // Set defaultcolor to transparent if undefined
        }
    }


    Image{
        id: id_telltale_27
        x:934
        y:87
        visible:id_telltales.telltale_pos_27[0][1] === "true"
        source: (id_telltales.telltale_pos_27[0][0] !== undefined) ? id_telltales.telltale_pos_27[0][0] : null

        ColorOverlay{
            anchors.fill: id_telltale_27
            source: id_telltale_27
            color: (id_telltales.telltale_pos_27[0][2] !== undefined) ? id_telltales.telltale_pos_27[0][2] : "transparent" // Set defaultcolor to transparent if undefined
        }
    }


    Image{
        id: id_telltale_28
        x:994
        y:87
        visible:id_telltales.telltale_pos_28[0][1] === "true"
        source: (id_telltales.telltale_pos_28[0][0] !== undefined) ? id_telltales.telltale_pos_28[0][0] : null

        ColorOverlay{
            anchors.fill: id_telltale_28
            source: id_telltale_28
            color: (id_telltales.telltale_pos_28[0][2] !== undefined) ? id_telltales.telltale_pos_28[0][2] : "transparent" // Set defaultcolor to transparent if undefined
        }
    }


    Image{
        id: id_telltale_29
        x:1054
        y:87
        visible:id_telltales.telltale_pos_29[0][1] === "true"
        source: (id_telltales.telltale_pos_29[0][0] !== undefined) ? id_telltales.telltale_pos_29[0][0] : null

        ColorOverlay{
            anchors.fill: id_telltale_29
            source: id_telltale_29
            color: (id_telltales.telltale_pos_29[0][2] !== undefined) ? id_telltales.telltale_pos_29[0][2] : "transparent" // Set defaultcolor to transparent if undefined
        }
    }


    Image{
        id: id_telltale_30
        x:1114
        y:87
        visible:id_telltales.telltale_pos_30[0][1] === "true"
        source: (id_telltales.telltale_pos_30[0][0] !== undefined) ? id_telltales.telltale_pos_30[0][0] : null

        ColorOverlay{
            anchors.fill: id_telltale_30
            source: id_telltale_30
            color: (id_telltales.telltale_pos_30[0][2] !== undefined) ? id_telltales.telltale_pos_30[0][2] : "transparent" // Set defaultcolor to transparent if undefined
        }
    }


    Image{
        id: id_telltale_31
        x:1174
        y:87
        visible:id_telltales.telltale_pos_31[0][1] === "true"
        source: (id_telltales.telltale_pos_31[0][0] !== undefined) ? id_telltales.telltale_pos_31[0][0] : null

        ColorOverlay{
            anchors.fill: id_telltale_31
            source: id_telltale_31
            color: (id_telltales.telltale_pos_31[0][2] !== undefined) ? id_telltales.telltale_pos_31[0][2] : "transparent" // Set defaultcolor to transparent if undefined
        }
    }


    Image{
        id: id_telltale_32
        x:1234
        y:87
        visible:id_telltales.telltale_pos_32[0][1] === "true"
        source: (id_telltales.telltale_pos_32[0][0] !== undefined) ? id_telltales.telltale_pos_32[0][0] : null

        ColorOverlay{
            anchors.fill: id_telltale_32
            source: id_telltale_32
            color: (id_telltales.telltale_pos_32[0][2] !== undefined) ? id_telltales.telltale_pos_32[0][2] : "transparent" // Set defaultcolor to transparent if undefined
        }
    }


    Image{
        id: id_telltale_33
        x:1294
        y:87
        visible:id_telltales.telltale_pos_33[0][1] === "true"
        source: (id_telltales.telltale_pos_33[0][0] !== undefined) ? id_telltales.telltale_pos_33[0][0] : null

        ColorOverlay{
            anchors.fill: id_telltale_33
            source: id_telltale_33
            color: (id_telltales.telltale_pos_33[0][2] !== undefined) ? id_telltales.telltale_pos_33[0][2] : "transparent" // Set defaultcolor to transparent if undefined
        }
    }

    Image{
        id: id_telltale_34
        x:34
        y:28
        visible:id_telltales.telltale_pos_34[0][1] === "true"
        source: {
            if(id_telltales.telltale_pos_34[0][2] === "green") source: "pics/TellTales/K/White/K34_g.png"
            else if(id_telltales.telltale_pos_34[0][2] === "red") source: "pics/TellTales/K/White/K34_r.png"
        }
        ColorOverlay{
            anchors.fill: id_telltale_34
            source: id_telltale_34
            color: (id_telltales.telltale_pos_34[0][2] !== undefined) ? id_telltales.telltale_pos_34[0][2] : "transparent" // Set defaultcolor to transparent if undefined
        }
    }

    Image{
        id: id_telltale_35
        x:94
        y:28
        visible:id_telltales.telltale_pos_35[0][1] === "true"
        source: (id_telltales.telltale_pos_35[0][0] !== undefined) ? id_telltales.telltale_pos_35[0][0] : null

        ColorOverlay{
            anchors.fill: id_telltale_35
            source: id_telltale_35
            color: (id_telltales.telltale_pos_35[0][2] !== undefined) ? id_telltales.telltale_pos_35[0][2] : "transparent" // Set defaultcolor to transparent if undefined
        }
    }

    Image{
        id: id_telltale_36
        x:154
        y:28
        visible:id_telltales.telltale_pos_36[0][1] === "true"
        source: (id_telltales.telltale_pos_36[0][0] !== undefined) ? id_telltales.telltale_pos_36[0][0] : null

        ColorOverlay{
            anchors.fill: id_telltale_36
            source: id_telltale_36
            color: (id_telltales.telltale_pos_36[0][2] !== undefined) ? id_telltales.telltale_pos_36[0][2] : "transparent" // Set defaultcolor to transparent if undefined
        }
    }

    Image{
        id: id_telltale_37
        x:214
        y:28
        visible:id_telltales.telltale_pos_37[0][1] === "true"
        source: (id_telltales.telltale_pos_37[0][0] !== undefined) ? id_telltales.telltale_pos_37[0][0] : null

        ColorOverlay{
            anchors.fill: id_telltale_37
            source: id_telltale_37
            color: (id_telltales.telltale_pos_37[0][2] !== undefined) ? id_telltales.telltale_pos_37[0][2] : "transparent" // Set defaultcolor to transparent if undefined
        }
    }


    Image{
        id: id_telltale_38
        x:274
        y:28
        visible:id_telltales.telltale_pos_38[0][1] === "true"
        source: (id_telltales.telltale_pos_38[0][0] !== undefined) ? id_telltales.telltale_pos_38[0][0] : null

        ColorOverlay{
            anchors.fill: id_telltale_38
            source: id_telltale_38
            color: (id_telltales.telltale_pos_38[0][2] !== undefined) ? id_telltales.telltale_pos_38[0][2] : "transparent" // Set defaultcolor to transparent if undefined
        }
    }

    Image{
        id: id_telltale_39
        x:334
        y:28
        visible:id_telltales.telltale_pos_39[0][1] === "true"
        source: (id_telltales.telltale_pos_39[0][0] !== undefined) ? id_telltales.telltale_pos_39[0][0] : null

        ColorOverlay{
            anchors.fill: id_telltale_39
            source: id_telltale_39
            color: (id_telltales.telltale_pos_39[0][2] !== undefined) ? id_telltales.telltale_pos_39[0][2] : "transparent" // Set defaultcolor to transparent if undefined
        }
    }

    Image{
        id: id_telltale_40
        x:394
        y:28
        visible:id_telltales.telltale_pos_40[0][1] === "true"
        source: (id_telltales.telltale_pos_40[0][0] !== undefined) ? id_telltales.telltale_pos_40[0][0] : null

        ColorOverlay{
            anchors.fill: id_telltale_40
            source: id_telltale_40
            color: (id_telltales.telltale_pos_40[0][2] !== undefined) ? id_telltales.telltale_pos_40[0][2] : "transparent" // Set defaultcolor to transparent if undefined
        }
    }

    Image{
        id: id_telltale_41
        x:454
        y:28
        visible:id_telltales.telltale_pos_41[0][1] === "true"
        source: (id_telltales.telltale_pos_41[0][0] !== undefined) ? id_telltales.telltale_pos_41[0][0] : null

        ColorOverlay{
            anchors.fill: id_telltale_41
            source: id_telltale_41
            color: (id_telltales.telltale_pos_41[0][2] !== undefined) ? id_telltales.telltale_pos_41[0][2] : "transparent" // Set defaultcolor to transparent if undefined
        }
    }

    Image{
        id: id_telltale_42
        x:514
        y:28
        visible:id_telltales.telltale_pos_42[0][1] === "true"
        source: (id_telltales.telltale_pos_42[0][0] !== undefined) ? id_telltales.telltale_pos_42[0][0] : null

        ColorOverlay{
            anchors.fill: id_telltale_42
            source: id_telltale_42
            color: (id_telltales.telltale_pos_42[0][2] !== undefined) ? id_telltales.telltale_pos_42[0][2] : "transparent" // Set defaultcolor to transparent if undefined
        }
    }

    Image{
        id: id_telltale_43
        x:574
        y:28
        visible:id_telltales.telltale_pos_43[0][1] === "true"
        source: (id_telltales.telltale_pos_43[0][0] !== undefined) ? id_telltales.telltale_pos_43[0][0] : null

        ColorOverlay{
            anchors.fill: id_telltale_43
            source: id_telltale_43
            color: (id_telltales.telltale_pos_43[0][2] !== undefined) ? id_telltales.telltale_pos_43[0][2] : "transparent" // Set defaultcolor to transparent if undefined
        }
    }

    Image{
        id: id_telltale_44
        x:634
        y:28
        visible:id_telltales.telltale_pos_44[0][1] === "true"
        source: (id_telltales.telltale_pos_44[0][0] !== undefined) ? id_telltales.telltale_pos_44[0][0] : null

        ColorOverlay{
            anchors.fill: id_telltale_44
            source: id_telltale_44
            color: (id_telltales.telltale_pos_44[0][2] !== undefined) ? id_telltales.telltale_pos_44[0][2] : "transparent" // Set defaultcolor to transparent if undefined
        }
    }

    Image{
        id: id_telltale_45
        x:694
        y:28
        visible:id_telltales.telltale_pos_45[0][1] === "true"
        source: (id_telltales.telltale_pos_45[0][0] !== undefined) ? id_telltales.telltale_pos_45[0][0] : null

//        ColorOverlay{
//            anchors.fill: id_telltale_45
//            source: id_telltale_45
//            color: (id_telltales.telltale_pos_45[0][2] !== undefined) ? id_telltales.telltale_pos_45[0][2] : "transparent" // Set defaultcolor to transparent if undefined
//        }
    }

    Image{
        id: id_telltale_46
        x:754
        y:28
        visible:id_telltales.telltale_pos_46[0][1] === "true"
        source: (id_telltales.telltale_pos_46[0][0] !== undefined) ? id_telltales.telltale_pos_46[0][0] : null

        ColorOverlay{
            anchors.fill: id_telltale_46
            source: id_telltale_46
            color: (id_telltales.telltale_pos_46[0][2] !== undefined) ? id_telltales.telltale_pos_46[0][2] : "transparent" // Set defaultcolor to transparent if undefined
        }
    }

    Image{
        id: id_telltale_47
        x:814
        y:28
        visible:id_telltales.telltale_pos_47[0][1] === "true"
        source: (id_telltales.telltale_pos_47[0][0] !== undefined) ? id_telltales.telltale_pos_47[0][0] : null

        ColorOverlay{
            anchors.fill: id_telltale_47
            source: id_telltale_47
            color: (id_telltales.telltale_pos_47[0][2] !== undefined) ? id_telltales.telltale_pos_47[0][2] : "transparent" // Set defaultcolor to transparent if undefined
        }
    }

    Image{
        id: id_telltale_48
        x:874
        y:28
        visible:id_telltales.telltale_pos_48[0][1] === "true"
        source: (id_telltales.telltale_pos_48[0][0] !== undefined) ? id_telltales.telltale_pos_48[0][0] : null

        ColorOverlay{
            anchors.fill: id_telltale_48
            source: id_telltale_48
            color: (id_telltales.telltale_pos_48[0][2] !== undefined) ? id_telltales.telltale_pos_48[0][2] : "transparent" // Set defaultcolor to transparent if undefined
        }
    }

    Image{
        id: id_telltale_49
        x:934
        y:28
        visible:id_telltales.telltale_pos_49[0][1] === "true"
        source: (id_telltales.telltale_pos_49[0][0] !== undefined) ? id_telltales.telltale_pos_49[0][0] : null

        ColorOverlay{
            anchors.fill: id_telltale_49
            source: id_telltale_49
            color: (id_telltales.telltale_pos_49[0][2] !== undefined) ? id_telltales.telltale_pos_49[0][2] : "transparent" // Set defaultcolor to transparent if undefined
        }
    }

    Image{
        id: id_telltale_50
        x:994
        y:28
        visible:id_telltales.telltale_pos_50[0][1] === "true"
        source: {
            if(id_telltales.telltale_pos_50[0][0] === "pics/TellTales/B/White/B21.png"){
                if(id_telltales.telltale_pos_50[0][2] === "green") source: "pics/TellTales/B/White/B21_g.png"
                else if(id_telltales.telltale_pos_50[0][2] === "yellow") source: "pics/TellTales/B/White/B21_y.png"
                else if(id_telltales.telltale_pos_50[0][2] === "red") source: "pics/TellTales/B/White/B21_r.png"
            }
            else if(id_telltales.telltale_pos_50[0][0] === "pics/TellTales/B/White/B24.png"){
                source: id_telltales.telltale_pos_50[0][0] //"pics/TellTales/B/White/B24.png"
            }
            else source: null
        }

//        ColorOverlay{
//            anchors.fill: id_telltale_50
//            source: id_telltale_50
//            color: (id_telltales.telltale_pos_50[0][2] !== undefined) ? id_telltales.telltale_pos_50[0][2] : "transparent" // Set defaultcolor to transparent if undefined
//        }
    }

    Image{
        id: id_telltale_51
        x:1054
        y:28
        visible:id_telltales.telltale_pos_51[0][1] === "true"
        source:{
            if(id_telltales.telltale_pos_51[0][2] === "green") source: "pics/TellTales/B/White/B14_g.png"
            else if(id_telltales.telltale_pos_51[0][2] === "yellow") source: "pics/TellTales/B/White/B14_y.png"
            else if(id_telltales.telltale_pos_51[0][2] === "red") source: "pics/TellTales/B/White/B14_r.png"
        }
            //(id_telltales.telltale_pos_51[0][0] !== undefined) ? id_telltales.telltale_pos_51[0][0] : null

        ColorOverlay{
            anchors.fill: id_telltale_51
            source: id_telltale_51
            color: (id_telltales.telltale_pos_51[0][2] !== undefined) ? id_telltales.telltale_pos_51[0][2] : "transparent" // Set defaultcolor to transparent if undefined
        }
    }

    Image{
        id: id_telltale_52
        x:1114
        y:28
        visible:id_telltales.telltale_pos_52[0][1] === "true"
        source: (id_telltales.telltale_pos_52[0][0] !== undefined) ? id_telltales.telltale_pos_52[0][0] : null

        ColorOverlay{
            anchors.fill: id_telltale_52
            source: id_telltale_52
            color: (id_telltales.telltale_pos_52[0][2] !== undefined) ? id_telltales.telltale_pos_52[0][2] : "transparent" // Set defaultcolor to transparent if undefined
        }
    }

    Image{
        id: id_telltale_53
        x:1174
        y:28
        visible:id_telltales.telltale_pos_53[0][1] === "true"
        source: (id_telltales.telltale_pos_53[0][0] !== undefined) ? id_telltales.telltale_pos_53[0][0] : null

        ColorOverlay{
            anchors.fill: id_telltale_53
            source: id_telltale_53
            color: (id_telltales.telltale_pos_53[0][2] !== undefined) ? id_telltales.telltale_pos_53[0][2] : "transparent" // Set defaultcolor to transparent if undefined
        }
    }

    Image{
        id: id_telltale_54
        x:1234
        y:28
        visible:id_telltales.telltale_pos_54[0][1] === "true"
        source: {
            if(id_telltales.telltale_pos_54[0][2] === "red") source: "pics/TellTales/B/White/B05_r.png"
            else if(id_telltales.telltale_pos_54[0][2] === "yellow") source: "pics/TellTales/B/White/B05_y.png"
        }

        ColorOverlay{
            anchors.fill: id_telltale_54
            source: id_telltale_54
            color: (id_telltales.telltale_pos_54[0][2] !== undefined) ? id_telltales.telltale_pos_54[0][2] : "transparent" // Set defaultcolor to transparent if undefined
        }
    }

    Image{
        id: id_telltale_55
        x:1294
        y:28
        visible:id_telltales.telltale_pos_55[0][1] === "true"
        source: (id_telltales.telltale_pos_55[0][0] !== undefined) ? id_telltales.telltale_pos_55[0][0] : null

        ColorOverlay{
            anchors.fill: id_telltale_55
            source: id_telltale_55
            color: (id_telltales.telltale_pos_55[0][2] !== undefined) ? id_telltales.telltale_pos_55[0][2] : "transparent" // Set defaultcolor to transparent if undefined
        }
    }

    Image{
        id: id_telltale_56
        x:1354
        y:28
        visible:id_telltales.telltale_pos_56[0][1] === "true"
        source: (id_telltales.telltale_pos_56[0][0] !== undefined) ? id_telltales.telltale_pos_56[0][0] : null

        ColorOverlay{
            anchors.fill: id_telltale_56
            source: id_telltale_56
            color: (id_telltales.telltale_pos_56[0][2] !== undefined) ? id_telltales.telltale_pos_56[0][2] : "transparent" // Set defaultcolor to transparent if undefined
        }
    }

    Image{
        id: id_telltale_57
        x:1414
        y:28
        visible:id_telltales.telltale_pos_57[0][1] === "true"
        source: (id_telltales.telltale_pos_57[0][0] !== undefined) ? id_telltales.telltale_pos_57[0][0] : null

        ColorOverlay{
            anchors.fill: id_telltale_57
            source: id_telltale_57
            color: (id_telltales.telltale_pos_57[0][2] !== undefined) ? id_telltales.telltale_pos_57[0][2] : "transparent" // Set defaultcolor to transparent if undefined
        }
    }

    Image{
        id: id_telltale_58
        x:1474
        y:28
        visible:id_telltales.telltale_pos_58[0][1] === "true"
        source: (id_telltales.telltale_pos_58[0][0] !== undefined) ? id_telltales.telltale_pos_58[0][0] : null

        ColorOverlay{
            anchors.fill: id_telltale_58
            source: id_telltale_58
            color: (id_telltales.telltale_pos_58[0][2] !== undefined) ? id_telltales.telltale_pos_58[0][2] : "transparent" // Set defaultcolor to transparent if undefined
        }
    }

    Image{
        id: id_telltale_59
        x:1534
        y:28
        visible:id_telltales.telltale_pos_59[0][1] === "true"
        source: (id_telltales.telltale_pos_59[0][0] !== undefined) ? id_telltales.telltale_pos_59[0][0] : null

        ColorOverlay{
            anchors.fill: id_telltale_59
            source: id_telltale_59
            color: (id_telltales.telltale_pos_59[0][2] !== undefined) ? id_telltales.telltale_pos_59[0][2] : "transparent" // Set defaultcolor to transparent if undefined
        }
    }

    Image{
        id: id_telltale_60
        x:1594
        y:28
        visible:id_telltales.telltale_pos_60[0][1] === "true"
        source: (id_telltales.telltale_pos_60[0][0] !== undefined) ? id_telltales.telltale_pos_60[0][0] : null

        ColorOverlay{
            anchors.fill: id_telltale_60
            source: id_telltale_60
            color: (id_telltales.telltale_pos_60[0][2] !== undefined) ? id_telltales.telltale_pos_60[0][2] : "transparent" // Set defaultcolor to transparent if undefined
        }
    }

    Image{
        id: id_telltale_61
        x:1654
        y:28
        visible:id_telltales.telltale_pos_61[0][1] === "true"
        source: (id_telltales.telltale_pos_61[0][0] !== undefined) ? id_telltales.telltale_pos_61[0][0] : null

        ColorOverlay{
            anchors.fill: id_telltale_61
            source: id_telltale_61
            color: (id_telltales.telltale_pos_61[0][2] !== undefined) ? id_telltales.telltale_pos_61[0][2] : "transparent" // Set defaultcolor to transparent if undefined
        }
    }

    Image{
        id: id_telltale_62
        x:1714
        y:28
        visible:id_telltales.telltale_pos_62[0][1] === "true"
        source: (id_telltales.telltale_pos_62[0][0] !== undefined) ? id_telltales.telltale_pos_62[0][0] : null

        ColorOverlay{
            anchors.fill: id_telltale_62
            source: id_telltale_62
            color: (id_telltales.telltale_pos_62[0][2] !== undefined) ? id_telltales.telltale_pos_62[0][2] : "transparent" // Set defaultcolor to transparent if undefined
        }
    }

    Image{
        id: id_telltale_63
        x:1774
        y:28
        visible:id_telltales.telltale_pos_63[0][1] === "true"
        source: (id_telltales.telltale_pos_63[0][0] !== undefined) ? id_telltales.telltale_pos_63[0][0] : null

        ColorOverlay{
            anchors.fill: id_telltale_63
            source: id_telltale_63
            color: (id_telltales.telltale_pos_63[0][2] !== undefined) ? id_telltales.telltale_pos_63[0][2] : "transparent" // Set defaultcolor to transparent if undefined
        }
    }

    Image{
        id: id_telltale_64
        x:1834
        y:28
        visible:id_telltales.telltale_pos_64[0][1] === "true"
        source: (id_telltales.telltale_pos_64[0][0] !== undefined) ? id_telltales.telltale_pos_64[0][0] : null

        ColorOverlay{
            anchors.fill: id_telltale_64
            source: id_telltale_64
            color: (id_telltales.telltale_pos_64[0][2] !== undefined) ? id_telltales.telltale_pos_64[0][2] : "transparent" // Set defaultcolor to transparent if undefined
        }
    }


    //

    Image{
        id: id_telltale_65
        x:34
        y:87
        visible:id_telltales.telltale_pos_65[0][1] === "true"
        source: {
            if(id_telltales.telltale_pos_65[0][2] === "yellow") source: "pics/TellTales/K/White/K35_y.png"
            else if(id_telltales.telltale_pos_65[0][2] === "red") source: "pics/TellTales/K/White/K35_r.png"
        }

        ColorOverlay{
            anchors.fill: id_telltale_65
            source: id_telltale_65
            color: (id_telltales.telltale_pos_65[0][2] !== undefined) ? id_telltales.telltale_pos_65[0][2] : "transparent" // Set defaultcolor to transparent if undefined
        }
    }


    Image{
        id: id_telltale_66
        x:94
        y:87
        visible:id_telltales.telltale_pos_66[0][1] === "true"
        source: (id_telltales.telltale_pos_66[0][0] !== undefined) ? id_telltales.telltale_pos_66[0][0] : null

        ColorOverlay{
            anchors.fill: id_telltale_66
            source: id_telltale_66
            color: (id_telltales.telltale_pos_66[0][2] !== undefined) ? id_telltales.telltale_pos_66[0][2] : "transparent" // Set defaultcolor to transparent if undefined
        }
    }

    Image{
        id: id_telltale_67
        x:1774
        y:87
        visible:id_telltales.telltale_pos_67[0][1] === "true"
        source: (id_telltales.telltale_pos_67[0][0] !== undefined) ? id_telltales.telltale_pos_67[0][0] : null

        ColorOverlay{
            anchors.fill: id_telltale_67
            source: id_telltale_67
            color: (id_telltales.telltale_pos_67[0][2] !== undefined) ? id_telltales.telltale_pos_67[0][2] : "transparent" // Set defaultcolor to transparent if undefined
        }
    }


    Image{
        id: id_telltale_68
        x:1834
        y:87
        visible:id_telltales.telltale_pos_68[0][1] === "true"
        source: (id_telltales.telltale_pos_68[0][0] !== undefined) ? id_telltales.telltale_pos_68[0][0] : null

        ColorOverlay{
            anchors.fill: id_telltale_68
            source: id_telltale_68
            color: (id_telltales.telltale_pos_68[0][2] !== undefined) ? id_telltales.telltale_pos_68[0][2] : "transparent" // Set defaultcolor to transparent if undefined
        }
    }

    Image{
        id: id_telltale_69
        x:34
        y:146
        visible:id_telltales.telltale_pos_69[0][1] === "true"
        source: (id_telltales.telltale_pos_69[0][0] !== undefined) ? id_telltales.telltale_pos_69[0][0] : null

        ColorOverlay{
            anchors.fill: id_telltale_69
            source: id_telltale_69
            color: (id_telltales.telltale_pos_69[0][2] !== undefined) ? id_telltales.telltale_pos_69[0][2] : "transparent" // Set defaultcolor to transparent if undefined
        }
    }


    Image{
        id: id_telltale_70
        x:1834
        y:146
        visible:id_telltales.telltale_pos_70[0][1] === "true"
        source: (id_telltales.telltale_pos_70[0][0] !== undefined) ? id_telltales.telltale_pos_70[0][0] : null

        ColorOverlay{
            anchors.fill: id_telltale_70
            source: id_telltale_70
            color: (id_telltales.telltale_pos_70[0][2] !== undefined) ? id_telltales.telltale_pos_70[0][2] : "transparent" // Set defaultcolor to transparent if undefined
        }
    }


    Image{
        id: id_telltale_71
        x:34
        y:205
        visible:id_telltales.telltale_pos_71[0][1] === "true"
        source: (id_telltales.telltale_pos_71[0][0] !== undefined) ? id_telltales.telltale_pos_71[0][0] : null

        ColorOverlay{
            anchors.fill: id_telltale_71
            source: id_telltale_71
            color: (id_telltales.telltale_pos_71[0][2] !== undefined) ? id_telltales.telltale_pos_71[0][2] : "transparent" // Set defaultcolor to transparent if undefined
        }
    }


    Image{
        id: id_telltale_72
        x:1834
        y:205
        visible:id_telltales.telltale_pos_72[0][1] === "true"
        source: (id_telltales.telltale_pos_72[0][0] !== undefined) ? id_telltales.telltale_pos_72[0][0] : null

        ColorOverlay{
            anchors.fill: id_telltale_72
            source: id_telltale_72
            color: (id_telltales.telltale_pos_72[0][2] !== undefined) ? id_telltales.telltale_pos_72[0][2] : "transparent" // Set defaultcolor to transparent if undefined
        }
    }


    Image{
        id: id_telltale_73
        x:34
        y:264
        visible:id_telltales.telltale_pos_73[0][1] === "true"
        source: (id_telltales.telltale_pos_73[0][0] !== undefined) ? id_telltales.telltale_pos_73[0][0] : null

        ColorOverlay{
            anchors.fill: id_telltale_73
            source: id_telltale_73
            color: (id_telltales.telltale_pos_73[0][2] !== undefined) ? id_telltales.telltale_pos_73[0][2] : "transparent" // Set defaultcolor to transparent if undefined
        }
    }


    Image{
        id: id_telltale_74
        x:1834
        y:264
        visible:id_telltales.telltale_pos_74[0][1] === "true"
        source: (id_telltales.telltale_pos_74[0][0] !== undefined) ? id_telltales.telltale_pos_74[0][0] : null

        ColorOverlay{
            anchors.fill: id_telltale_74
            source: id_telltale_74
            color: (id_telltales.telltale_pos_74[0][2] !== undefined) ? id_telltales.telltale_pos_74[0][2] : "transparent" // Set defaultcolor to transparent if undefined
        }
    }
}
