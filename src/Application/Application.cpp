#include "Application.h"

#include "../Performance/Trace.h"

Application* Application::instancePtr = nullptr;

Application::Application() {
  assert(instancePtr == nullptr && "The application is already instantiated");
  instancePtr = this;
}

Application::~Application() {
  instancePtr = nullptr;
}

int32_t Application::run() {
  TRACE_FUNCTION();
  if (!scene || !window.isValid()) {
    return -1;
  }

  lastTick = Clock::now();
  while (!window.shouldClose()) {
    window.pollEvents();
    updateAndRender();
  }
  return 0;
}

void Application::updateAndRender() {
  TRACE_FUNCTION();

  TimePoint now = Clock::now();
  float deltaTime = static_cast<float>((now - lastTick).count()) / 1000000000.0f;
  lastTick = now;

  scene->update(deltaTime);

  if (window.shouldRender()) {
    TRACE_SCOPE("Window::render");
    window.beginFrame();
    scene->render();
    window.finalizeFrame();

    gui.beginFrame();
    scene->renderGui();
    gui.finalizeFrame();

    window.swapBuffers();
  }
}