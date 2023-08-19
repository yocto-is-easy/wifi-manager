#pragma once

#include <string>

#include <stdint.h>

#include <midf.hpp>

MIDF_DECL_PORT(wifi_manager, 25002);

MIDF_DECL_FUNC_NO_ARGS(std::string, wifi_manager, get_wifi_ssid);
MIDF_DECL_FUNC_NO_ARGS(std::string, wifi_manager, get_wifi_password);
MIDF_DECL_FUNC_NO_ARGS(std::string, wifi_manager, get_wifi_gateway_ip);
MIDF_DECL_FUNC_NO_ARGS(std::string, wifi_manager, get_wifi_gateway_mac);
MIDF_DECL_FUNC_NO_ARGS(int64_t, wifi_manager, get_wifi_speed_mbps);
