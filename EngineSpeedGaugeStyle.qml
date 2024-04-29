import QtQuick 2.0
import QtQuick.Controls.Styles 1.4
import QtQuick.Extras 1.4


CircularGaugeStyle{

    id:id_gauge_style
    labelStepSize:5
    minimumValueAngle: 180
    maximumValueAngle: -30
    property bool gradient_illumination: false
    needle: Item {
        id: id_item_needle
        y: -outerRadius*0.7
        antialiasing: true

        Image {
           id: id_needle
           anchors.centerIn: parent
           source: "pics/IC12_interface_graphics/iC12_big_arrow.png"
           rotation: 180
        }
        Image {
            id: id_gradient_illumination
            y:-58
            rotation:-180
            visible: gradient_illumination
            source: "pics/IC12_interface_graphics/gradient_illumination.png"
        }
    }

    background:Rectangle {
        id:id_background
        color: "transparent"
        Image {
            id:id_gauge_background
            source: "pics/IC12_interface_graphics/iC12_speedometr_centr.png"
            x:id_background.width/2 - id_gauge_background.width/2
            y:id_background.height/2 - id_gauge_background.height/2

        }
    }

    foreground: Item {
        Rectangle {
            visible: false
        }
    }

    tickmarkLabel: Text {
        FontLoader { id: local_vehspeed_font140; source: "Fonts/Roboto-LightItalic.ttf" }
        font { family: local_vehspeed_font140.name; pixelSize: 35;}
        text: styleData.value
        color: "white"
        antialiasing: true
        }

    minorTickmark: Rectangle {
        visible: true
    }

    tickmark: Rectangle {
        visible: true
    }


}
