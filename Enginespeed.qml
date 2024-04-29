import QtQuick 2.12
import QtQuick.Window 2.1
import QtQuick.Controls 2.12
import com.mettem.enginemeter 1.0
import QtQuick.Controls.Styles 1.4
import QtQuick.Extras 1.4

Item {
    id : id_enginemeter_screen
    Qtenginemeter
    {
        objectName: "obj_qtenginemeter"
        id: id_enginemeter
        engine_speed: engine_speed
    }

    CircularGauge {
        id:id_engine_speed_gauge
        width: 548
        height: 548
        x:1250
        y:97
        maximumValue: 35
        value: id_enginemeter.engine_speed.toFixed(0)/100

        style: EngineSpeedGaugeStyle {
            id:id_big_gauge_style
            gradient_illumination:id_engine_speed_gauge.value>6
        }

        Component.onCompleted: forceActiveFocus()
    }

    Text{
        id : id_engine_speed_value
        x:1481
        y:269
        width:  85
        height:  83
        visible: true
        text:  id_enginemeter.engine_speed.toFixed(0)

        color: {
            if(id_enginemeter.engine_speed > 3500)
                return "red"
            else
                return "white"
        }

        horizontalAlignment: Text.AlignHCenter
        FontLoader { id: local_engspeed_font; source: "Fonts/Roboto-Italic.ttf" }
        font { family: local_engspeed_font.name; pixelSize: 77;}
        font.letterSpacing: 1.0
    }
}
