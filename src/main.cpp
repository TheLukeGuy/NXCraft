#include <iostream>

#include "nxcraft.hpp"

using namespace nxcraft;

int main() {
    #if defined (__SWITCH__)
    Global::platform = new platforms::Switch();
    #else
    std::cout << "[!] Your platform is not supported. However, NXCraft is open-source so you can add it yourself.";
    return EXIT_FAILURE;
    #endif

    Global::platform->init();

    std::cout << "[*] Welcome to NXCraft!\n";

    std::cout << "[*] Platform: " << Global::platform->getName() << "\n";
    std::cout << "[*] NXCraft Version: " << Constants::NXCRAFT_VERSION << "\n";
    std::cout << "[*] NXCraft Pre-Release: " << (Constants::NXCRAFT_PRE_RELEASE ? "Yes" : "No") << "\n";
    std::cout << "[*] Minecraft Version: " << Constants::MINECRAFT_VERSION << "\n";
    std::cout << "[*] Asset Version: " << Constants::ASSET_VERSION << "\n";
    std::cout << "[*] Protocol Version: " << Constants::PROTOCOL_VERSION << "\n";

    game::ResourcePacks::loadResourcePack(Global::platform->getResourcePath() + "pack");

    std::pair<int, int> defaultWindowSize = Global::platform->getDefaultWindowSize();
    if (!graphics::Graphics::initGraphics(defaultWindowSize.first, defaultWindowSize.second)) {
        std::cout << "[!] Failed to initialize graphics. Exiting...\n";
        
        Global::platform->deinit();
        return EXIT_FAILURE;
    }

    while (!glfwWindowShouldClose(graphics::Graphics::window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glfwSwapBuffers(graphics::Graphics::window);
        glfwPollEvents();
    }

    glfwTerminate();
    Global::platform->deinit();
    return EXIT_SUCCESS;
}
