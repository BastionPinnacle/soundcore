enable_testing()

find_package(Qt6 REQUIRED COMPONENTS Test Bluetooth)


#add_executable(test_bluetooth_discovery QBluetoothDeviceDiscoveryAgentTest.cpp)
#add_executable(DeviceInfoListTest DeviceInfoListTest.cpp)
#add_executable(DeviceTest DeviceTest.cpp)

#target_link_libraries(test_bluetooth_discovery PRIVATE Qt6::Test Qt6::Bluetooth soundcore)

#target_link_libraries(DeviceInfoListTest PRIVATE Qt6::Test Qt6::Bluetooth soundcore)

#target_link_libraries(DeviceTest PRIVATE Qt6::Test Qt6::Bluetooth soundcore)

#add_test(NAME BluetoothTest COMMAND test_bluetooth_discovery)
#add_test(NAME DeviceInfoListTest COMMAND DeviceInfoListTest)
#add_test(NAME DeviceTest COMMAND DeviceTest)