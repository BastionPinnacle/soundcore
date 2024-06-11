file(GLOB HEADERS "${CMAKE_SOURCE_DIR}/include/soundcore/*.hpp")

add_library(${PROJECT_NAME} ${HEADERS})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Bluetooth)