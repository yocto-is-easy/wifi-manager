#pragma once

#include <iostream>
#include <string>

#include "IPasswordGenerator.hpp"

class WifiInitter {
private:
    std::string ssid_;
    std::string password_;

    const uint64_t PASSWORD_LENGTH = 14;
    const std::string DEFAULT_UNKNOWN_IP = "0.0.0.0";
    const std::string DEFAULT_UNKNOWN_MAC = "00:00:00:00:00:00";

    bool isNatInitialized_ = false;
    bool isWifiEnabled_ = false;
    bool isHotspotCreated_ = false;

public:
    WifiInitter(std::string ssid, IPasswordGenerator& passwordGenerator);
    ~WifiInitter();

    void init();

    std::string getPassword();
    std::string getSsid();
    std::string getGatewayIp();
    std::string getGatewayMac();
    uint64_t getSpeedMbps();

private:
    void initNat();
    void enableWifi();
    void createWifiHotspot();
};
