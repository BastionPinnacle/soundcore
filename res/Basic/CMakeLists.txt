qt_add_library(BasicLib STATIC)

set_target_properties(BasicLib PROPERTIES AUTOMOC ON)
target_link_libraries(BasicLib PRIVATE Qt6::Quick  Qt6::QuickControls2 ColorsLibplugin)

list(APPEND MODULE_QML_FILES BasicButton.qml)

qt_add_qml_module(BasicLib URI Basic VERSION 1.0 RESOURCE_PREFIX /soundcore/imports QML_FILES ${MODULE_QML_FILES})