import QtQuick 2.0
import QtQuick.Controls 2.12

Item {
    id : id_menu_services_dialog
    property int i : 0
    property string password_first_digit: "0"
    property string password_second_digit: "0"
    property string password_third_digit: "0"
    property string password_fourth_digit: "0"

    property string password_first_digit_visible: "*"
    property string password_second_digit_visible: "*"
    property string password_third_digit_visible: "*"
    property string password_fourth_digit_visible: "*"

    property int password_position:0
    property int password_individual_value :0
    property bool pwd_incorrect_status: false

    function services_popup_handler(){
        id_menu_services_dialog.i++
        if(id_menu_services_dialog.i === 1){
            id_menuconfig.services_popup_active = true
            if (screen_name === "SERVICES_DIALOG" && services_popup_active === true
                    && password_validity === false){
                if(id_mainmenu.button_click === "DOWN"){
                    password_individual_value--
                    if(password_individual_value < 0){
                        password_individual_value = 9
                    }
                }
                else if (id_mainmenu.button_click === "UP"){
                    password_individual_value++
                    if(password_individual_value > 9){
                        password_individual_value = 0
                    }
                } else if (id_mainmenu.button_click === "RIGHT"){
                    password_position++
                    if(password_position >= 3){
                        password_position = 3
                        password_individual_value = 0
                    } else {
                        password_individual_value = 0
                    }
                } else if (id_mainmenu.button_click === "LEFT"){
                    password_position--
                    if(password_position <= 0){
                        password_position = 0
                        password_individual_value = 0
                    } else {
                        password_individual_value = 0
                    }
                }
                switch (password_position) {
                case 0:
                    password_first_digit = password_individual_value.toString()
                    password_first_digit_visible =  password_first_digit
                    password_second_digit_visible = "*"
                    password_third_digit_visible = "*"
                    password_fourth_digit_visible = "*"
                    break;
                case 1:
                    password_second_digit = password_individual_value.toString()
                    password_first_digit_visible =  "*"
                    password_second_digit_visible = password_second_digit
                    password_third_digit_visible = "*"
                    password_fourth_digit_visible = "*"
                    break;
                case 2:
                    password_third_digit = password_individual_value.toString()
                    password_first_digit_visible =  "*"
                    password_second_digit_visible = "*"
                    password_third_digit_visible = password_third_digit
                    password_fourth_digit_visible = "*"
                    break;
                case 3:
                    password_fourth_digit  = password_individual_value.toString()
                    password_first_digit_visible =  "*"
                    password_second_digit_visible = "*"
                    password_third_digit_visible = "*"
                    password_fourth_digit_visible = password_fourth_digit
                    break;
                default:
                    console.log("Invalid option");
                    break;
                }
            }
        }
        if(id_menu_services_dialog.i === 2){
            id_menu_services_dialog.i = 0
        }
    }

    function password_incorrect_handler(){
        seqAnimation.start()
        pwd_incorrect_status = true
    }

    Rectangle{
        id: id_services_popup
        x:33.5
        y:145
        width: 1853
        height: 500
        color: "transparent"
        visible: true
        Image {
            id: id_password_layer
            anchors.fill: parent
            width: id_services_popup.width
            height: id_services_popup.height
            source: "pics/Menu/Layer_1.png"
            visible: true
        }

        Text {
            id: id_enter_password_text
            y: 150
            anchors.horizontalCenter: parent.horizontalCenter
            text: id_mainmenu.menu_services_password_data[pos0][pos0]
            color: "white"
            visible: true
            FontLoader { id: enter_password_text_right_font; source: "Fonts/Roboto-Italic.ttf" }
            font { family: enter_password_text_right_font.name; pixelSize: 37;}
            font.letterSpacing: 1.0
        }

        Rectangle{
            id: id_shake_rectangle
            width: 500
            height: 100 //250
            color: "transparent"
            x:677
            y:200
            visible: true
            Grid {
                anchors.centerIn: parent
                y:id_password_layer.y + 100
                columns: 4
                spacing: 20
                Rectangle {
                    id: id_password_first_rect
                    visible:true
                    color: "transparent"
                    width: 40
                    height: 40
                    Text {
                        id: id_password_first_text
                        anchors.centerIn: parent
                        color: {
                            if(pwd_incorrect_status === true){
                                color: "red"
                            } else if(password_first_digit_visible >=0 && password_first_digit_visible <= 9) {
                                color: "#21B1D0"
                            }else if(password_first_digit_visible === "*"){
                                color: "white"
                            }
                        }

                        font.pixelSize: {
                            switch (id_password_first_text.color){
                            case "red":
                                return 87;
                            case "#21B1D0":
                                return 68;
                            case "white":
                                return 87
                            default:
                                return 68
                            }
                        }

                        text: {
                            if(pwd_incorrect_status === true){
                                text: "*"
                            } else {
                                text: password_first_digit_visible
                            }
                        }
                        FontLoader { id: firstdigit_text_font; source: "Fonts/Roboto-Italic.ttf" }
                        font { family: firstdigit_text_font.name;pixelSize: 87}
                        font.letterSpacing: 1.0
                    }
                }
                Rectangle {
                    id: id_password_second_rect
                    visible:true
                    width: 40
                    height: 40
                    color: "transparent"
                    Text {
                        id: id_password_second_text
                        anchors.centerIn: parent
                        color: {
                            if(pwd_incorrect_status === true){
                                color: "red"
                            } else if(password_second_digit_visible >=0 && password_second_digit_visible <= 9) {
                                color: "#21B1D0"
                            }else if(password_second_digit_visible === "*"){
                                color: "white"
                            }
                        }
                        font.pixelSize: {
                            switch (id_password_second_text.color){
                            case "red":
                                return 87;
                            case "#21B1D0":
                                return 68;
                            case "white":
                                return 87
                            default:
                                return 68
                            }
                        }

                        text: {
                            if(pwd_incorrect_status === true){
                                text: "*"
                            } else {
                                text: password_second_digit_visible
                            }
                        }
                        FontLoader { id: seconddigit_text_font; source: "Fonts/Roboto-Italic.ttf" }
                        font { family: seconddigit_text_font.name}
                        font.letterSpacing: 1.0
                    }
                }
                Rectangle {
                    id: id_password_third_rect
                    visible:true
                    width: 40
                    height: 40
                    color: "transparent"
                    Text {
                        id: id_password_third_text
                        anchors.centerIn: parent
                        color: {
                            if(pwd_incorrect_status === true){
                                color: "red"
                            } else if(password_third_digit_visible >=0 && password_third_digit_visible <= 9) {
                                color: "#21B1D0"
                            }else if(password_third_digit_visible === "*"){
                                color: "white"
                            }
                        }

                        font.pixelSize: {
                            switch (id_password_third_text.color){
                            case "red":
                                return 87;
                            case "#21B1D0":
                                return 68;
                            case "white":
                                return 87
                            default:
                                return 68
                            }
                        }

                        text: {
                            if(pwd_incorrect_status === true){
                                text: "*"
                            } else {
                                text: password_third_digit_visible
                            }
                        }
                        FontLoader { id: third_digit_text_font; source: "Fonts/Roboto-Italic.ttf" }
                        font { family: third_digit_text_font.name}
                        font.letterSpacing: 1.0
                    }
                }
                Rectangle {
                    id: id_password_forth_rect
                    visible:true
                    width: 40
                    height: 40
                    color: "transparent"
                    Text {
                        id: id_password_fourth_text
                        anchors.centerIn: parent
                        color: {
                            if(pwd_incorrect_status === true){
                                color: "red"
                            } else if(password_fourth_digit_visible >=0 && password_fourth_digit_visible <= 9) {
                                color: "#21B1D0"
                            }else if(password_fourth_digit_visible === "*"){
                                color: "white"
                            }
                        }

                        font.pixelSize: {
                            switch (id_password_fourth_text.color){
                            case "red":
                                return 87;
                            case "#21B1D0":
                                return 68;
                            case "white":
                                return 87
                            default:
                                return 68
                            }
                        }

                        text: {
                            if(pwd_incorrect_status === true){
                                text: "*"
                            } else {
                                text: password_fourth_digit_visible
                            }
                        }
                        FontLoader { id: fourth_digit_text_font; source: "Fonts/Roboto-Italic.ttf" }
                        font { family: fourth_digit_text_font.name}
                        font.letterSpacing: 1.0
                    }
                }
            }
        }


    }

    SequentialAnimation {
        id: seqAnimation
        running: false
        loops: 2
        PropertyAnimation {
            target: id_shake_rectangle
            property: "x"
            to: 707
            duration: 100
            easing.type: Easing.InOutQuad

        }
        PropertyAnimation {
            target: id_shake_rectangle
            property: "x"
            to: 677
            duration: 100
            easing.type: Easing.InOutQuad
        }
        onStopped: {
            pwd_incorrect_status = false
        }
    }
}
