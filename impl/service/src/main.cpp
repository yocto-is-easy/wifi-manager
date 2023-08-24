#include <iostream>
#include <memory>

#include "spdlog/spdlog.h"

#include "WifiInitter.hpp"
#include "PasswordGenerator.hpp"
#include "WifiManagerServiceImpl.hpp"

const std::string WIFI_SSID = "RaspberryPi3b 2.4GHz";
const std::string CHARSET = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

int main() {
    PasswordGenerator passwordGenerator(CHARSET);

    std::shared_ptr<WifiInitter> wifiInitter = std::make_shared<WifiInitter>(WIFI_SSID, passwordGenerator);

    try {
        wifiInitter->init();
    } catch(const std::exception& e) {
        spdlog::error("Error while initializing WifiInitter: {}", e.what());
        return -1;
    }
    spdlog::info("WifiInitter initialized");

    wifi_manager_service::setupWifiInitter(wifiInitter);
    try {
        wifi_manager_service::start();
    } catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
    }

    return 0;
}