import QtQuick 2.12
import QtQuick.Window 2.1
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.12
import "Fonts"
import com.mettem.speedometer 1.0


Item 
{
    id: id_speedometer_screen
    Qtspeedometer
    {
        objectName: "obj_qtspeeodmeter"
        id: id_speedometer
        speed: speed
    }

Rectangle 
{
        id: id_speedometer_center_needle
        x:266
        y:238
        width: 260
        height: 260
        color: "transparent"
        radius:width
        rotation : id_speedometer.speed * 1.5
        transitions:  Transition 
        {
            RotationAnimation 
            {
                duration: 5
                direction: RotationAnimation.Clockwise
                easing.type: Easing.OutElastic
            }
        }
        Image
        {
            id: id_speedometer_needle
            x:111
            y:263
            height: sourceSize.height - 10
            source: "pics/IC12_interface_graphics/iC12_big_arrow.png"
            Image 
            {
                id: id_speedometer_gradient_increase
                rotation:-30
                x:-5
                y:-20
                visible: id_speedometer.speed * 1.5 >= 30
                width: 255
                height: 116
                source: "pics/IC12_interface_graphics/iC12_gradient_illumination_speedometr(2).png"
            }
        }
    }

    Image {
        id: id_speedometer_center
        x: 266
        y:  238
        width: 260
        height: 260
        source: "pics/IC12_interface_graphics/iC12_speedometr_centr.png"
    }

    Text{
        id : id_vehicle_speed_value
        x:348
        y:269
        width:101
        height: 83
        color: "white"
        visible: true
        horizontalAlignment: Text.AlignHCenter
        text:  (id_speedometer.speed).toFixed(0);
        FontLoader { id: local_vehspeed_font; source: "Fonts/Roboto-Italic.ttf" }
        font { family: local_vehspeed_font.name; pixelSize: 77;}
        font.letterSpacing: 1.0
    }


    Text{
        id : id_vehicle_speed_text0
        x: 380
        y: 580
        color: "white"
        FontLoader { id: local_vehspeed_font0; source: "Fonts/Roboto-LightItalic.ttf" }
        font { family: local_vehspeed_font0.name; pixelSize: 35;}
        font.letterSpacing: 1.0
        text:  "0"
    }

    Text{
        id : id_vehicle_speed_text20
        x:258
        y: 540
        color: "white"
        FontLoader { id: local_vehspeed_font20; source: "Fonts/Roboto-LightItalic.ttf" }
        font { family: local_vehspeed_font20.name; pixelSize: 35;}
        font.letterSpacing: 1.0
        text:  "20"
    }

    Text{
        id : id_vehicle_speed_text40
        x:190
        y:460
        color: "white"
        FontLoader { id: local_vehspeed_font40; source: "Fonts/Roboto-LightItalic.ttf" }
        font { family: local_vehspeed_font40.name; pixelSize: 35;}
        font.letterSpacing: 1.0
        text:  "40"
    }

    Text{
        id : id_vehicle_speed_text60
        x:150
        y:345
        color: "white"
        FontLoader { id: local_vehspeedfont60; source: "Fonts/Roboto-LightItalic.ttf" }
        font { family: local_vehspeedfont60.name; pixelSize: 35;}
        font.letterSpacing: 1.0
        text:  "60"
    }

    Text{
        id : id_vehicle_speed_text80
        x:185
        y:230
        color: "white"
        FontLoader { id: local_vehspeed_font80; source: "Fonts/Roboto-LightItalic.ttf" }
        font { family: local_vehspeed_font80.name; pixelSize: 35;}
        font.letterSpacing: 1.0
        text:  "80"
    }

    Text{
        id : id_vehicle_speed_text100
        x:260
        y:150
        color: "white"
        FontLoader { id: local_vehspeed_font100; source: "Fonts/Roboto-LightItalic.ttf" }
        font { family: local_vehspeed_font100.name; pixelSize: 35;}
        font.letterSpacing: 1.0
        text:  "100"
    }

    Text{
        id : id_vehicle_speed_text120
        x:370
        y:120
        color: "white"
        FontLoader { id: local_vehspeed_font120; source: "Fonts/Roboto-LightItalic.ttf" }
        font { family: local_vehspeed_font120.name; pixelSize: 35;}
        font.letterSpacing: 1.0
        text:  "120"
    }

    Text{
        id : id_vehicle_speed_text140
        x:495
        y:148
        color: "white"
        FontLoader { id: local_vehspeed_font140; source: "Fonts/Roboto-LightItalic.ttf" }
        font { family: local_vehspeed_font140.name; pixelSize: 35;}
        font.letterSpacing: 1.0
        text:  "140"
    }


}
