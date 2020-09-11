#pragma once

#include <string>
#include <map>

#include "../protocol/rich_text.hpp"

namespace nxcraft {
namespace game {

class Menu {
    public:
    struct Button {};

    class ButtonGroup {};

    ~Menu();

    void drawImage(std::byte *image, int width, int height, float x, float y);
    void drawImage(std::byte *image, int width, int height, float x, float y, int scaledWidth, int scaledHeight);
    void drawImage(std::byte *image, int width, int height, float x, float y, float scaledWidth, float scaledHeight);

    void drawTexture(std::string name, float x, float y);
    void drawTexture(std::string name, float x, float y, int scaledWidth, int scaledHeight);
    void drawTexture(std::string name, float x, float y, float scaledWidth, float scaledHeight);

    void drawText(std::string text, float x, float y);
    void drawText(protocol::RichText richText, float x, float y);

    void drawLoadingBar(float percentage, float x, float y, int width, int height,
        int barRed, int barGreen, int barBlue, int borderRed, int borderGreen, int borderBlue);

    void drawButton(Button button, float x, float y);
    void drawButton(Button button, float x, float y, float widthScale, float heightScale);
    void drawButton(Button button, float x, float y, int width, int height);

    void drawButtonGroup(ButtonGroup group, float x, float y);

    private:
    std::map<std::byte *, int> nvgImageCache;
};

} // namespace game
} // namespace nxcraft
