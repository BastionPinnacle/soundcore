cmake_minimum_required(VERSION 3.22)

set(CMAKE_CXX_STANDARD 20)

set(CONAN_SCRIPT "${CMAKE_SOURCE_DIR}/scripts/prepare_conan.sh")

execute_process(COMMAND bash -c "${CONAN_SCRIPT} ${CMAKE_SOURCE_DIR} ${CMAKE_BINARY_DIR} ${CMAKE_BUILD_TYPE}")

set(CMAKE_TOOLCHAIN_FILE ${CMAKE_BINARY_DIR}/build/${CMAKE_BUILD_TYPE}/generators/conan_toolchain.cmake)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


project(soundcore)
include(cmake/find_libs.cmake)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES main.cpp)
qt_add_resources(SOURCES res/resources.qrc)
qt_add_executable(main ${SOURCES})
target_link_libraries(main PRIVATE Qt6::Gui Qt6::Qml Qt6::Bluetooth Qt6::Core Qt::Test soundcore BasicLibplugin ColorsLibplugin)

add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(res/Basic)
add_subdirectory(res/Colors)