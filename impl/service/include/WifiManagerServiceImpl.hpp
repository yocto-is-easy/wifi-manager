#pragma once

#include <memory>

#include "wifi-manager/i-wifi-manager.h"
#include <supervisor.hpp>

#include "WifiInitter.hpp"

using namespace std::chrono_literals;

namespace wifi_manager_service {
    std::shared_ptr<WifiInitter> wifiInitter = nullptr;

    void setupWifiInitter(std::shared_ptr<WifiInitter> wifiInitter);
    void start();
} // wifi_manager_service

INIT_MIDF_SERVER(wifi_manager);

MIDF_IMPL_FUNC(std::string, wifi_manager, get_wifi_ssid) () {
    return wifi_manager_service::wifiInitter->getSsid();
}

MIDF_IMPL_FUNC(std::string, wifi_manager, get_wifi_password) () {
    return wifi_manager_service::wifiInitter->getPassword();
}

MIDF_IMPL_FUNC(std::string, wifi_manager, get_wifi_gateway_ip) () {
    return wifi_manager_service::wifiInitter->getGatewayIp();
}

MIDF_IMPL_FUNC(std::string, wifi_manager, get_wifi_gateway_mac) () {
    return wifi_manager_service::wifiInitter->getGatewayMac();
}

MIDF_IMPL_FUNC(int64_t, wifi_manager, get_wifi_speed_mbps) () {
    return wifi_manager_service::wifiInitter->getSpeedMbps();
}

namespace wifi_manager_service {
    void setupWifiInitter(std::shared_ptr<WifiInitter> wifiInitter) {
        wifi_manager_service::wifiInitter = wifiInitter;
    }

    void start() {
        START_MIDF_SERVER(wifi_manager);
    }
} // wifi_manager_service
