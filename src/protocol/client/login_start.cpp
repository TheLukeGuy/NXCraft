#include "login_start.hpp"

namespace nc {
namespace protocol {
namespace client {

LoginStartPacket::LoginStartPacket(std::string name) : name(name) {}

int LoginStartPacket::getPacketId() {
    return 0x00;
}

void LoginStartPacket::fromBuffer(Buffer buffer) {
    if (buffer.readVarInt() != getPacketId()) {
        return;
    }
    name = buffer.readString();
}

Buffer LoginStartPacket::toBuffer() {
    Buffer buffer;
    buffer.writeVarInt(getPacketId());
    buffer.writeString(name);
    return buffer;
}

} // namespace client
} // namespace protocol
} // namespace nc
