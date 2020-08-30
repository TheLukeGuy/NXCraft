#pragma once

#include <string>

#include "socket.hpp"
#include "packet.hpp"

namespace nxcraft {
namespace protocol {

class Client {
    public:
    Socket socket;

    Client();

    bool connect(std::string address, int port);
    bool disconnect();

    bool sendPacket(Packet *packet);
    
    void sendChat(std::string message);
};

} // namespace protocol
} // namespace nxcraft
