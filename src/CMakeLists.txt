file(GLOB HEADERS "${CMAKE_SOURCE_DIR}/include/soundcore/*.hpp")

add_library(${PROJECT_NAME} ${HEADERS}
        Device.cpp
        DeviceList.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(${PROJECT_NAME} PUBLIC Qt6::Core Qt6::Bluetooth Qt6::Qml)