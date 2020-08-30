#include "chat_message.hpp"

namespace nxcraft {
namespace protocol {
namespace client {

ChatMessagePacket::ChatMessagePacket(std::string message) : message(message) {}

int ChatMessagePacket::getPacketId() {
    return 0x03;
}

void ChatMessagePacket::fromBuffer(Buffer buffer) {
    if (buffer.readVarInt() != getPacketId()) {
        return;
    }
    message = buffer.readString();
}

Buffer ChatMessagePacket::toBuffer() {
    Buffer buffer;
    buffer.writeVarInt(getPacketId());
    buffer.writeString(message);
    return buffer;
}

} // namespace client
} // namespace protocol
} // namespace nxcraft
