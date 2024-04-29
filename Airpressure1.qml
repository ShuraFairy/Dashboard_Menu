import QtQuick 2.12
import QtQuick.Window 2.1
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12
import "Fonts"
import com.mettem.airpressure1 1.0



Item {
    Qtairpressure1
    {
        objectName: "obj_qtairpressure1"
        id: id_airpressure1
        air_pressure_1: air_pressure_1
    }

    Rectangle {
        id: id_airpressure1_with_needle
        visible: true
        x:111
        y: 523
        width:93
        height:93
        color: "transparent"
        radius:width
        rotation: id_airpressure1.air_pressure_1;
        transitions: Transition {
            RotationAnimation {
                duration: 5
                direction: RotationAnimation.Clockwise
                easing.type: Easing.OutElastic
        }
        }
        Image {
            id: id_airpressure1_needle
            visible: true
            x:45
            y:90
            height: sourceSize.height
            width: sourceSize.width
            source: "pics/IC12_interface_graphics/iC12_small_arrow.png"
            smooth:true;
            Image {
                id: id_airpressure_gradient_increase
                rotation:-22
                x:-10
                y:-20
                visible: id_airpressure1.air_pressure_1 >= 18
                width: 97
                height: 70
                source: "pics/IC12_interface_graphics/iC12_gradient_illumination_air_pressure_left.png"
            }
        }
    }

    Image {
        id: id_airpressure1_img
        visible: true
        x: 111
        y:  523
        width: 93
        height: 93
        source: "pics/IC12_interface_graphics/iC12_tonometer_centr_left.png"
        Text{
            id : id_airpressure1_value
            anchors.centerIn: parent
            visible: true
            x:132 ; y:556
            width: 50 ;
            height: 33 ;
            color: "white"
            text:  ( (id_airpressure1.air_pressure_1 / 18) + 2.0 ).toFixed(1) ;
            FontLoader { id: local_font_airpressure1_val; source: "Fonts/Roboto-Italic.ttf"}
            font { family: local_font_airpressure1_val.name; pixelSize: 30;}
            font.letterSpacing: 1.0
        }
    }

    Text{
        id : id_maxairpressure1_value
        x:96
        y:500
        color: "white"
        text :  "10"
        FontLoader { id: local_font_airpressure1_10; source: "Fonts/Roboto-LightItalic.ttf" }
        font { family: local_font_airpressure1_10.name; pixelSize: 18;}
        font.letterSpacing: 1.0
    }

    Text{
        id : id_minAirpressure1_value
        x:193
        y:620
        color: "white"
        text:  "0"
        FontLoader {
            id:local_font_airpressure1_0;
            source: "Fonts/Roboto-LightItalic.ttf"
        }
        font {
            family: local_font_airpressure1_0.name; pixelSize: 18;
        }
        font.letterSpacing: 1.0
    }
}
