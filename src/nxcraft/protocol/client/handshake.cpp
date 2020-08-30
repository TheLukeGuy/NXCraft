#include "handshake.hpp"

namespace nxcraft {
namespace protocol {
namespace client {

HandshakePacket::HandshakePacket(int protocolVersion, std::string serverAddress, unsigned short serverPort, int nextState) :
    protocolVersion(protocolVersion),
    serverAddress(serverAddress),
    serverPort(serverPort),
    nextState(nextState) {}

int HandshakePacket::getPacketId() {
    return 0x00;
}

void HandshakePacket::fromBuffer(Buffer buffer) {
    if (buffer.readVarInt() != getPacketId()) {
        return;
    }

    protocolVersion = buffer.readVarInt();
    serverAddress = buffer.readString();
    serverPort = buffer.readUShort();
    nextState = buffer.readVarInt();
}

Buffer HandshakePacket::toBuffer() {
    Buffer buffer;
    buffer.writeVarInt(getPacketId());
    buffer.writeVarInt(protocolVersion);
    buffer.writeString(serverAddress);
    buffer.writeUShort(serverPort);
    buffer.writeVarInt(nextState);
    return buffer;
}

} // namespace client
} // namespace protocol
} // namespace nxcraft
