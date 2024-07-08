#include <gtest/gtest.h>
#include "soundcore/DeviceScanner.hpp"
#include "soundcore/DeviceList.hpp"


TEST(DeviceListTest, TestScanning ) {
    DeviceList device_list;
    device_list.refresh();
    std::this_thread::sleep_for(std::chrono::seconds {1});
    device_list.stopRefreshing();
    auto devices = device_list.getDevices();

    ASSERT_NE(devices.size(),0);
}
