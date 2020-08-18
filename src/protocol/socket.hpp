#pragma once

#include <string>
#include "buffer.hpp"

namespace nc {
namespace protocol {

class Socket {
    public:
    bool init();

    bool connect(std::string address, int port);
    bool disconnect();

    bool writeBuffer(Buffer buffer);
    void readBuffer(Buffer *buffer);

    private:
    int sockfd;
};

} // namespace protocol
} // namespace nc
