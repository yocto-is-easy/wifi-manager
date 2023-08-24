#pragma once

#include <string>
#include <filesystem>
#include <optional>

#include "spdlog/spdlog.h"
#include "boost/property_tree/ptree.hpp"
#include "boost/property_tree/json_parser.hpp"

namespace ptree = boost::property_tree;

class ConfigManager {
private:
    std::string configFilePath_;
    ptree::ptree configTree_;

public:
    ConfigManager(std::string configFilePath = "/etc/wifi-manager/config.json");
    ~ConfigManager();

    void saveParam(std::string key, std::string value);
    std::optional<std::string> loadParam(std::string key);

    void loadAll();
    void saveAll();
};
