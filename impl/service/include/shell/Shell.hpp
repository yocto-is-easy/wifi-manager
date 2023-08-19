#pragma once

#include <string>

class Shell {
public:
    enum class Rc {
        NO_COMMAND_FOUND = 127,
        SUCCESS = 0,
        
        UNKNOWN = -256
    };

    struct CmdResult {
        Rc rc;
        std::string output;
    };

private:
    static constexpr uint64_t BUFFER_SIZE = 256;

public:
    static CmdResult execute(const std::string& command);

};
