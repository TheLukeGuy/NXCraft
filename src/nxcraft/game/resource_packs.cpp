#include "resource_packs.hpp"

#include <fstream>
#include <sstream>

#include "nlohmann/json.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace nxcraft {
namespace game {

ResourcePacks::PackMeta ResourcePacks::getPackMeta(std::string path) {
    std::ifstream stream(path + "/pack.mcmeta");
    nlohmann::json json;
    stream >> json;

    std::byte *icon;
    std::filesystem::path iconPath(path + "/pack.png");
    if (std::filesystem::exists(iconPath)) {
        icon = getImage(iconPath);
    } else {
        icon = getTexture("misc/unknown_pack.png");
    }

    return {
        json["pack"]["pack_format"],
        json["pack"]["description"],
        icon
    };
}

void ResourcePacks::loadResourcePack(std::string path) {
    PackMeta meta = getPackMeta(path);
    loadResourcePack(path, meta);
}

void ResourcePacks::loadResourcePack(std::string path, ResourcePacks::PackMeta meta) {
    resourcePacks.insert(resourcePacks.begin(), {path, meta});
}

std::filesystem::path ResourcePacks::getFilePath(std::string name) {
    for (std::pair<std::string, PackMeta> pack : resourcePacks) {
        std::filesystem::path path(pack.first + "/" + name);
        if (std::filesystem::exists(path)) {
            return path;
        }
    }
}

std::byte * ResourcePacks::getTexture(std::string name) {
    std::filesystem::path path = getFilePath(name);
    return getImage(path);
}

std::byte * ResourcePacks::getImage(std::string path) {
    int width, height;
    getImage(path, &width, &height);
}

std::byte * ResourcePacks::getImage(std::string path, int *width, int *height) {
    stbi_set_flip_vertically_on_load(true);

    int nrChannels;
    return (std::byte *) stbi_load(path.c_str(), width, height, &nrChannels, 0);
}

} // namespace game
} // namespace nxcraft
