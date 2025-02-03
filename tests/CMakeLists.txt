enable_testing()

find_package(Qt6 REQUIRED COMPONENTS Test Bluetooth)


add_executable(test_bluetooth_discovery QBluetoothDeviceDiscoveryAgentTest.cpp)

target_link_libraries(test_bluetooth_discovery PRIVATE Qt6::Test Qt6::Bluetooth soundcore)

add_test(NAME BluetoothTest COMMAND test_bluetooth_discovery)