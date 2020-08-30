#pragma once

#include <string>

#include "../packet.hpp"

namespace nxcraft {
namespace protocol {
namespace client {

class LoginStartPacket : public Packet {
    public:
    std::string name;

    LoginStartPacket(std::string name);
    LoginStartPacket();
    
    virtual int getPacketId();
    
    virtual void fromBuffer(Buffer buffer);
    virtual Buffer toBuffer();
};

} // namespace client
} // namespace protocol
} // namespace nxcraft
