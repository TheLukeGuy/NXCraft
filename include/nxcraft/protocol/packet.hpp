#pragma once

#include "buffer.hpp"

namespace nxcraft {
namespace protocol {

class Packet {
    public:
    virtual int getPacketId() = 0;
    
    virtual void fromBuffer(Buffer buffer) = 0;
    virtual Buffer toBuffer() = 0;
};

} // namespace protocol
} // namespace nxcraft
