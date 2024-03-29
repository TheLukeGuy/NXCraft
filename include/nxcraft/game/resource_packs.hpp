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

    struct TextureCache {
        std::byte *texture;
        int width;
        int height;
        int nrChannels;
    };

    static std::map<std::string, PackMeta> resourcePacks;

    static std::map<std::string, TextureCache> textureCache;

    static PackMeta getPackMeta(std::string path);
    static void clearCaches();

    static void loadResourcePack(std::string path);
    static void loadResourcePack(std::string path, PackMeta meta);

    static std::filesystem::path getFilePath(std::string name);

    static std::byte * getTexture(std::string name);
    static std::byte * getTexture(std::string name, int *width, int *height);
    static std::byte * getTexture(std::string name, int *width, int *height, int *nrChannels);

    private:
    static std::byte * getImage(std::string path);
    static std::byte * getImage(std::string path, int *width, int *height);
    static std::byte * getImage(std::string path, int *width, int *height, int *nrChannels);
};

} // namespace game
} // namespace nxcraft
