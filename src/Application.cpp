#include "Application.h"

#include <memory>
#include <iostream>
#include <chrono>
#include <ctime>
#include <thread>

#include "window/Window.h"
#include "scene/Scene.h"
#include "util/exceptions.h"
#include "util/callbacks.h"
#include "util/debug.h"
#include "model/ModelRegistry.h"
#include "model/shader/ShaderRegistry.h"
#include "model/texture/TextureRegistry.h"
#include "demo/Demo.h"

using namespace std::chrono_literals;

const int Application::FPS = 60;
const int Application::FRAME_DURATION_NS = static_cast<int>(1000000000.f / static_cast<float>(FPS));

Application::Application() {
    initCallbacks();
    initGLFW();
}

Application::Status Application::run() {
    try {
        std::unique_ptr<Window> window(new Window({}));

        initRegistry();

        window->addKeyCallback([&window](const KeyData& data) {
            if (data.action == GLFW_PRESS && data.key == GLFW_KEY_ESCAPE) {
                window->close();
            }
        });

        Demo demo;
        demo.run(window.get());

        while (!window->isClosed()) {
            auto start = std::chrono::system_clock::now();
            window->draw();
            auto end = std::chrono::system_clock::now();

            auto render_duration = end - start;
            auto sleepDuration = std::chrono::nanoseconds(FRAME_DURATION_NS) - render_duration;

            std::this_thread::sleep_for(sleepDuration);
        }
    } catch (std::exception& ex) {
        std::cerr << ex.what() << std::endl;
        debugGlCall(glfwTerminate);
        return Application::Status::ERROR;
    }

    debugGlCall(glfwTerminate);
    return Application::Status::SUCCESS;
}

void Application::initGLFW() const {
    if (!debugGlCall(glfwInit)) {
        throw GlfwException("Could not initialize GLFW");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void Application::initCallbacks() const {
    debugGlCall(glfwSetErrorCallback, [](int error, const char *description) {
                throw std::runtime_error("[" + std::to_string(error) + "]" + " - " + description);
                });
}

void Application::initRegistry() const {
    ShaderRegistry::get()->registerDefaultShaders();
    TextureRegistry::get()->registerDefaultTextures();
    ModelRegistry::get()->registerDefaultModels();
}
