#include <algorithm>
#include <string.h>
#include "buffer.hpp"

namespace nc {
namespace protocol {

void Buffer::writeByte(std::byte value) {
    buffer.push_back(value);
}

void Buffer::writeBytes(std::vector<std::byte> values) {
    for (std::byte byte : values) {
        writeByte(byte);
    }
}

void Buffer::writeBool(bool value) {
    writeByte((std::byte) value);
}

void Buffer::writeShort(short value) {
    splitAndWriteBytes(value);
}

void Buffer::writeUShort(unsigned short value) {
    splitAndWriteBytes(value);
}

void Buffer::writeInt(int value) {
    splitAndWriteBytes(value);
}

void Buffer::writeLong(long value) {
    splitAndWriteBytes(value);
}

void Buffer::writeFloat(float value) {
    splitAndWriteBytes(value);
}

void Buffer::writeDouble(double value) {
    splitAndWriteBytes(value);
}

void Buffer::writeVarInt(int value) {
    do {
        std::byte temp = (std::byte) (value & 0b01111111);
        value = value >> 7;
        if (value != 0) {
            temp = (std::byte) ((int) temp | 0b10000000);
        }
        writeByte(temp);
    } while (value != 0);
}

void Buffer::writeString(std::string value) {
    writeVarInt(value.length());
    for (char byte : value) {
        if (byte > 0) {
            writeByte((std::byte) byte);
        }
    }
}

void Buffer::writeJson(nlohmann::json value) {
    writeString(value.dump());
}

void Buffer::writeRichText(RichText value) {
    writeJson(value.toJson());
}

void Buffer::writeUuid(std::string value) {
    value.erase(std::remove(value.begin(), value.end(), '-'), value.end());
    writeLong(std::stoul(value.substr(0, 16), nullptr, 16));
    writeLong(std::stoul(value.substr(16, 16), nullptr, 16));
}

std::byte Buffer::readByte() {
    std::byte byte = buffer.at(0);
    buffer.erase(buffer.begin());
    return byte;
}

std::vector<std::byte> Buffer::readBytes(int count) {
    std::vector<std::byte> bytes;
    for (int i = 0; i < count; ++i) {
        bytes.push_back(readByte());
    }
    return bytes;
}

bool Buffer::readBool() {
    return (bool) readByte();
}

short Buffer::readShort() {
    return readAndJoinBytes<short>();
}

unsigned short Buffer::readUShort() {
    return readAndJoinBytes<unsigned short>();
}

int Buffer::readInt() {
    return readAndJoinBytes<int>();
}

long Buffer::readLong() {
    return readAndJoinBytes<long>();
}

float Buffer::readFloat() {
    return readAndJoinBytes<float>();
}

double Buffer::readDouble() {
    return readAndJoinBytes<double>();
}

int Buffer::readVarInt() {
    int numRead = 0;
    int result = 0;

    std::byte read;
    do {
        read = readByte();
        int value = ((int) read & 0b01111111);
        result = result | (value << (7 * numRead));
        ++numRead;
    } while (((int) read & 0b10000000) != 0);

    return result;
}

std::string Buffer::readString() {
    int length = readVarInt();
    std::string string;
    for (int i = 0; i < length; ++i) {
        string += (char) readByte();
    }
    return string;
}

nlohmann::json Buffer::readJson() {
    std::string jsonString = readString();
    return nlohmann::json::parse(jsonString);
}

RichText Buffer::readRichText() {
    return RichText::fromJson(readJson());
}

std::string Buffer::readUuid() {
    std::stringstream stream;
    stream << std::hex << readLong() << readLong();

    std::string uuid = stream.str();
    uuid.insert(8, "-");
    uuid.insert(13, "-");
    uuid.insert(18, "-");
    uuid.insert(23, "-");

    return uuid;
}

template <typename T>
void Buffer::splitAndWriteBytes(T value) {
    std::vector<std::byte> bytes;
    std::byte *pointer = (std::byte *) &value;

    for (unsigned long i = 0; i < sizeof(value); ++i) {
        bytes.push_back(pointer[i]);
    }

    std::reverse(bytes.begin(), bytes.end());
    writeBytes(bytes);
}

template <typename T>
T Buffer::readAndJoinBytes() {
    std::vector<std::byte> bytes = readBytes(sizeof(T));
    std::reverse(bytes.begin(), bytes.end());

    T joined;
    memcpy(&joined, &bytes[0], sizeof(T));
    return joined;
}

template void Buffer::splitAndWriteBytes<short>(short value);
template void Buffer::splitAndWriteBytes<unsigned short>(unsigned short value);
template void Buffer::splitAndWriteBytes<int>(int value);
template void Buffer::splitAndWriteBytes<long>(long value);
template void Buffer::splitAndWriteBytes<float>(float value);
template void Buffer::splitAndWriteBytes<double>(double value);

} // namespace protocol
} // namespace nc
