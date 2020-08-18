#pragma once

#include <vector>
#include <string>
#include <sstream>
#include <nlohmann/json.hpp>
#include "rich_text.hpp"

namespace nc {
namespace protocol {

class Buffer {
    public:
    std::vector<std::byte> buffer;

    void writeByte(std::byte value);
    void writeBytes(std::vector<std::byte> values);
    void writeBool(bool value);
    void writeShort(short value);
    void writeUShort(unsigned short value);
    void writeInt(int value);
    void writeLong(long value);
    void writeFloat(float value);
    void writeDouble(double value);
    void writeVarInt(int value);
    void writeString(std::string value);
    void writeJson(nlohmann::json value);
    void writeRichText(RichText value);
    void writeUuid(std::string value);

    std::byte readByte();
    std::vector<std::byte> readBytes(int count);
    bool readBool();
    short readShort();
    unsigned short readUShort();
    int readInt();
    long readLong();
    float readFloat();
    double readDouble();
    int readVarInt();
    std::string readString();
    nlohmann::json readJson();
    RichText readRichText();
    std::string readUuid();

    private:
    template <typename T>
    void splitAndWriteBytes(T value);
    template <typename T>
    T readAndJoinBytes();
};

} // namespace protocol
} // namespace nc
