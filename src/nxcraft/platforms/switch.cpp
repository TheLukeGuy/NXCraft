#include "switch.hpp"

#if defined (__SWITCH__)

#include <switch.h>

namespace nxcraft {
namespace platforms {

std::string Switch::getName() {
    return "Nintendo Switch";
}

std::pair<int, int> Switch::getDefaultWindowSize() {
    return {1280, 720};
}

std::string Switch::getResourcePath() {
    return "romfs:/";
}

void Switch::init() {
    socketInitializeDefault();
    nxlinkStdio();
    romfsInit();
}

void Switch::deinit() {
    romfsExit();
    socketExit();
}

} // namespace platforms
} // namespace nxcraft

#endif // defined __SWITCH__
