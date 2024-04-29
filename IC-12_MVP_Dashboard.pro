QT += quick
QT += multimedia
QT += qml quick

CONFIG += c++17

QMAKE_CXXFLAGS += -std=c++17

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += lib/mt_dsp/include

SOURCES += \
        Business_Logic/Common/hmi_config.cpp \
    Business_Logic/Common/j1939_config.cpp \
    Business_Logic/Connectivity/JSON/qtjsonconfiguredata.cpp \
    Business_Logic/Connectivity/JSON/qtjsonhandler.cpp \
    Business_Logic/Connectivity/JSON/qtjsonmenuhandler.cpp \
    Business_Logic/Connectivity/JSON/qtjsonpopuphandler.cpp \
        Business_Logic/Connectivity/can_handler.cpp \
        Business_Logic/Connectivity/hmi_handler.cpp \
    Business_Logic/Connectivity/j1939_data_handler.cpp \
    Business_Logic/Connectivity/pwmchannel.cpp \
    Business_Logic/Logger/error_tracing.cpp \
    Business_Logic/Logger/exception_define.cpp \
        Business_Logic/Logger/logger.cpp \
    Business_Logic/Menu/menu_diagnostics_handler.cpp \
    Business_Logic/Menu/menu_handler.cpp \
    Business_Logic/Menu/menu_services_handler.cpp \
    Business_Logic/Menu/menu_settings_handler.cpp \
    Business_Logic/Menu/newmenuitems.cpp \
        Business_Logic/Qt_Framework/qtairpressure1.cpp \
        Business_Logic/Qt_Framework/qtairpressure2.cpp \
        Business_Logic/Qt_Framework/qtapphandler.cpp \
        Business_Logic/Qt_Framework/qtcentraldashboard.cpp \
        Business_Logic/Qt_Framework/qtenginemeter.cpp \
        Business_Logic/Qt_Framework/qtmenuops.cpp \
        Business_Logic/Qt_Framework/qtpopup.cpp \
        Business_Logic/Qt_Framework/qtpwmcontrol.cpp \
        Business_Logic/Qt_Framework/qtspeedometer.cpp \
        Business_Logic/Qt_Framework/qttelltales.cpp \
        Business_Logic/Qt_Framework/qtzummerhandler.cpp \
    Business_Logic/navigation.cpp \
    Business_Logic/playlistfactory.cpp \
        Business_Logic/playlisthandlerwav.cpp \
        Business_Logic/playlistwav.cpp \
    Business_Logic/sound_handler.cpp \
    Business_Logic/soundplaylist.cpp \
    Business_Logic/subscribe_notifer.cpp \
        lib/mt_dsp/mt_dsp_median.c \
        lib/mt_dsp/mt_dsp_mavg.c \
        main.cpp \

RESOURCES += qml.qrc

TRANSLATIONS += \
#    IC-12_MVP_Dashboard_en_US.ts \
    Translator/menu_ru.ts

system(lrelease \"$$_PRO_FILE_\")

#tr.commands = lupdate \"$$_PRO_FILE_\" && lrelease \"$$_PRO_FILE_\"
#    PRE_TARGETDEPS += tr
#    QMAKE_EXTRA_TARGETS += tr
# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    AirPressure1.qml \
    AirPressure2.qml \
    Airpressure1.qml \
    Airpressure2.qml \
    Bus.qml \
    CentralDashboard.qml \
    Centraldashboard.qml \
    Dashboard.qml \
    Diagnostics.qml \
    EngineSpeedGaugeStyle.qml \
    Enginespeed.qml \
    Fonts/Roboto-Italic.ttf \
    Fonts/Roboto-Light.ttf \
    Fonts/Roboto-LightItalic.ttf \
    IC-12_MVP_Dashboard_en_US.qm \
    Json/config_data.json \
    Json/menu-items.json \
    Json/menu_items_3.json \
    Json/pop_up.json \
    Json/tell-tales.json \
    MainMenu.qml \
    MainMenuWindow.qml \
    MenuDiagnosticsDoorSensor.qml \
    MenuDiagnosticsDoorValve.qml \
    MenuDiagnosticsEmergencyCrane.qml \
    MenuDiagnosticsEmergencyHammers.qml \
    MenuDiagnosticsFireExtinguishers.qml \
    MenuDiagnosticsHeaters.qml \
    MenuDiagnosticsHeatingSystemValves.qml \
    MenuParameters.qml \
    MenuParametersBrakepads.qml \
    MenuParametersEngine.qml \
    MenuParametersTyrePressTemp.qml \
    MenuServicesDialog.qml \
    PopUpWindow.qml \
    README.md \
    Sounds/001_MVP12_Snd.wav \
    Sounds/002_MVP12_Snd.wav \
    Sounds/003_MVP12_Snd.wav \
    Sounds/004_MVP12_Snd.wav \
    Sounds/005_MVP12_Snd.wav \
    Sounds/006_MVP12_Snd.wav \
    Sounds/Sound_license.txt \
    Speedneedle.qml \
    EngineSpeed.qml \
    Speedometers.qml \
    Telltale.qml \
    Telltales.qml \
    Translator/menu_ru.qm \
    Translator/menu_ru.ts \
    build.sh \
    main.qml \
    password_data.txt \
    pics/Graphics/Description.docx \
    pics/Graphics/Layer0/Layer0.png \
    pics/Graphics/Layer1/Layer1.png \
    pics/Graphics/Layer10/Layer10_Door1_Close.png \
    pics/Graphics/Layer10/Layer10_Door2_Close.png \
    pics/Graphics/Layer10/Layer10_Door3_Close.png \
    pics/Graphics/Layer11/Layer11_Door1_OpenReq.png \
    pics/Graphics/Layer11/Layer11_Door2_OpenReq.png \
    pics/Graphics/Layer11/Layer11_Door3_OpenReq.png \
    pics/Graphics/Layer12/Layer12_Door1_Opening_LeftPart.png \
    pics/Graphics/Layer12/Layer12_Door1_Opening_RightPart.png \
    pics/Graphics/Layer12/Layer12_Door2_Opening_LeftPart.png \
    pics/Graphics/Layer12/Layer12_Door2_Opening_RightPart.png \
    pics/Graphics/Layer12/Layer12_Door3_Opening_LeftPart.png \
    pics/Graphics/Layer12/Layer12_Door3_Opening_RightPart.png \
    pics/Graphics/Layer13/Layer13_Door1_Open.png \
    pics/Graphics/Layer13/Layer13_Door2_Open.png \
    pics/Graphics/Layer13/Layer13_Door3_Open.png \
    pics/Graphics/Layer14/Layer14_Door1_PassengerPinching.png \
    pics/Graphics/Layer14/Layer14_Door2_PassengerPinching.png \
    pics/Graphics/Layer14/Layer14_Door3_PassengerPinching.png \
    pics/Graphics/Layer15/Layer15_Door1_UnauthorizedOpening.png \
    pics/Graphics/Layer15/Layer15_Door2_UnauthorizedOpening.png \
    pics/Graphics/Layer15/Layer15_Door3_UnauthorizedOpening.png \
    pics/Graphics/Layer16/Layer16_Door1_WorningDoor.png \
    pics/Graphics/Layer16/Layer16_Door2_WorningDoor.png \
    pics/Graphics/Layer16/Layer16_Door3_WorningDoor.png \
    pics/Graphics/Layer2/Layer2_Part1.png \
    pics/Graphics/Layer2/Layer2_Part2.png \
    pics/Graphics/Layer4/Layer4.png \
    pics/Graphics/Layer5/Layer5_ EngineSpeedScale.png \
    pics/Graphics/Layer5/Layer5_ EngineSpeedScale.png \
    pics/Graphics/Layer5/Layer5_ VehicleSpeedScale.png \
    pics/Graphics/Layer5/Layer5_ VehicleSpeedScale.png \
    pics/Graphics/Layer5/Layer5_AirPressCircle1.png \
    pics/Graphics/Layer5/Layer5_AirPressCircle2.png \
    pics/Graphics/Layer5/Layer5_B_03_1.png \
    pics/Graphics/Layer5/Layer5_B_03_2.png \
    pics/Graphics/Layer5/Layer5_B_04_1.png \
    pics/Graphics/Layer5/Layer5_B_04_2.png \
    pics/Graphics/Layer6/Layer6_ NeedleBackgroun_EngineSpeed.png \
    pics/Graphics/Layer6/Layer6_ NeedleBackgroun_EngineSpeed.png \
    pics/Graphics/Layer6/Layer6_ NeedleBackgroun_EngineSpeed.png \
    pics/Graphics/Layer6/Layer6_ NeedleBackgroun_EngineSpeed.png \
    pics/Graphics/Layer6/Layer6_ NeedleBackgroun_EngineSpeed.png \
    pics/Graphics/Layer6/Layer6_ NeedleBackground_AirPressCircle1.png \
    pics/Graphics/Layer6/Layer6_ NeedleBackground_AirPressCircle1.png \
    pics/Graphics/Layer6/Layer6_ NeedleBackground_AirPressCircle1.png \
    pics/Graphics/Layer6/Layer6_ NeedleBackground_AirPressCircle1.png \
    pics/Graphics/Layer6/Layer6_ NeedleBackground_AirPressCircle1.png \
    pics/Graphics/Layer6/Layer6_ NeedleBackground_AirPressCircle2.png \
    pics/Graphics/Layer6/Layer6_ NeedleBackground_AirPressCircle2.png \
    pics/Graphics/Layer6/Layer6_ NeedleBackground_AirPressCircle2.png \
    pics/Graphics/Layer6/Layer6_ NeedleBackground_AirPressCircle2.png \
    pics/Graphics/Layer6/Layer6_ NeedleBackground_AirPressCircle2.png \
    pics/Graphics/Layer6/Layer6_ NeedleBackground_VehicleSpeed — копия.png \
    pics/Graphics/Layer6/Layer6_ NeedleBackground_VehicleSpeed — копия.png \
    pics/Graphics/Layer6/Layer6_ NeedleBackground_VehicleSpeed — копия.png \
    pics/Graphics/Layer6/Layer6_ NeedleBackground_VehicleSpeed — копия.png \
    pics/Graphics/Layer6/Layer6_ NeedleBackground_VehicleSpeed.png \
    pics/Graphics/Layer7/Layer7_ Needle_ AirPressCircle1.png \
    pics/Graphics/Layer7/Layer7_ Needle_ AirPressCircle1.png \
    pics/Graphics/Layer7/Layer7_ Needle_ AirPressCircle2.png \
    pics/Graphics/Layer7/Layer7_ Needle_ AirPressCircle2.png \
    pics/Graphics/Layer7/Layer7_ Needle_EngineSpeed.png \
    pics/Graphics/Layer7/Layer7_ Needle_EngineSpeed.png \
    pics/Graphics/Layer7/Layer7_ Needle_VehicleSpeed.png \
    pics/Graphics/Layer7/Layer7_ Needle_VehicleSpeed.png \
    pics/Graphics/Layer8/Layer8_CentralCircle_AirPress1.png \
    pics/Graphics/Layer8/Layer8_CentralCircle_AirPress2.png \
    pics/Graphics/Layer8/Layer8_CentralCircle_EngineSpeed.png \
    pics/Graphics/Layer8/Layer8_CentralCircle_VehicleSpeed.png \
    pics/Graphics/Layer9/Layer9_Bus_5292.png \
    pics/Graphics/Layer9/Layer9_F_03_1.png \
    pics/Graphics/Layer9/Layer9_F_03_2.png \
    pics/Graphics/Layer9/Layer9_G_01_1.png \
    pics/Graphics/Layer9/Layer9_G_01_2.png \
    pics/Graphics/Layer9/Layer9_H_01.png \
    pics/Graphics/Layer9/Layer9_H_02.png \
    pics/Graphics/Layer9/Layer9_H_03.png \
    pics/Graphics/Layer9/Layer9_H_04.png \
    pics/Graphics/Layer9/Layer9_L_01_1.png \
    pics/Graphics/Layer9/Layer9_L_01_2.png \
    pics/Graphics/Layer9/Layer9_M_03.png \
    pics/Graphics/Layer9/Layer9_M_04.png \
    pics/Graphics/Layer9/Layer9_M_05.png \
    pics/Graphics/Layer9/Layer9_M_06.png \
    pics/Graphics/Layer9/Layer9_TempCabin.png \
    pics/Graphics/Layer9/Layer9_TempFrontalAC.png \
    pics/Graphics/Layer9/Layer9_TempSalon.png \
    pics/Graphics/Layer9/Layer9_Weather.png \
    pics/IC12_interface_graphics/Icon_1.png \
    pics/IC12_interface_graphics/Icon_2.png \
    pics/IC12_interface_graphics/Icon_3.png \
    pics/IC12_interface_graphics/Layer_2.png \
    pics/IC12_interface_graphics/iC12_CenterwithNeedle.png \
    pics/IC12_interface_graphics/iC12_big_arrow.png \
    pics/IC12_interface_graphics/iC12_big_arrow1.png \
    pics/IC12_interface_graphics/iC12_big_arrow_without_backlight.png \
    pics/IC12_interface_graphics/iC12_brake_circut_1.png \
    pics/IC12_interface_graphics/iC12_brake_circut_1_red.png \
    pics/IC12_interface_graphics/iC12_brake_circut_2.png \
    pics/IC12_interface_graphics/iC12_brake_circut_2_red.png \
    pics/IC12_interface_graphics/iC12_bus.png \
    pics/IC12_interface_graphics/iC12_bus_without_doors.png \
    pics/IC12_interface_graphics/iC12_door_left_red.png \
    pics/IC12_interface_graphics/iC12_door_right_red.png \
    pics/IC12_interface_graphics/iC12_door_right_yellow.png \
    pics/IC12_interface_graphics/iC12_door_rleft_yellow.png \
    pics/IC12_interface_graphics/iC12_doors_attention_red.png \
    pics/IC12_interface_graphics/iC12_doors_attention_yellow.png \
    pics/IC12_interface_graphics/iC12_doors_close.png \
    pics/IC12_interface_graphics/iC12_doors_close_red.png \
    pics/IC12_interface_graphics/iC12_doors_close_yellow.png \
    pics/IC12_interface_graphics/iC12_doors_passenger.png \
    pics/IC12_interface_graphics/iC12_drive_off.png \
    pics/IC12_interface_graphics/iC12_drive_on.png \
    pics/IC12_interface_graphics/iC12_electrical_system.png \
    pics/IC12_interface_graphics/iC12_electrical_system_red.png \
    pics/IC12_interface_graphics/iC12_engineCenterwithNeedle.png \
    pics/IC12_interface_graphics/iC12_engine_warm-up_request.png \
    pics/IC12_interface_graphics/iC12_engine_warm-up_request_red.png \
    pics/IC12_interface_graphics/iC12_enginebig_arrow.png \
    pics/IC12_interface_graphics/iC12_full_view.png \
    pics/IC12_interface_graphics/iC12_gradient_illumination_air_pressure_left.png \
    pics/IC12_interface_graphics/iC12_gradient_illumination_air_pressure_right.png \
    pics/IC12_interface_graphics/iC12_gradient_illumination_speedometr(0).png \
    pics/IC12_interface_graphics/iC12_gradient_illumination_speedometr(1).png \
    pics/IC12_interface_graphics/iC12_gradient_illumination_speedometr(2).png \
    pics/IC12_interface_graphics/iC12_gradient_illumination_tachometr(0).png \
    pics/IC12_interface_graphics/iC12_gradient_illumination_tachometr(1).png \
    pics/IC12_interface_graphics/iC12_gradient_illumination_tachometr(2).png \
    pics/IC12_interface_graphics/iC12_layer_1.png \
    pics/IC12_interface_graphics/iC12_layer_2.png \
    pics/IC12_interface_graphics/iC12_neutral_off.png \
    pics/IC12_interface_graphics/iC12_neutral_on.png \
    pics/IC12_interface_graphics/iC12_park_off.png \
    pics/IC12_interface_graphics/iC12_park_on.png \
    pics/IC12_interface_graphics/iC12_reverse_off.png \
    pics/IC12_interface_graphics/iC12_reverse_on.png \
    pics/IC12_interface_graphics/iC12_selector_badge_podium.png \
    pics/IC12_interface_graphics/iC12_selector_illumination.png \
    pics/IC12_interface_graphics/iC12_small_arrow.png \
    pics/IC12_interface_graphics/iC12_small_arrow_2.png \
    pics/IC12_interface_graphics/iC12_speedometr_centr.png \
    pics/IC12_interface_graphics/iC12_speedometr_centr_last.png \
    pics/IC12_interface_graphics/iC12_tank_system.png \
    pics/IC12_interface_graphics/iC12_tank_system_amber_yellow.png \
    pics/IC12_interface_graphics/iC12_tonometer_centr_left.png \
    pics/IC12_interface_graphics/iC12_tonometer_centr_right.png \
    pics/IC12_interface_graphics/popup.png \
    pics/IC12_interface_graphics/welcome_screen.png \
    pics/IC12_interface_graphics/welcome_screen1.png \
    pics/Menu/1.png \
    pics/Menu/10.png \
    pics/Menu/11.png \
    pics/Menu/2.png \
    pics/Menu/4.png \
    pics/Menu/5.png \
    pics/Menu/6.png \
    pics/Menu/7.png \
    pics/Menu/8.png \
    pics/Menu/9.png \
    pics/Menu/AdBlue.png \
    pics/Menu/AdBlue_temperature.png \
    pics/Menu/Arrow (door valves) 2.png \
    pics/Menu/Arrow (door valves) 2.png \
    pics/Menu/Arrow (door valves).png \
    pics/Menu/Arrow (door valves).png \
    pics/Menu/Arrow_down.png \
    pics/Menu/Arrow_left.png \
    pics/Menu/Arrow_right.png \
    pics/Menu/Arrow_up.png \
    pics/Menu/Automatic Kneeling.png \
    pics/Menu/Automatic Kneeling.png \
    pics/Menu/Automatic door closing by sensors.png \
    pics/Menu/Automatic door closing by sensors.png \
    pics/Menu/Automatic on the alarm system.png \
    pics/Menu/Automatic on the alarm system.png \
    pics/Menu/Automatic opening.png \
    pics/Menu/Automatic opening.png \
    pics/Menu/Battery.png \
    pics/Menu/Bus layout 2.png \
    pics/Menu/Bus layout 2.png \
    pics/Menu/Bus layout 3.png \
    pics/Menu/Bus layout 3.png \
    pics/Menu/Bus layout.png \
    pics/Menu/Bus layout.png \
    pics/Menu/Bus1.png \
    pics/Menu/Bus1b.png \
    pics/Menu/Bus1w.png \
    pics/Menu/Bus2.png \
    pics/Menu/Bus2b.png \
    pics/Menu/Bus2w.png \
    pics/Menu/Bus_layout_2ax__1_.png \
    pics/Menu/Bus_layout_3.png \
    pics/Menu/Bus_layout_3__1_.png \
    pics/Menu/Button_off.png \
    pics/Menu/Button_off_last.png \
    pics/Menu/Button_off_left_temp.png \
    pics/Menu/Button_on.png \
    pics/Menu/Button_on_left_temp.png \
    pics/Menu/Circuit_1.png \
    pics/Menu/Circuit_2.png \
    pics/Menu/Circuit_3.png \
    pics/Menu/Circuit_4.png \
    pics/Menu/Circuit_5.png \
    pics/Menu/Coolant_temperature.png \
    pics/Menu/DLR.png \
    pics/Menu/Diagnostics.png \
    pics/Menu/Diagnostics_white.png \
    pics/Menu/Door valves (2).png \
    pics/Menu/Door valves (2).png \
    pics/Menu/Door valves.png \
    pics/Menu/Door valves.png \
    pics/Menu/Door__1_.png \
    pics/Menu/Doorway passenger sensor.png \
    pics/Menu/Doorway passenger sensor.png \
    pics/Menu/Emergence cranes.png \
    pics/Menu/Emergence cranes.png \
    pics/Menu/Emergence_hammers_for_menu__1_.png \
    pics/Menu/Fire_extinguishers_for_mnu__1_.png \
    pics/Menu/Fuel.png \
    pics/Menu/Heating_system_valves.png \
    pics/Menu/Illumination.png \
    pics/Menu/Layer_1.png \
    pics/Menu/Layer_1_5.png \
    pics/Menu/Layer_1_last.png \
    pics/Menu/Oil.png \
    pics/Menu/Oil_temperature.png \
    pics/Menu/Oil_temperature_hydraulic_retarder.png \
    pics/Menu/Parameters.png \
    pics/Menu/Parameters_white.png \
    pics/Menu/Runner.png \
    pics/Menu/Runner_bluebot.png \
    pics/Menu/Runner_bluedot.png \
    pics/Menu/Runner_line.png \
    pics/Menu/Service.png \
    pics/Menu/Service_white.png \
    pics/Menu/Settings.png \
    pics/Menu/Settings_white.png \
    pics/Menu/Small_illumination.png \
    pics/Menu/Sound.png \
    pics/Menu/Tire_2.png \
    pics/Menu/Wipers.png \
    pics/Menu/bar.png \
    pics/Menu/bar_background.png \
    pics/Menu/dual_axle_bus_with_double-wheel_rear_axle.png \
    pics/Menu/front fog light.png \
    pics/Menu/front fog light.png \
    pics/Menu/front fog light.png \
    pics/Menu/full_view_menu.png \
    pics/Menu/parameter.png \
    pics/Menu/Illumination.png \
    pics/Menu/the_utmost_bar.png \
    pics/Menu/tire_1.png \
    pics/Menu/tire_menu_red.png \
    pics/Menu/tire_menu_yellow.png \
    pics/TellTales/A/Black/A01.png \
    pics/TellTales/A/Black/A01.png \
    pics/TellTales/A/Black/A02.png \
    pics/TellTales/A/Black/A02.png \
    pics/TellTales/A/Black/A05.png \
    pics/TellTales/A/Black/A05.png \
    pics/TellTales/A/Black/A06.png \
    pics/TellTales/A/Black/A06.png \
    pics/TellTales/A/Black/A09.png \
    pics/TellTales/A/Black/A09.png \
    pics/TellTales/A/Black/A21.png \
    pics/TellTales/A/Black/A27.png \
    pics/TellTales/A/Black/A37.png \
    pics/TellTales/A/Black/A37.png \
    pics/TellTales/A/Black/A40.png \
    pics/TellTales/A/Black/A40.png \
    pics/TellTales/A/Black/A41.png \
    pics/TellTales/A/Black/A41.png \
    pics/TellTales/A/Black/A42.png \
    pics/TellTales/A/Black/A42.png \
    pics/TellTales/A/Black/A43.png \
    pics/TellTales/A/Black/A46.png \
    pics/TellTales/A/Black/A47.png \
    pics/TellTales/A/Black/A48.png \
    pics/TellTales/A/Black/A49.png \
    pics/TellTales/A/Black/A50.png \
    pics/TellTales/A/Black/A51.png \
    pics/TellTales/A/Black/A52.png \
    pics/TellTales/A/Black/A53.png \
    pics/TellTales/A/White/A01.png \
    pics/TellTales/A/White/A01.png \
    pics/TellTales/A/White/A01_w.png \
    pics/TellTales/A/White/A02.png \
    pics/TellTales/A/White/A02.png \
    pics/TellTales/A/White/A02_w.png \
    pics/TellTales/A/White/A05.png \
    pics/TellTales/A/White/A05.png \
    pics/TellTales/A/White/A05_w.png \
    pics/TellTales/A/White/A06.png \
    pics/TellTales/A/White/A06.png \
    pics/TellTales/A/White/A06_w.png \
    pics/TellTales/A/White/A09.png \
    pics/TellTales/A/White/A09.png \
    pics/TellTales/A/White/A09_w.png \
    pics/TellTales/A/White/A21.png \
    pics/TellTales/A/White/A21_w.png \
    pics/TellTales/A/White/A27.png \
    pics/TellTales/A/White/A27_w.png \
    pics/TellTales/A/White/A37.png \
    pics/TellTales/A/White/A37.png \
    pics/TellTales/A/White/A37_w.png \
    pics/TellTales/A/White/A40.png \
    pics/TellTales/A/White/A40.png \
    pics/TellTales/A/White/A40_w.png \
    pics/TellTales/A/White/A41.png \
    pics/TellTales/A/White/A41.png \
    pics/TellTales/A/White/A41_w.png \
    pics/TellTales/A/White/A42.png \
    pics/TellTales/A/White/A42.png \
    pics/TellTales/A/White/A42_w.png \
    pics/TellTales/A/White/A43.png \
    pics/TellTales/A/White/A43_w.png \
    pics/TellTales/A/White/A46.png \
    pics/TellTales/A/White/A46_w.png \
    pics/TellTales/A/White/A47.png \
    pics/TellTales/A/White/A47_w.png \
    pics/TellTales/A/White/A48.png \
    pics/TellTales/A/White/A48_w.png \
    pics/TellTales/A/White/A49.png \
    pics/TellTales/A/White/A49_w.png \
    pics/TellTales/A/White/A50.png \
    pics/TellTales/A/White/A50_w.png \
    pics/TellTales/A/White/A51.png \
    pics/TellTales/A/White/A51_w.png \
    pics/TellTales/A/White/A52.png \
    pics/TellTales/A/White/A52_w.png \
    pics/TellTales/A/White/A53.png \
    pics/TellTales/A/White/A53_w.png \
    pics/TellTales/B/Black/B01.png \
    pics/TellTales/B/Black/B02.png \
    pics/TellTales/B/Black/B03.png \
    pics/TellTales/B/Black/B04.png \
    pics/TellTales/B/Black/B05.png \
    pics/TellTales/B/Black/B10.png \
    pics/TellTales/B/Black/B14.png \
    pics/TellTales/B/Black/B15.png \
    pics/TellTales/B/Black/B21.png \
    pics/TellTales/B/Black/B21.png \
    pics/TellTales/B/Black/B22.png \
    pics/TellTales/B/Black/B23.png \
    pics/TellTales/B/Black/B24.png \
    pics/TellTales/B/Black/В01.png \
    pics/TellTales/B/Black/В02.png \
    pics/TellTales/B/Black/В03.png \
    pics/TellTales/B/Black/В04.png \
    pics/TellTales/B/Black/В05.png \
    pics/TellTales/B/Black/В10.png \
    pics/TellTales/B/Black/В14.png \
    pics/TellTales/B/Black/В15.png \
    pics/TellTales/B/Black/В22.png \
    pics/TellTales/B/Black/В23.png \
    pics/TellTales/B/White/B01.png \
    pics/TellTales/B/White/B01_w.png \
    pics/TellTales/B/White/B02.png \
    pics/TellTales/B/White/B02_w.png \
    pics/TellTales/B/White/B03.png \
    pics/TellTales/B/White/B03_w.png \
    pics/TellTales/B/White/B04.png \
    pics/TellTales/B/White/B04_w.png \
    pics/TellTales/B/White/B05.png \
    pics/TellTales/B/White/B05_r.png \
    pics/TellTales/B/White/B05_y.png \
    pics/TellTales/B/White/B10.png \
    pics/TellTales/B/White/B10_w.png \
    pics/TellTales/B/White/B14.png \
    pics/TellTales/B/White/B14_g.png \
    pics/TellTales/B/White/B14_r.png \
    pics/TellTales/B/White/B14_y.png \
    pics/TellTales/B/White/B15.png \
    pics/TellTales/B/White/B15_w.png \
    pics/TellTales/B/White/B21.png \
    pics/TellTales/B/White/B21.png \
    pics/TellTales/B/White/B21_g.png \
    pics/TellTales/B/White/B21_r.png \
    pics/TellTales/B/White/B21_y.png \
    pics/TellTales/B/White/B22.png \
    pics/TellTales/B/White/B22_w.png \
    pics/TellTales/B/White/B23.png \
    pics/TellTales/B/White/B23_w.png \
    pics/TellTales/B/White/B24.png \
    pics/TellTales/B/White/B24_w.png \
    pics/TellTales/B/White/B24_white.png \
    pics/TellTales/B/White/В01.png \
    pics/TellTales/B/White/В02.png \
    pics/TellTales/B/White/В03.png \
    pics/TellTales/B/White/В04.png \
    pics/TellTales/B/White/В05.png \
    pics/TellTales/B/White/В10.png \
    pics/TellTales/B/White/В14.png \
    pics/TellTales/B/White/В15.png \
    pics/TellTales/B/White/В22.png \
    pics/TellTales/B/White/В23.png \
    pics/TellTales/C/Black/C02.png \
    pics/TellTales/C/Black/C02.png \
    pics/TellTales/C/Black/C07.png \
    pics/TellTales/C/Black/C25.png \
    pics/TellTales/C/Black/C25.png \
    pics/TellTales/C/Black/C26.png \
    pics/TellTales/C/Black/C26.png \
    pics/TellTales/C/Black/C27.png \
    pics/TellTales/C/Black/C27.png \
    pics/TellTales/C/Black/C28.png \
    pics/TellTales/C/Black/C28.png \
    pics/TellTales/C/Black/C29.png \
    pics/TellTales/C/Black/C29.png \
    pics/TellTales/C/Black/C30.png \
    pics/TellTales/C/Black/C30.png \
    pics/TellTales/C/Black/C31.png \
    pics/TellTales/C/Black/C31.png \
    pics/TellTales/C/White/C02.png \
    pics/TellTales/C/White/C02.png \
    pics/TellTales/C/White/C02_w.png \
    pics/TellTales/C/White/C07.png \
    pics/TellTales/C/White/C07_w.png \
    pics/TellTales/C/White/C07_white.png \
    pics/TellTales/C/White/C18.png \
    pics/TellTales/C/White/C18_w.png \
    pics/TellTales/C/White/C18_white.png \
    pics/TellTales/C/White/C25.png \
    pics/TellTales/C/White/C25.png \
    pics/TellTales/C/White/C25_w.png \
    pics/TellTales/C/White/C26.png \
    pics/TellTales/C/White/C26.png \
    pics/TellTales/C/White/C26_w.png \
    pics/TellTales/C/White/C27.png \
    pics/TellTales/C/White/C27.png \
    pics/TellTales/C/White/C27_w.png \
    pics/TellTales/C/White/C28.png \
    pics/TellTales/C/White/C28.png \
    pics/TellTales/C/White/C28_w.png \
    pics/TellTales/C/White/C29.png \
    pics/TellTales/C/White/C29.png \
    pics/TellTales/C/White/C29_w.png \
    pics/TellTales/C/White/C30.png \
    pics/TellTales/C/White/C30.png \
    pics/TellTales/C/White/C30_w.png \
    pics/TellTales/C/White/C31.png \
    pics/TellTales/C/White/C31.png \
    pics/TellTales/C/White/C31_w.png \
    pics/TellTales/D/Black/D31.png \
    pics/TellTales/D/Black/D31.png \
    pics/TellTales/D/Black/D44.png \
    pics/TellTales/D/Black/D44.png \
    pics/TellTales/D/Black/D46.png \
    pics/TellTales/D/Black/D46.png \
    pics/TellTales/D/Black/D47.png \
    pics/TellTales/D/Black/D47.png \
    pics/TellTales/D/Black/D48.png \
    pics/TellTales/D/Black/D48.png \
    pics/TellTales/D/White/D31.png \
    pics/TellTales/D/White/D31.png \
    pics/TellTales/D/White/D31_w.png \
    pics/TellTales/D/White/D44.png \
    pics/TellTales/D/White/D44.png \
    pics/TellTales/D/White/D44_w.png \
    pics/TellTales/D/White/D45.png \
    pics/TellTales/D/White/D45_w.png \
    pics/TellTales/D/White/D46.png \
    pics/TellTales/D/White/D46.png \
    pics/TellTales/D/White/D46_w.png \
    pics/TellTales/D/White/D47.png \
    pics/TellTales/D/White/D47.png \
    pics/TellTales/D/White/D47_w.png \
    pics/TellTales/D/White/D48.png \
    pics/TellTales/D/White/D48.png \
    pics/TellTales/D/White/D48_w.png \
    pics/TellTales/D/White/D49.png \
    pics/TellTales/D/White/D49_w.png \
    pics/TellTales/D/White/D50.png \
    pics/TellTales/D/White/D50_w.png \
    pics/TellTales/D/White/D51.png \
    pics/TellTales/D/White/D51_w.png \
    pics/TellTales/E/Black/E15.png \
    pics/TellTales/E/Black/E15.png \
    pics/TellTales/E/Black/E16.png \
    pics/TellTales/E/Black/E16.png \
    pics/TellTales/E/Black/E17.png \
    pics/TellTales/E/Black/E17.png \
    pics/TellTales/E/Black/E18.png \
    pics/TellTales/E/Black/E18.png \
    pics/TellTales/E/Black/E19.png \
    pics/TellTales/E/Black/E19.png \
    pics/TellTales/E/Black/E20.png \
    pics/TellTales/E/Black/E20.png \
    pics/TellTales/E/White/E15.png \
    pics/TellTales/E/White/E15.png \
    pics/TellTales/E/White/E15_w.png \
    pics/TellTales/E/White/E16.png \
    pics/TellTales/E/White/E16.png \
    pics/TellTales/E/White/E16_w.png \
    pics/TellTales/E/White/E17.png \
    pics/TellTales/E/White/E17.png \
    pics/TellTales/E/White/E17_w.png \
    pics/TellTales/E/White/E18.png \
    pics/TellTales/E/White/E18.png \
    pics/TellTales/E/White/E18_w.png \
    pics/TellTales/E/White/E19.png \
    pics/TellTales/E/White/E19.png \
    pics/TellTales/E/White/E19_w.png \
    pics/TellTales/E/White/E20.png \
    pics/TellTales/E/White/E20.png \
    pics/TellTales/E/White/E20_w.png \
    pics/TellTales/F/Black/F01.png \
    pics/TellTales/F/Black/F01.png \
    pics/TellTales/F/Black/F02.png \
    pics/TellTales/F/Black/F02.png \
    pics/TellTales/F/Black/F03.png \
    pics/TellTales/F/Black/F03.png \
    pics/TellTales/F/Black/F04.png \
    pics/TellTales/F/Black/F04.png \
    pics/TellTales/F/Black/F05.png \
    pics/TellTales/F/Black/F05.png \
    pics/TellTales/F/Black/F10.png \
    pics/TellTales/F/Black/F10.png \
    pics/TellTales/F/Black/F15.png \
    pics/TellTales/F/Black/F15.png \
    pics/TellTales/F/Black/F16.png \
    pics/TellTales/F/Black/F16.png \
    pics/TellTales/F/Black/F30.png \
    pics/TellTales/F/Black/F30.png \
    pics/TellTales/F/Black/F31.png \
    pics/TellTales/F/Black/F31.png \
    pics/TellTales/F/Black/F32.png \
    pics/TellTales/F/Black/F32.png \
    pics/TellTales/F/Black/F33.png \
    pics/TellTales/F/Black/F33.png \
    pics/TellTales/F/Black/F34.png \
    pics/TellTales/F/Black/F34.png \
    pics/TellTales/F/Black/F35.png \
    pics/TellTales/F/Black/F35.png \
    pics/TellTales/F/Black/F36.png \
    pics/TellTales/F/Black/F36.png \
    pics/TellTales/F/White/F01.png \
    pics/TellTales/F/White/F01.png \
    pics/TellTales/F/White/F01_w.png \
    pics/TellTales/F/White/F02.png \
    pics/TellTales/F/White/F02.png \
    pics/TellTales/F/White/F02_w.png \
    pics/TellTales/F/White/F03.png \
    pics/TellTales/F/White/F03.png \
    pics/TellTales/F/White/F03_w.png \
    pics/TellTales/F/White/F04.png \
    pics/TellTales/F/White/F04.png \
    pics/TellTales/F/White/F04_w.png \
    pics/TellTales/F/White/F05.png \
    pics/TellTales/F/White/F05.png \
    pics/TellTales/F/White/F05_w.png \
    pics/TellTales/F/White/F10.png \
    pics/TellTales/F/White/F10.png \
    pics/TellTales/F/White/F10_w.png \
    pics/TellTales/F/White/F15.png \
    pics/TellTales/F/White/F15.png \
    pics/TellTales/F/White/F15_w.png \
    pics/TellTales/F/White/F15_y.png \
    pics/TellTales/F/White/F16.png \
    pics/TellTales/F/White/F16.png \
    pics/TellTales/F/White/F16_w.png \
    pics/TellTales/F/White/F18_r.png \
    pics/TellTales/F/White/F19_y.png \
    pics/TellTales/F/White/F22_y.png \
    pics/TellTales/F/White/F30.png \
    pics/TellTales/F/White/F30.png \
    pics/TellTales/F/White/F30_w.png \
    pics/TellTales/F/White/F31.png \
    pics/TellTales/F/White/F31.png \
    pics/TellTales/F/White/F31_w.png \
    pics/TellTales/F/White/F32.png \
    pics/TellTales/F/White/F32.png \
    pics/TellTales/F/White/F32_w.png \
    pics/TellTales/F/White/F33.png \
    pics/TellTales/F/White/F33.png \
    pics/TellTales/F/White/F33_w.png \
    pics/TellTales/F/White/F34.png \
    pics/TellTales/F/White/F34.png \
    pics/TellTales/F/White/F34_w.png \
    pics/TellTales/F/White/F35.png \
    pics/TellTales/F/White/F35.png \
    pics/TellTales/F/White/F35_w.png \
    pics/TellTales/F/White/F36.png \
    pics/TellTales/F/White/F36.png \
    pics/TellTales/F/White/F36_w.png \
    pics/TellTales/G/Black/G01.png \
    pics/TellTales/G/Black/G01.png \
    pics/TellTales/G/White/G01.png \
    pics/TellTales/G/White/G01.png \
    pics/TellTales/G/White/G01_w.png \
    pics/TellTales/G/White/G10_r.png \
    pics/TellTales/G/White/G21.png \
    pics/TellTales/G/White/G21_w.png \
    pics/TellTales/G/White/G22.png \
    pics/TellTales/G/White/G22_w.png \
    pics/TellTales/G/White/G23.png \
    pics/TellTales/G/White/G23_w.png \
    pics/TellTales/G/White/G24.png \
    pics/TellTales/G/White/G24_w.png \
    pics/TellTales/G/White/G25.png \
    pics/TellTales/G/White/G25_w.png \
    pics/TellTales/G/White/G26.png \
    pics/TellTales/G/White/G26_w.png \
    pics/TellTales/GrpA/A_01.png \
    pics/TellTales/GrpA/A_02.png \
    pics/TellTales/GrpA/A_03.png \
    pics/TellTales/GrpA/A_04.png \
    pics/TellTales/GrpA/A_05.png \
    pics/TellTales/GrpA/A_06.png \
    pics/TellTales/H/Black/H05.png \
    pics/TellTales/H/Black/H05.png \
    pics/TellTales/H/White/H05.png \
    pics/TellTales/H/White/H05.png \
    pics/TellTales/H/White/H05_w.png \
    pics/TellTales/High beam.png \
    pics/TellTales/J/white/J07.png \
    pics/TellTales/J/white/J07_w.png \
    pics/TellTales/J/white/J07_white.png \
    pics/TellTales/K/Black/K01.png \
    pics/TellTales/K/Black/K01.png \
    pics/TellTales/K/Black/K10.png \
    pics/TellTales/K/Black/K10.png \
    pics/TellTales/K/Black/K13.png \
    pics/TellTales/K/Black/K13.png \
    pics/TellTales/K/Black/K28.png \
    pics/TellTales/K/Black/K28.png \
    pics/TellTales/K/Black/K29.png \
    pics/TellTales/K/Black/K29.png \
    pics/TellTales/K/Black/K30.png \
    pics/TellTales/K/Black/K30.png \
    pics/TellTales/K/Black/K31.png \
    pics/TellTales/K/Black/K31.png \
    pics/TellTales/K/Black/K32.png \
    pics/TellTales/K/Black/K32.png \
    pics/TellTales/K/Black/K33.png \
    pics/TellTales/K/Black/K33.png \
    pics/TellTales/K/Black/K34.png \
    pics/TellTales/K/Black/K34.png \
    pics/TellTales/K/Black/K35.png \
    pics/TellTales/K/Black/K35.png \
    pics/TellTales/K/White/K01.png \
    pics/TellTales/K/White/K01.png \
    pics/TellTales/K/White/K01_w.png \
    pics/TellTales/K/White/K10.png \
    pics/TellTales/K/White/K10.png \
    pics/TellTales/K/White/K10_w.png \
    pics/TellTales/K/White/K13.png \
    pics/TellTales/K/White/K13.png \
    pics/TellTales/K/White/K13_w.png \
    pics/TellTales/K/White/K28.png \
    pics/TellTales/K/White/K28.png \
    pics/TellTales/K/White/K28_w.png \
    pics/TellTales/K/White/K29.png \
    pics/TellTales/K/White/K29.png \
    pics/TellTales/K/White/K29_w.png \
    pics/TellTales/K/White/K30.png \
    pics/TellTales/K/White/K30.png \
    pics/TellTales/K/White/K30_w.png \
    pics/TellTales/K/White/K31.png \
    pics/TellTales/K/White/K31.png \
    pics/TellTales/K/White/K31_w.png \
    pics/TellTales/K/White/K32.png \
    pics/TellTales/K/White/K32.png \
    pics/TellTales/K/White/K32_w.png \
    pics/TellTales/K/White/K33.png \
    pics/TellTales/K/White/K33.png \
    pics/TellTales/K/White/K33_w.png \
    pics/TellTales/K/White/K34.png \
    pics/TellTales/K/White/K34.png \
    pics/TellTales/K/White/K34_g.png \
    pics/TellTales/K/White/K34_r.png \
    pics/TellTales/K/White/K35.png \
    pics/TellTales/K/White/K35.png \
    pics/TellTales/K/White/K35_r.png \
    pics/TellTales/K/White/K35_y.png \
    pics/TellTales/M/Black/M01.png \
    pics/TellTales/M/White/M01.png \
    pics/TellTales/M/White/M01_w.png \
    pics/TellTales/P/Black/P08.png \
    pics/TellTales/P/Black/P08.png \
    pics/TellTales/P/White/P08.png \
    pics/TellTales/P/White/P08.png \
    pics/TellTales/P/White/P08_w.png \
    pics/TellTales/high-beam.png \
    pics/TellTales/high-beam.png \
    pics/TellTales/М/Black/M01.png \
    pics/TellTales/М/White/M01.png \
    pics/dummy.png \

HEADERS += \
    Business_Logic/Common/j1939_config.h \
    Business_Logic/Common/menu_defines.h \
    Business_Logic/Common/menu_items.h \
    Business_Logic/Common/telltales_defines.h \
    Business_Logic/Connectivity/JSON/qtjsonconfiguredata.h \
    Business_Logic/Connectivity/JSON/qtjsonhandler.h \
    Business_Logic/Connectivity/JSON/qtjsonmenuhandler.h \
    Business_Logic/Connectivity/JSON/qtjsonpopuphandler.h \
    Business_Logic/Connectivity/can_handler.h \
    Business_Logic/Connectivity/hmi_handler.h \
    Business_Logic/Connectivity/j1939_data_handler.h \
    Business_Logic/Connectivity/pwmchannel.h \
    Business_Logic/Interfaces/IMenuDrawer.h \
    Business_Logic/Interfaces/IMenuNavigation.h \
    Business_Logic/Interfaces/ISubscriber.h \
    Business_Logic/Interfaces/ican_msg.h \
    Business_Logic/Interfaces/iobserverforrender.h \
    Business_Logic/Interfaces/iplaylist.h \
    Business_Logic/Logger/error_tracing.h \
    Business_Logic/Logger/exception_define.h \
    Business_Logic/Menu/menu_diagnostics_handler.h \
    Business_Logic/Menu/menu_handler.h \
    Business_Logic/Menu/menu_services_handler.h \
    Business_Logic/Menu/menu_settings_handler.h \
    Business_Logic/Menu/newmenuitems.h \
    Business_Logic/navigation.h \
    Business_Logic/playlistfactory.h \
    Business_Logic/playlisthandlerwav.h \
    Business_Logic/playlistwav.h \
    Business_Logic/subscribe_notifer.h \
    lib/mt_dsp/include/mt_dsp_median.h \
    lib/mt_dsp/include/mt_dsp_mavg.h \
    Business_Logic/Common/apptypes.h \
    Business_Logic/Common/hmi_config.h \
    Business_Logic/Logger/logger.h \
    Business_Logic/Qt_Framework/qtairpressure1.h \
    Business_Logic/Qt_Framework/qtairpressure2.h \
    Business_Logic/Qt_Framework/qtapphandler.h \
    Business_Logic/Qt_Framework/qtcentraldashboard.h \
    Business_Logic/Qt_Framework/qtenginemeter.h \
    Business_Logic/Qt_Framework/qtmenuops.h \
    Business_Logic/Qt_Framework/qtpopup.h \
    Business_Logic/Qt_Framework/qtpwmcontrol.h \
    Business_Logic/Qt_Framework/qtspeedometer.h \
    Business_Logic/Qt_Framework/qttelltales.h \
    Business_Logic/Qt_Framework/qtzummerhandler.h \
    Business_Logic/sound_handler.h \
    Business_Logic/soundplaylist.h \

