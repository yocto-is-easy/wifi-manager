#include "shell/Shell.hpp"

#include <iostream>
#include <memory>
#include <string>
#include <sstream>

Shell::CmdResult Shell::execute(const std::string& command) {
    std::shared_ptr<FILE> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        return {Rc::UNKNOWN, ""};
    }

    char buffer[Shell::BUFFER_SIZE];
    std::stringstream result;

    while (!feof(pipe.get())) {
        if (fgets(buffer, Shell::BUFFER_SIZE, pipe.get()) != nullptr) {
            result << buffer;
        }
    }

    return {Rc::SUCCESS, result.str()};
}
