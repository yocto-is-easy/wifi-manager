#include "PasswordGenerator.hpp"

#include <string>
#include <random>

PasswordGenerator::PasswordGenerator(std::string charset) {
    this->charset_ = charset;
}

PasswordGenerator::~PasswordGenerator() {
}

std::string PasswordGenerator::generate(uint32_t length) {
    std::random_device randomDevice;
    std::mt19937 generator(randomDevice());
    std::uniform_int_distribution<> distribution(0, charset_.size() - 1);

    std::string password = "";
    for(uint32_t i = 0; i < length; i++) {
        password += charset_[distribution(generator)];
    }

    return password;
}
