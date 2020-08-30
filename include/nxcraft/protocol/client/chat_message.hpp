#pragma once

#include <string>

#include "../packet.hpp"

namespace nxcraft {
namespace protocol {
namespace client {

class ChatMessagePacket : public Packet {
    public:
    std::string message;

    ChatMessagePacket(std::string message);
    ChatMessagePacket();
    
    virtual int getPacketId();
    
    virtual void fromBuffer(Buffer buffer);
    virtual Buffer toBuffer();
};

} // namespace client
} // namespace protocol
} // namespace nxcraft
