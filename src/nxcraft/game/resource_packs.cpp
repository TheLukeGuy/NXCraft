#include "resource_packs.hpp"

#include <fstream>
#include <sstream>

#include "nlohmann/json.hpp"
#include "stb_image.h"
#include "nanovg.h"

#include "../graphics.hpp"

namespace nxcraft {
namespace game {

std::map<std::string, ResourcePacks::PackMeta> ResourcePacks::resourcePacks = {};

std::map<std::string, ResourcePacks::TextureCache> ResourcePacks::textureCache = {};

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

void ResourcePacks::clearCaches() {
    for (std::pair<std::string, TextureCache> cache : textureCache) {
        stbi_image_free(cache.second.texture);
    }
    textureCache.clear();
}

void ResourcePacks::loadResourcePack(std::string path) {
    clearCaches();
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
    return "";
}

std::byte * ResourcePacks::getTexture(std::string name) {
    int width, height, nrChannels;
    return getTexture(name, &width, &height, &nrChannels);
}

std::byte * ResourcePacks::getTexture(std::string name, int *width, int *height) {
    int nrChannels;
    return getTexture(name, width, height, &nrChannels);
}

std::byte * ResourcePacks::getTexture(std::string name, int *width, int *height, int *nrChannels) {
    if (textureCache.count(name)) {
        TextureCache cache = textureCache[name];
        *width = cache.width;
        *height = cache.height;
        *nrChannels = cache.nrChannels;
        return cache.texture;
    }

    std::filesystem::path path = getFilePath("assets/minecraft/textures/" + name);
    std::byte *image = getImage(path, width, height, nrChannels);

    textureCache[name] = {image, *width, *height, *nrChannels};
    return image;
}

std::byte * ResourcePacks::getImage(std::string path) {
    int width, height;
    return getImage(path, &width, &height);
}

std::byte * ResourcePacks::getImage(std::string path, int *width, int *height) {
    int nrChannels;
    return getImage(path, width, height, &nrChannels);
}

std::byte * ResourcePacks::getImage(std::string path, int *width, int *height, int *nrChannels) {
    stbi_set_unpremultiply_on_load(true);
    stbi_convert_iphone_png_to_rgb(true);
    return (std::byte *) stbi_load(path.c_str(), width, height, nrChannels, 4);
}

} // namespace game
} // namespace nxcraft
