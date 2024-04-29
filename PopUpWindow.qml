import QtQuick 2.9
import QtQuick.Layouts 1.12
import com.mettem.popupwindow 1.0
import QtMultimedia 5.6
import QtGraphicalEffects 1.12


Item {
    Qtpopupwindow{
        objectName: "obj_qtpopupwindow"
        id: id_popups
        popup_state: popup_state;
        static_popup_text: static_popup_text
    }
    Repeater{
        model: id_popups.static_popup_text
            Image{
                x:565
                y:224
                z:modelData[2]
                visible:id_popups.popup_state[index]
                source: "pics/IC12_interface_graphics/popup.png"
                Text {
                    anchors.centerIn: parent
                    text:  qsTr(modelData[0])
                    color: modelData[1]
                    FontLoader { id: popup_font; source: "Fonts/Roboto-Italic.ttf" }
                    font { family: popup_font.name; pixelSize: 35;}
                    font.letterSpacing: 1.0
                }
            }
    }
}
