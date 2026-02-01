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

void Window::onMouseButtonEvent(GLFWwindow *, int32_t button, int32_t action, int32_t mods) {
  TRACE_FUNCTION();
  Application::instance().onMouseButtonEvent(button, action, mods);
}

void Window::onCursorPosition(GLFWwindow *, double x, double y) {
  TRACE_FUNCTION();
  Application::instance().onCursorPositionEvent(x, y);
}

void Window::onRefreshWindow(GLFWwindow *) {
  TRACE_FUNCTION();
  Application::instance().onRefreshWindow();
}

void Window::setupCallbacks() {
  TRACE_FUNCTION();
  glfwSetKeyCallback(window, onKeyEvent);
  glfwSetMouseButtonCallback(window, onMouseButtonEvent);
  glfwSetCursorPosCallback(window, onCursorPosition);
  glfwSetFramebufferSizeCallback(window, onResized);

#ifndef BUILD_TYPE_DIST
  glEnable(GL_DEBUG_OUTPUT);
  glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
  glDebugMessageCallback(onOpenGlMessage, nullptr);
  glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
#endif
  glfwSwapInterval(1);

  glfwSetWindowRefreshCallback(window, onRefreshWindow);
  glfwSetErrorCallback(Window::onWindowError);
}

bool Window::setupGlad() {
  TRACE_FUNCTION();
  if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
    std::cerr << "Failed to initialize OpenGL context" << std::endl;
    return false;
  }

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);

  return true;
}

void Window::lockMouse() {
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

