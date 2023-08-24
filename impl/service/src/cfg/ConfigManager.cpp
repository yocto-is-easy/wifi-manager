#include "cfg/ConfigManager.hpp"

ConfigManager::ConfigManager(std::string configFilePath) {
    this->configFilePath_ = configFilePath;
}

ConfigManager::~ConfigManager() {
}

void ConfigManager::saveParam(std::string key, std::string value) {
    configTree_.put(key, value);
    saveAll();
    spdlog::info("Config param saved: {} = {}", key, value);
}

std::optional<std::string> ConfigManager::loadParam(std::string key) {
    loadAll();

    std::string value;
    try {
        value = configTree_.get<std::string>(key);
    } catch(const std::exception& e) {
        spdlog::warn("Config param not found: {}", key);
        return {};
    }
    
    spdlog::info("Config param loaded: {} = {}", key, value);

    return value;
}

void ConfigManager::loadAll() {
    if(!std::filesystem::exists(configFilePath_)) {
        spdlog::warn("Config file not found. Creating new one...");
        saveAll();
    }

    ptree::read_json(configFilePath_, configTree_);
}

void ConfigManager::saveAll() {
    if(!std::filesystem::exists(configFilePath_)) {
        std::filesystem::path configFilePath(configFilePath_);
        std::filesystem::create_directories(configFilePath.parent_path());
    }

    ptree::write_json(configFilePath_, configTree_);
}
