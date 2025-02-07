qt_add_library(ColorsLib STATIC)

set_target_properties(ColorsLib PROPERTIES AUTOMOC ON)
target_link_libraries(ColorsLib PRIVATE Qt6::Quick)

list(APPEND SINGLETON_MODULE_QML_FILES Colors.qml)

set_source_files_properties(${SINGLETON_MODULE_QML_FILES} PROPERTIES QT_QML_SINGLETON_TYPE TRUE)

qt_add_qml_module(ColorsLib URI Colors VERSION 1.0 RESOURCE_PREFIX /soundcore/imports QML_FILES ${SINGLETON_MODULE_QML_FILES} )