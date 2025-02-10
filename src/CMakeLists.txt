file(GLOB HEADERS "${CMAKE_SOURCE_DIR}/include/soundcore/*.hpp" "${CMAKE_SOURCE_DIR}/include/soundcore/*/*.hpp")

add_library(${PROJECT_NAME} ${HEADERS}
        App.cpp
        connection/DeviceConnector.cpp
        discovery/DeviceDiscoverer.cpp
        list/DiscoveredDevicesInfoListModel.cpp
        device/Device.cpp
        device/Device2.cpp
        control/DeviceController.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(${PROJECT_NAME} PUBLIC Qt6::Core Qt6::Bluetooth Qt6::Qml)