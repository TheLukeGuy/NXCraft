#include "graphics.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#define NANOVG_GL3_IMPLEMENTATION
#include "nanovg_gl.h"

#include "../global.hpp"

namespace nxcraft {

GLFWwindow *Graphics::window = nullptr;
NVGcontext *Graphics::vg = nullptr;

int Graphics::windowX = 0;
int Graphics::windowY = 0;
int Graphics::bufferX = 0;
int Graphics::bufferY = 0;

std::map<std::string, unsigned int> Graphics::shaderCache = {};

bool Graphics::init(int width, int height) {
    std::cout << "[*] Loading GLFW...\n";
    if (!glfwInit()) {
        std::cout << "[!] Failed to load GLFW.\n";
        return false;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    std::cout << "[*] Creating GLFW window...\n";
    window = glfwCreateWindow(width, height, "NXCraft", nullptr, nullptr);
    if (!window) {
        std::cout << "[!] Failed to create GLFW window.\n";
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    std::cout << "[*] Loading GLAD...\n";
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "[!] Failed to load GLAD.\n";
        glfwTerminate();
        return false;
    }

    std::cout << "[*] GL Vendor: " << glGetString(GL_VENDOR) << "\n";
    std::cout << "[*] GL Renderer: " << glGetString(GL_RENDERER) << "\n";
    std::cout << "[*] GL Version: " << glGetString(GL_VERSION) << "\n";

    std::cout << "[*] Setting OpenGL viewport...\n";
    auto setFramebufferSize = [](GLFWwindow *window, int width, int height) {
        glViewport(0, 0, width, height);
        std::cout << "[*] Set window size: " << width << "x" << height << "\n";
    };
    glfwSetFramebufferSizeCallback(window, setFramebufferSize);
    setFramebufferSize(window, width, height);

    std::cout << "[*] Loading NanoVG...\n";
    vg = nvgCreateGL3(NVG_STENCIL_STROKES);
    if (!vg) {
        std::cout << "[!] Failed to load NanoVG.\n";
        glfwTerminate();
        return false;
    }

    return true;
}

void Graphics::deinit() {
    nvgDeleteGL3(vg);
    glfwTerminate();
}

bool Graphics::keepRunning() {
    return !glfwWindowShouldClose(window);
}

void Graphics::beginFrame() {
    glfwGetWindowSize(window, &windowX, &windowY);
    glfwGetFramebufferSize(window, &bufferX, &bufferY);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    nvgBeginFrame(vg, windowX, windowY, bufferX / windowX);
}

void Graphics::endFrame() {
    nvgEndFrame(vg);

    glfwSwapBuffers(window);
    glfwPollEvents();
}

unsigned int Graphics::getShader(std::string name) {
    if (shaderCache.count(name)) {
        return shaderCache[name];
    }

    unsigned int program = glCreateProgram();
    std::vector<unsigned int> shaders;

    for (unsigned int type : { GL_VERTEX_SHADER, GL_FRAGMENT_SHADER }) {
        std::string extension = type == GL_VERTEX_SHADER ? "vert" : "frag";
        std::ifstream stream(Global::platform->getResourcePath() + "shaders/" + name + "." + extension);

        std::stringstream buffer;
        buffer << stream.rdbuf();

        std::string sourceStr = buffer.str();
        const char *source = sourceStr.c_str();

        unsigned int shader = glCreateShader(type);
        glShaderSource(shader, 1, &source, nullptr);
        glCompileShader(shader);

        int success;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            char log[512];
            glGetShaderInfoLog(shader, 512, nullptr, log);
            std::cout << "[!] Shader compilation failed for " << name << "." << extension << ": " << log;

            glDeleteShader(shader);
            continue;
        }

        glAttachShader(program, shader);
        shaders.push_back(shader);
    }

    glLinkProgram(program);
    glValidateProgram(program);

    for (unsigned int shader : shaders) {
        glDeleteShader(shader);
    }

    shaderCache[name] = program;
    return program;
}

} // namespace nxcraft
