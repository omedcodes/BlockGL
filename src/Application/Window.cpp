#include "Window.h"

#include "../Performance/Trace.h"
#include "../Rendering/ColorRenderPass.h"
#include "Application.h"

Window* Window::instancePtr = nullptr;

Window::Window() 
{
    TRACE_FUNCTION();
    assert(instancePtr == nullptr && "The window is already instantiated")L
    instancePtr = this;
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifndef BUILD_TYPE_DIST
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
#endif
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

    window = glfwCreateWindow(windowWidth, windowHeight, name, nullptr, nullptr);
    glfwMakeContextCurrent(window);

    if (window == nullptr) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        return;
    }

    setupCallbacks();
}

Window::~Window() 
{
    TRACE_FUNCTION();
    instancePtr = nullptr;
    glfwTerminate();
}

void Window::onWindowError(int32_t errorCode, const char* description) {
    std::cerr << "GLFW: *ERROR* error=" << errorCode << " description=" << description << std::endl;
}

void Window::onKeyEvent(GLFWwindow *, int32_t key, int32_t scancode, int32_t action, int32_t mode) {
    TRACE_FUNCTION();
    Application::instance().onKeyEvent(key, scancode, action, mode);
}

void Window::onResized(GLFWwindow *, int32_t width, int32_t height) {
  TRACE_FUNCTION();
  Application &app = Application::instance();
  Window &window = app.getWindow();
  window.setWindowHeight(height);
  window.setWindowWidth(width);

  app.onResized(width, height);
}