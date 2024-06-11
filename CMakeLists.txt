cmake_minimum_required(VERSION 3.27)

set(CMAKE_CXX_STANDARD 20)

set(CONAN_SCRIPT "${CMAKE_SOURCE_DIR}/scripts/prepare_conan.sh")

execute_process(COMMAND bash -c "${CONAN_SCRIPT} ${CMAKE_SOURCE_DIR} ${CMAKE_BINARY_DIR} ${CMAKE_BUILD_TYPE}")

set(CMAKE_TOOLCHAIN_FILE ${CMAKE_BINARY_DIR}/build/${CMAKE_BUILD_TYPE}/generators/conan_toolchain.cmake)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

project(soundcore)
include(cmake/find_libs.cmake)

add_executable(main main.cpp ${RESOURCES})

add_subdirectory(src)

target_link_libraries(main PRIVATE Qt6::Qml Qt6::Gui Qt6::Bluetooth ${PROJECT_NAME})