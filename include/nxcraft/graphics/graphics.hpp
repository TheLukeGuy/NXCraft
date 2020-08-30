#pragma once

#include <map>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace nxcraft {
namespace graphics {

class Graphics {
    public:
    static GLFWwindow *window;
    static std::map<std::string, unsigned int> shaderCache;

    static bool initGraphics(int width, int height);
    static unsigned int getShader(std::string name);
};

} // namespace graphics
} // namespace nxcraft
