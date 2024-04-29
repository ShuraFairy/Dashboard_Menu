import QtQuick 2.0
import QtQuick.Layouts 1.1
import QtQml 2.0
import "Fonts"
import com.mettem.centraldashboard 1.0


Item {
    property bool gear_visibility: id_dashboard_screen.gear_visibility                           // true
    property int pos0: 0
    property int pos1: 1
    property int pos2: 2
    property int pos3: 3
    property int pos4: 4
    property int pos5: 5
    property int pos6: 6
    property int pos7: 7
    property int pos8: 8


    Qtcentraldashboard
    {
        objectName: "obj_qtcentraldashboard"
        id: id_central_dashboard
        temperature : temperature;
        cabin_temperature1 : cabin_temperature1;
        cabin_temperature2 : cabin_temperature2;
        present_date: present_date;
        present_time: present_time;
        mileage: mileage
        daily_fuel_consumption: daily_fuel_consumption
        trip_distance: trip_distance
        fuel_consumption: fuel_consumption
        engine_coolant_temperature: engine_coolant_temperature
        battery_ampere: battery_ampere
        battery_voltage: battery_voltage
        engine_uom:engine_uom
        speed_uom:speed_uom

        gear_shift: gear_shift
        fuel_level: fuel_level
    }

    Text{
        id : id_fuel_level
        x: 402
        y: 365
        width: 55
        height: 24
        color: {
            if (id_central_dashboard.fuel_level === "-- ") {
                color: "red"
            } else {
                color: "white"
            }
        }
        visible: true
        text:  id_central_dashboard.fuel_level + " %"
        FontLoader { id: local_fuel_level; source: "Fonts/Roboto-LightItalic.ttf" }
        font { family: local_fuel_level.name; pixelSize: 27;}
        font.letterSpacing: 1.0
    }


    Text{
        id : id_Cooltemp_val
        x: 1525
        y: 365
        width: 64
        height: 24
        color: "white"
        visible: true
        text: id_central_dashboard.engine_coolant_temperature[pos0][pos1] + id_central_dashboard.engine_coolant_temperature[pos0][pos2]
        FontLoader { id: localcooltemp; source: "Fonts/Roboto-LightItalic.ttf" }
        font { family: localcooltemp.name; pixelSize: 27;}
        font.letterSpacing: 1.0
    }

    ColumnLayout{
        x: 1525
        y: 416
        spacing:0.1

        Text{
            id : id_battery_voltage
            width: 70
            height: 49
            color: "white"
            visible: true
            text:id_central_dashboard.battery_voltage[pos0][pos1] + id_central_dashboard.battery_voltage[pos0][pos2]
            FontLoader { id: local_voltage; source: "Fonts/Roboto-LightItalic.ttf" }
            font { family: local_voltage.name; pixelSize: 27;}
            font.letterSpacing: 1.0
        }
    }

    Text{
        id : id_enginepeed_uom
        x:1380.0044
        y:538.96
        width:  41
        height:  17
        color: "#4E5C6B"
        text:  id_central_dashboard.engine_uom[pos0][pos2]
        FontLoader { id: local_enginevehuom_font; source: "Fonts/Roboto-LightItalic.ttf" }
        font { family: local_enginevehuom_font.name; pixelSize: 18;}
        font.letterSpacing: 1.0
    }

    Text{
        id : id_enginepeed_uom_power_minus_1
        x:1464.0044
        y:533.96
        width:  5
        height:  10
        color: "#4E5C6B"
        text:  "- 1"
        FontLoader { id: local_enginevehuom_power_minus1_font; source: "Fonts/Roboto-LightItalic.ttf" }
        font { family: local_enginevehuom_power_minus1_font.name; pixelSize: 12;}
        font.letterSpacing: 1.0
    }

    Text{
        id : id_vehicle_speeduom
        x:490
        y:539;
        width: 41
        height: 17
        color: "#4E5C6B"
        text:  id_central_dashboard.speed_uom[pos0][pos2]
        FontLoader { id: local_vehspeed_fontvehuom; source: "Fonts/Roboto-LightItalic.ttf" }
        font { family: local_vehspeed_fontvehuom.name; pixelSize: 18;}
        font.letterSpacing: 1.0
    }

    Text{
        id : id_airpressure1_uom
        x:143
        y:585
        width: 55
        height: 24
        color: "white"
        text:  id_central_dashboard.pressure_uom[pos0][pos2]
        FontLoader {
            id:local_font_airpressure1_uom;
            source: "Fonts/Roboto-LightItalic.ttf"
        }
        font {
            family: local_font_airpressure1_uom.name; pixelSize: 19;
        }
        font.letterSpacing: 1.0
    }

    Text{
        id : id_airpressure2_uom
        x:1748
        y:585
        height: 24
        width: 55
        color: "white"
        text:  id_central_dashboard.pressure_uom[pos0][pos2]
        FontLoader {
            id:local_font_airpressure2_uom;
            source: "Fonts/Roboto-LightItalic.ttf"
        }
        font {
            family: local_font_airpressure2_uom.name; pixelSize: 19;
        }
        font.letterSpacing: 1.0
    }

    Image {
        id: id_letter_r
        visible: gear_visibility   //true
        x:907
        y:614
        width: 31
        height: 28
        source: {
            if(id_central_dashboard.gear_shift < 0){
                return "pics/IC12_interface_graphics/iC12_reverse_on.png"
            } else{
                return "pics/IC12_interface_graphics/iC12_reverse_off.png"
            }
        }
    }

    Image {
        id: id_letter_r_illumination
        x:885
        y:650
        visible:id_central_dashboard.gear_shift < 0 && gear_visibility
        width: sourceSize.width
        height: sourceSize.height
        source: "pics/IC12_interface_graphics/iC12_selector_illumination.png"
    }

    Image {
        id: id_letter_n
        visible:gear_visibility   //true
        x:957
        y:614
        width: 33
        height: 27
        source: {
            if(id_central_dashboard.gear_shift == 0){
                return "pics/IC12_interface_graphics/iC12_neutral_on.png"
            } else{
                return "pics/IC12_interface_graphics/iC12_neutral_off.png"
            }
        }
    }

    Image {
        id: id_letter_n_illumination
        x:937
        y:650
        visible:id_central_dashboard.gear_shift == 0 && gear_visibility
        width: sourceSize.width
        height: sourceSize.height
        source: "pics/IC12_interface_graphics/iC12_selector_illumination.png"
    }

    Image {
        id: id_letter_d
        visible:gear_visibility    //true
        x:1010
        y:614
        width: 30
        height: 28
        source: {
            if(id_central_dashboard.gear_shift > 0){
                return "pics/IC12_interface_graphics/iC12_drive_on.png"
            } else{
                return "pics/IC12_interface_graphics/iC12_drive_off.png"
            }
        }
    }


    Image {
        id: id_letter_d_illumination
        x:988
        y:650
        visible: id_central_dashboard.gear_shift > 0 && gear_visibility
        width:   sourceSize.width
        height: sourceSize.height
        source: "pics/IC12_interface_graphics/iC12_selector_illumination.png"
    }

    Text {
        id : id_presentdate
        x:660
        y:207
        width: 96
        height: 22
        color: "white"
        text:  id_central_dashboard.present_date
        FontLoader { id: local_font_date; source: "Fonts/Roboto-Italic.ttf" }
        font { family: local_font_date.name; pixelSize: 26;}
        font.letterSpacing: 1.0
    }
    Text {
        id : id_presenttime
        x:800
        y:207
        width: 58
        height: 22
        color: "white"
        text:  id_central_dashboard.present_time
        FontLoader { id: local_Font_time; source: "Fonts/Roboto-Italic.ttf" }
        font { family: local_Font_time.name; pixelSize: 26;}
        font.letterSpacing: 1.0
    }
    Image {
        id: id_weather
        x:894
        y:207
        source: "pics/IC12_interface_graphics/Icon_1.png"
    }
    Text {
        id : id_temperature
        x:947
        y:207
        width: 57
        height: 22
        color: "white"
        text:  id_central_dashboard.temperature + "°C"
        FontLoader { id: local_font_temp; source: "Fonts/Roboto-Italic.ttf" }
        font { family: local_font_temp.name; pixelSize: 26;}
        font.letterSpacing: 1.0
    }
    Image {
        id: id_rearbus
        x:1028
        y:212
        source: "pics/IC12_interface_graphics/Icon_2.png"
    }
    Text {
        id : id_cabintemp1
        x:1078
        y:207
        width: 58
        height: 22
        color: "white"
        text:  id_central_dashboard.cabin_temperature1 + "°C"
        FontLoader { id: local_font_cabtemp1; source: "Fonts/Roboto-Italic.ttf" }
        font { family: local_font_cabtemp1.name; pixelSize: 26;}
        font.letterSpacing: 1.0
    }
    Image {
        id: id_frontbus
        x:1160
        y:212
        source: "pics/IC12_interface_graphics/Icon_3.png"
    }
    Text {
        id : id_cabintemp2
        x:1213
        y:207
        width: 58
        height: 22
        color: "white"
        text: id_central_dashboard.cabin_temperature2 + "°C"
        FontLoader { id: local_font_cabtemp2; source: "Fonts/Roboto-Italic.ttf" }
        font { family: local_font_cabtemp2.name; pixelSize: 26;}
        font.letterSpacing: 1.0
    }


    Rectangle{
        id: id_mileage_header
        height: 50
        width: 200
        visible: true
        color: "transparent"
        x: 396
        y: 650
        Row {
            anchors.centerIn: parent
            Text {
                text: id_central_dashboard.mileage[pos0][pos0]
                color: "#4E5C6B"
                wrapMode: Text.WordWrap
                FontLoader { id: mileage_name_font; source: "Fonts/Roboto-Italic.ttf" }
                font { family: mileage_name_font.name; pixelSize: 20;}
                font.letterSpacing: 1.0
            }
            Text {
                color: "#4E5C6B"
                text: ":  "
                FontLoader { id: seperator_font; source: "Fonts/Roboto-Italic.ttf" }
                font { family: seperator_font.name; pixelSize: 20;}
                font.letterSpacing: 1.0
            }
            Text {
                text: id_central_dashboard.mileage[pos0][pos1] + " "
                color: "#4E5C6B"
                wrapMode: Text.WordWrap
                FontLoader { id: mileage_value_font; source: "Fonts/Roboto-Italic.ttf" }
                font { family: mileage_value_font.name; pixelSize: 20;}
                font.letterSpacing: 1.0
            }
            Text {
                text: id_central_dashboard.mileage[pos0][pos2]
                color: "#4E5C6B"
                wrapMode: Text.WordWrap
                FontLoader { id: mileage_uom_fontfont; source: "Fonts/Roboto-Italic.ttf" }
                font { family: mileage_uom_fontfont.name; pixelSize: 20;}
                font.letterSpacing: 1.0
            }
        }
    }

    Rectangle{
        id: id_daily_fuel_consumption_header
        height: 50
        width: 200
        visible: true
        color: "transparent"
        x:849
        y:650
        Row {
            anchors.centerIn: parent
            Text {
                text: id_central_dashboard.daily_fuel_consumption[pos0][pos0]
                color: "#4E5C6B"
                wrapMode: Text.WordWrap
                FontLoader { id: daily_fuel_consumption_name_font; source: "Fonts/Roboto-Italic.ttf" }
                font { family: daily_fuel_consumption_name_font.name; pixelSize: 20;}
                font.letterSpacing: 1.0
            }
            Text {
                color: "#4E5C6B"
                text: ":  "
                FontLoader { id: daily_fuel_consumption_seperator_font; source: "Fonts/Roboto-Italic.ttf" }
                font { family: daily_fuel_consumption_seperator_font.name; pixelSize: 20;}
                font.letterSpacing: 1.0
            }
            Text {
                text: id_central_dashboard.daily_fuel_consumption[pos0][pos1] + " "
                color: "#4E5C6B"
                wrapMode: Text.WordWrap
                FontLoader { id: daily_fuel_consumption_value_font; source: "Fonts/Roboto-Italic.ttf" }
                font { family: daily_fuel_consumption_value_font.name; pixelSize: 20;}
                font.letterSpacing: 1.0
            }
            Text {
                text: id_central_dashboard.daily_fuel_consumption[pos0][pos2]
                color: "#4E5C6B"
                wrapMode: Text.WordWrap
                FontLoader { id: daily_fuel_consumption_uom_fontfont; source: "Fonts/Roboto-Italic.ttf" }
                font { family: daily_fuel_consumption_uom_fontfont.name; pixelSize: 20;}
                font.letterSpacing: 1.0
            }
        }
    }

    Rectangle{
        id: id_trip_distance_header
        height: 50
        width: 200
        visible: true
        color: "transparent"
        x:1254
        y:650
        Row {
            anchors.centerIn: parent
            Text {
                text: id_central_dashboard.trip_distance[pos0][pos0]
                color: "#4E5C6B"
                wrapMode: Text.WordWrap
                FontLoader { id: daily_mileage_name_font; source: "Fonts/Roboto-Italic.ttf" }
                font { family: daily_mileage_name_font.name; pixelSize: 20;}
                font.letterSpacing: 1.0
            }
            Text {
                color: "#4E5C6B"
                text: ":  "
                FontLoader { id: daily_mileage_seperator_font; source: "Fonts/Roboto-Italic.ttf" }
                font { family: daily_mileage_seperator_font.name; pixelSize: 20;}
                font.letterSpacing: 1.0
            }
            Text {
                text: id_central_dashboard.trip_distance[pos0][pos1] + " "
                color: "#4E5C6B"
                wrapMode: Text.WordWrap
                FontLoader { id: daily_mileage_value_font; source: "Fonts/Roboto-Italic.ttf" }
                font { family: daily_mileage_value_font.name; pixelSize: 20;}
                font.letterSpacing: 1.0
            }
            Text {
                text: id_central_dashboard.trip_distance[pos0][pos2]
                color: "#4E5C6B"
                wrapMode: Text.WordWrap
                FontLoader { id: daily_mileage_uom_fontfont; source: "Fonts/Roboto-Italic.ttf" }
                font { family: daily_mileage_uom_fontfont.name; pixelSize: 20;}
                font.letterSpacing: 1.0
            }
        }
    }

}
