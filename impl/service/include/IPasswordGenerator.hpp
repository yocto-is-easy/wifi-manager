#pragma once

#include <string>

#include <stdint.h>

class IPasswordGenerator {
public:
    virtual std::string generate(uint32_t length) = 0;
};