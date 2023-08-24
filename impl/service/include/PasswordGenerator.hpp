#pragma once

#include "IPasswordGenerator.hpp"

class PasswordGenerator : public IPasswordGenerator {
private:
    std::string charset_;

public:
    PasswordGenerator(std::string charset);
    ~PasswordGenerator();

    std::string generate(uint32_t length);
};
