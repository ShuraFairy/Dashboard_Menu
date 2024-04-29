import QtQuick 2.12
import QtQuick.Window 2.1
import QtQuick.Controls 2.12
import com.mettem.airpressure2 1.0

Item {    
    Qtairpressure2
    {
        objectName: "obj_qtairpressure2"
        id: id_airpressure2
        air_pressure_2: air_pressure_2
    }
    Rectangle {
        id: id_airpressure2_with_needle
        x: 1810
        y:523
        width:93
        height:93
        color: "transparent"
        radius:width
        rotation: id_airpressure2.air_pressure_2
        transform: [Scale {xScale: -1}]
        transitions: Transition {
            RotationAnimation {
                duration: 5
                direction: RotationAnimation.Counterclockwise
                easing.type: Easing.OutElastic
        }
        }
        Image {
            id: id_airpressure2_needle
            visible: true
            x:45
            y:90
            height: sourceSize.height
            width : sourceSize.width
            source: "pics/IC12_interface_graphics/iC12_small_arrow.png"
            smooth:true;
            Image {
                id: id_airpressure_gradient_increase
                transform: [Scale {xScale: -1}]
                rotation:20
                x:87
                y:-20
                visible: id_airpressure2.air_pressure_2 >= 18
                width: 97
                height: 70
                source: "pics/IC12_interface_graphics/iC12_gradient_illumination_air_pressure_right.png"
            }
        }
    }

    Image {
        id: id_airpressure2_img
        visible: true
        x: 1716
        y:523
        width:  93
        height: 93
        source: "pics/IC12_interface_graphics/iC12_tonometer_centr_right.png"

    }
    Text{
        id : id_airpressure2_value
        visible: true
        x:1738
        y:554
        width:  50
        height:  33
        color: "white"
        text:  ( (id_airpressure2.air_pressure_2 / 18 ) + 2.0 ).toFixed(1) ;
        FontLoader { id: local_font_airpressure2_val; source: "Fonts/Roboto-Italic.ttf" }
        font { family: local_font_airpressure2_val.name; pixelSize: 30;}
        font.letterSpacing: 1.0
    }

    Text{
        id : id_maxairpressure2_value
        x:1804
        y:505
        color: "white"
        text :  "10"
        FontLoader { id: local_font_airpressure2_10; source: "Fonts/Roboto-LightItalic.ttf" }
        font { family: local_font_airpressure2_10.name; pixelSize: 18;}
        font.letterSpacing: 1.0
    }

    Text{
        id : id_minairpressure2_value
        x:1709
        y:621
        color: "white"
        text:  "0"
        FontLoader {
            id:local_font_airpressure2_0;
            source: "Fonts/Roboto-LightItalic.ttf"
        }
        font {
            family: local_font_airpressure2_0.name; pixelSize: 18;
        }
        font.letterSpacing: 1.0
    }
}
