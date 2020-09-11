#pragma once

#include <map>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "nanovg.h"

namespace nxcraft {

class Graphics {
    public:
    static GLFWwindow *window;
    static NVGcontext *vg;

    static int windowX;
    static int windowY;
    static int bufferX;
    static int bufferY;

    static std::map<std::string, unsigned int> shaderCache;

    static bool init(int width, int height);
    static void deinit();

    static bool keepRunning();
    static void beginFrame();
    static void endFrame();

    static unsigned int getShader(std::string name);
};

} // namespace nxcraft
