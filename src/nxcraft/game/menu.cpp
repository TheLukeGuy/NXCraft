#include "menu.hpp"

#include "nanovg.h"

#include "../graphics.hpp"
#include "resource_packs.hpp"

namespace nxcraft {
namespace game {

Menu::~Menu() {
    for (std::pair<std::byte *, int> cache : nvgImageCache) {
        nvgDeleteImage(Graphics::vg, cache.second);
    }
}

void Menu::drawImage(std::byte *image, int width, int height, float x, float y) {
    drawImage(image, width, height, x, y, width, height);
}

void Menu::drawImage(std::byte *image, int width, int height, float x, float y, int scaledWidth, int scaledHeight) {
    int actualX = Graphics::windowX * x;
    int actualY = Graphics::windowY * y;

    int topLeftX = actualX - (scaledWidth / 2);
    int topLeftY = actualY - (scaledHeight / 2);

    int nvgImage = 0;
    if (scaledWidth == scaledHeight && width == height && scaledWidth > width && scaledWidth % width == 0) {
        int pixelSize = scaledWidth / width;

        for (int row = 0; row < height; ++row) {
            for (int column = 0; column < width; ++column) {
                int pixelX = topLeftX + (pixelSize * column);
                int pixelY = topLeftY + (pixelSize * row);

                int colorIndex = (row * width) + column;
                unsigned char *red = (unsigned char *) &image[colorIndex * 4];
                NVGcolor pixelColor = nvgRGBA(*red, *(red + 1), *(red + 2), *(red + 3));

                nvgBeginPath(Graphics::vg);
                nvgRect(Graphics::vg, pixelX, pixelY, pixelSize, pixelSize);
                nvgFillColor(Graphics::vg, pixelColor);
                nvgFill(Graphics::vg);
            }
        }

        return;
    } else if (nvgImageCache.count(image)) {
        nvgImage = nvgImageCache[image];
    } else {
        nvgImage = nvgCreateImageRGBA(Graphics::vg, width, height, 0, (unsigned char *) image);
        nvgImageCache[image] = nvgImage;
    }

    NVGpaint paint = nvgImagePattern(Graphics::vg, topLeftX, topLeftY, scaledWidth, scaledHeight, 0, nvgImage, 1);
    nvgBeginPath(Graphics::vg);
    nvgRect(Graphics::vg, topLeftX, topLeftY, scaledWidth, scaledHeight);
    nvgFillPaint(Graphics::vg, paint);
    nvgFill(Graphics::vg);
}

void Menu::drawImage(std::byte *image, int width, int height, float x, float y, float scaledWidth, float scaledHeight) {
    int actualHeight = Graphics::windowX * scaledWidth;
    int actualWidth = Graphics::windowY * scaledHeight;
    drawImage(image, width, height, x, y, actualWidth, actualWidth);
}

void Menu::drawTexture(std::string name, float x, float y) {
    int width, height;
    std::byte *image = ResourcePacks::getTexture(name, &width, &height);
    drawImage(image, width, height, x, y);
}

void Menu::drawTexture(std::string name, float x, float y, int scaledWidth, int scaledHeight) {
    int width, height;
    std::byte *image = ResourcePacks::getTexture(name, &width, &height);
    drawImage(image, width, height, x, y, scaledWidth, scaledHeight);
}

void Menu::drawTexture(std::string name, float x, float y, float scaledWidth, float scaledHeight) {
    int width, height;
    std::byte *image = ResourcePacks::getTexture(name, &width, &height);
    drawImage(image, width, height, x, y, scaledWidth, scaledHeight);
}

} // namespace game
} // namespace nxcraft
