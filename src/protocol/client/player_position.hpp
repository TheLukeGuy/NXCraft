#pragma once

#include "../packet.hpp"

namespace nc {
namespace protocol {
namespace client {

class PlayerPositionPacket : public Packet {
    public:
    double x;
    double feetY;
    double z;
    bool onGround;

    PlayerPositionPacket(double x, double feetY, double z, bool onGround);
    PlayerPositionPacket();
    
    virtual int getPacketId();
    
    virtual void fromBuffer(Buffer buffer);
    virtual Buffer toBuffer();
};

} // namespace client
} // namespace protocol
} // namespace nc
