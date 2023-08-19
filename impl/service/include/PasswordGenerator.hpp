#pragma once

#include "IPasswordGenerator.hpp"

class PasswordGenerator : public IPasswordGenerator {
private:
    std::string charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

public:
    PasswordGenerator(std::string charset);
    ~PasswordGenerator();

    std::string generate(uint32_t length);
};
