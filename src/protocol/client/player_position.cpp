#include "player_position.hpp"

namespace nc {
namespace protocol {
namespace client {

PlayerPositionPacket::PlayerPositionPacket(double x, double feetY, double z, bool onGround) :
    x(x),
    feetY(feetY),
    z(z),
    onGround(onGround) {}

int PlayerPositionPacket::getPacketId() {
    return 0x12;
}

void PlayerPositionPacket::fromBuffer(Buffer buffer) {
    if (buffer.readVarInt() != getPacketId()) {
        return;
    }

    x = buffer.readDouble();
    feetY = buffer.readDouble();
    z = buffer.readDouble();
    onGround = buffer.readBool();
}

Buffer PlayerPositionPacket::toBuffer() {
    Buffer buffer;
    buffer.writeVarInt(getPacketId());
    buffer.writeDouble(x);
    buffer.writeDouble(feetY);
    buffer.writeDouble(z);
    buffer.writeBool(onGround);
    return buffer;
}

} // namespace client
} // namespace protocol
} // namespace nc
