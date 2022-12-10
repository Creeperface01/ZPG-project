#include "Application.h"

#include <memory>
#include <iostream>

#include "window/Window.h"
#include "scene/Scene.h"
#include "util/exceptions.h"
#include "util/callbacks.h"
#include "util/debug.h"
#include "model/ModelRegistry.h"
#include "model/shader/ShaderRegistry.h"
#include "model/texture/TextureRegistry.h"

#include "Demo.h"

Application::Application() {
    initCallbacks();
    initGLFW();
}

Application::Status Application::run() {
    try {
        std::unique_ptr<Window> window(new Window({}));

        initRegistry();

        window->addKeyCallback([&window](const KeyData &data) {
            if (data.action == GLFW_PRESS && data.key == GLFW_KEY_ESCAPE) {
                window->close();
            }
        });

        Demo::run(window.get());

        while (!window->isClosed()) {
            window->draw();
        }
    } catch (std::exception &ex) {
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
        std::cerr << '[' << error << ']' << " - " << description << std::endl;
    });
}

void Application::initRegistry() const {
    ShaderRegistry::get()->registerDefaultShaders();
    TextureRegistry::get()->registerDefaultTextures();
    ModelRegistry::get()->registerDefaultModels();
}
