#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <vector>
#include "socket.hpp"

namespace nc {
namespace protocol {

bool Socket::init() {
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    return sockfd >= 0;
}

bool Socket::connect(std::string address, int port) {
    struct sockaddr_in sockAddr;
    memset(&sockAddr, 0, sizeof(sockAddr));

    sockAddr.sin_family = AF_INET;
    sockAddr.sin_port = htons(port);

    if (inet_pton(AF_INET, address.c_str(), &sockAddr.sin_addr) <= 0) {
        return false;
    }

    return ::connect(sockfd, (struct sockaddr *) &sockAddr, sizeof(sockAddr)) >= 0;
}

bool Socket::disconnect() {
    return close(sockfd) >= 0;
}

bool Socket::writeBuffer(Buffer buffer) {
    buffer.buffer.insert(buffer.buffer.begin(), (std::byte) buffer.buffer.size());
    std::vector<std::byte> copy = buffer.buffer;
    return write(sockfd, &copy[0], copy.size()) >= 0;
}

void Socket::readBuffer(Buffer *buffer) {
    int numRead = 0;
    int length = 0;

    std::byte read;
    do {
        char readBuffer[1];
        recv(sockfd, readBuffer, 1, 0);
        read = (std::byte) readBuffer[0];

        int value = ((int) read & 0b01111111);
        length = length | (value << (7 * numRead));
        ++numRead;
    } while (((int) read & 0b10000000) != 0);

    char oldBuffer[length];
    recv(sockfd, oldBuffer, length, 0);

    for (int i = 0; i < length; ++i) {
        buffer->writeByte((std::byte) oldBuffer[i]);
    }
}

} // namespace protocol
} // namespace nc
