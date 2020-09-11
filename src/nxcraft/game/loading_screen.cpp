#include "loading_screen.hpp"

namespace nxcraft {
namespace game {

std::string LoadingScreen::getName() {
    return "loading_screen";
}

void LoadingScreen::onLoad() {}

void LoadingScreen::onUpdate() {
    drawTexture("gui/options_background.png", 0.5, 0.5, 496, 496);
    drawTexture("font/ascii.png", 0.5, 0.5, 1024, 1024);
}

void LoadingScreen::onUnload() {}

} // namespace game
} // namespace nxcraft
