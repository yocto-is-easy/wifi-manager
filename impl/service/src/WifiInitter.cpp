#include <regex>
#include <sstream>
#include <string>

#include "WifiInitter.hpp"

#include "shell/Shell.hpp"

WifiInitter::WifiInitter(std::string ssid, IPasswordGenerator& passwordGenerator) {
    this->ssid_ = ssid;
    this->password_ = passwordGenerator.generate(PASSWORD_LENGTH);
}

WifiInitter::~WifiInitter() {
}

void WifiInitter::init() {
    initNat();
    enableWifi();
    createWifiHotspot();
}

void WifiInitter::initNat() {
    Shell::execute("sysctl -w net.ipv4.ip_forward=1");

    this->isNatInitialized_ = true;
}

void WifiInitter::enableWifi() {
    Shell::execute("connmanctl enable wifi");

    this->isWifiEnabled_ = true;
}

void WifiInitter::createWifiHotspot() {
    Shell::execute("connmanctl tether wifi on " + ssid_ + " " + password_);

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
