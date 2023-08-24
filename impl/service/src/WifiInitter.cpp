#include <regex>
#include <sstream>
#include <string>

#include "spdlog/spdlog.h"

#include "WifiInitter.hpp"

#include "shell/Shell.hpp"

WifiInitter::WifiInitter(std::string ssid, IPasswordGenerator& passwordGenerator) {    
    if(configManager_.loadParam("ssid").has_value()) {
        ssid_ = configManager_.loadParam("ssid").value();
    } else {
        ssid_ = ssid;
        configManager_.saveParam("ssid", ssid);
    }

    if(configManager_.loadParam("password").has_value()) {
        password_ = configManager_.loadParam("password").value();
    } else {
        password_ = passwordGenerator.generate(PASSWORD_LENGTH);
        configManager_.saveParam("password", password_);
    }
}

WifiInitter::~WifiInitter() {
}

void WifiInitter::init() {
    spdlog::info("Initializing wifi...");

    initNat();
    enableWifi();
    createWifiHotspot();

    spdlog::info("Wifi initialized");
}

void WifiInitter::initNat() {
    Shell::CmdResult res = Shell::execute("sysctl -w net.ipv4.ip_forward=1");
    
    spdlog::info("Initialize NAT: {}", res.output);

    this->isNatInitialized_ = true;
}

void WifiInitter::enableWifi() {
    Shell::CmdResult res = Shell::execute("connmanctl enable wifi");

    spdlog::info("Enable wifi: {}", res.output);

    this->isWifiEnabled_ = true;
}

void WifiInitter::createWifiHotspot() {
    Shell::CmdResult res = Shell::execute("connmanctl tether wifi on \'" + ssid_ + "\' \'" + password_ + "\'");
    if(isTetheringEnabled()) {
        throw WifiInitterException("Failed to create wifi hotspot");
    }

    spdlog::info("Create wifi hotspot: {}", res.output);

    this->isHotspotCreated_ = true;
}

std::string WifiInitter::getPassword() {
    return password_;
}

std::string WifiInitter::getSsid() {
    return ssid_;
}

std::string WifiInitter::getGatewayIp() {
    if(!isWifiEnabled_ || !isHotspotCreated_) {
        return DEFAULT_UNKNOWN_IP;
    }

    std::string out = Shell::execute("ip -f inet addr show tether").output;

    std::regex regex("inet ([0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3})\\/");
    std::smatch match;
    std::regex_search(out, match, regex);

    if (match.size() == 2) {
        return match[1];
    } else {
        return DEFAULT_UNKNOWN_IP;
    }
}

std::string WifiInitter::getGatewayMac() {
    if(!isWifiEnabled_ || !isHotspotCreated_) {
        return DEFAULT_UNKNOWN_MAC;
    }

    std::string out = Shell::execute("ip link show tether").output;

    std::regex regex("link\\/ether ([0-9a-fA-F]{2}(?:\\:[0-9a-fA-F]{2}){5}) brd");
    std::smatch match;
    std::regex_search(out, match, regex);

    if (match.size() == 2) {
        return match[1];
    } else {
        return DEFAULT_UNKNOWN_MAC;
    }
}

uint64_t WifiInitter::getSpeedMbps() {
    // TODO: implement
    return 0;
}

bool WifiInitter::isTetheringEnabled() {
    std::string out = Shell::execute("ip link show tether 2>&1").output;

    std::regex regex("can\'t find device");
    std::smatch match;

    return std::regex_search(out, match, regex);
}
