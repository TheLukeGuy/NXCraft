#include "client.hpp"
#include "client/chat_message.hpp"

namespace nc {
namespace protocol {

Client::Client() {
    socket = Socket();
    socket.init();
}

bool Client::connect(std::string address, int port) {
    return socket.connect(address, port);
}

bool Client::disconnect() {
    return socket.disconnect();
}

bool Client::sendPacket(Packet *packet) {
    Buffer buffer = packet->toBuffer();
    return socket.writeBuffer(buffer);
}

void Client::sendChat(std::string message) {
    client::ChatMessagePacket packet(message);
    sendPacket(&packet);
}

} // namespace protocol
} // namespace nc
