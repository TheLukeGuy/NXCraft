#pragma once

#include <string>

#include "../packet.hpp"

namespace nxcraft {
namespace protocol {
namespace client {

class HandshakePacket : public Packet {
    public:
    int protocolVersion;
    std::string serverAddress;
    unsigned short serverPort;
    int nextState;

    HandshakePacket(int protocolVersion, std::string serverAddress, unsigned short serverPort, int nextState);
    HandshakePacket();
    
    virtual int getPacketId();
    
    virtual void fromBuffer(Buffer buffer);
    virtual Buffer toBuffer();
};

} // namespace client
} // namespace protocol
} // namespace nxcraft
