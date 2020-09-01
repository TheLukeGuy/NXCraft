#pragma once

#include <string>
#include <map>
#include <filesystem>

namespace nxcraft {
namespace game {

class ResourcePacks {
    public:
    struct PackMeta {
        int format;
        std::string description;
        std::byte * icon;
    };

    static std::map<std::string, PackMeta> resourcePacks;
    static std::map<std::string, std::byte *> textureCache;

    static PackMeta getPackMeta(std::string path);
    static void loadResourcePack(std::string path);
    static void loadResourcePack(std::string path, PackMeta meta);

    static std::filesystem::path getFilePath(std::string name);
    static std::byte * getTexture(std::string name);

    private:
    static std::byte * getImage(std::string path);
    static std::byte * getImage(std::string path, int *width, int *height);
};

} // namespace game
} // namespace nxcraft
