#include "Scene.h"

#include <Frustum.h>

#include "../Application/Application.h"
#include "../Math/WorldRayCast.h"
#include "../Performance/Trace.h"
#include "../World/BlockName.h"
#include "Behaviors/BlockBreakParticleBehavior.h"
#include "Behaviors/LavaParticleBehavior.h"

Scene::Scene(const std::string& savePath)
    : persistence(std::make_shared<Persistence>(savePath)),
      world(std::make_shared<World>(
         persistence,
         std::vector{std::static_pointer_cast<WorldBehavior>(std::make_shared<LavaParticleBehavior>()),
                     std::static_pointer_cast<WorldBehavior>(std::make_shared<BlockBreakParticleBehavior>())},
         1337)),
      player(world, persistence) {
  TRACE_FUNCTION();
  onResized(Application::instance().getWindowWidth(), Application::instance().getWindowHeight());
  updateMouse();
}

void Scene::update(float dt) {
  TRACE_FUNCTION();
  deltaTime = dt;
  player.update(deltaTime);
  world->update(player.getCamera().getPosition(), deltaTime);
  skybox.update(projectionMatrix, player.getCamera().getViewMatrix(), deltaTime);
}

void Scene::toggleMenu() {
  isMenuOpen = !isMenuOpen;
  updateMouse();
}

void Scene::updateMouse() {
  TRACE_FUNCTION();
  if (isMenuOpen) {
    player.resetMousePosition();
    Window::instance().unlockMouse();
  } else {
    Window::instance().lockMouse();
  }
}

void Scene::render() {
  TRACE_FUNCTION();
  skybox.render();

  const glm::mat4 mvp = projectionMatrix * player.getCamera().getViewMatrix();
  Frustum frustum(mvp);

  const Camera& camera = player.getCamera();
  const int32_t width = Window::instance().getWindowWidth();
  const int32_t height = Window::instance().getWindowHeight();

  static Ref<Framebuffer> framebuffer = nullptr;
  if (framebuffer == nullptr || framebuffer->getWidth() != width || framebuffer->getHeight() != height) {
    framebuffer = std::make_shared<Framebuffer>(width, height, true, 1);
  }

  Window::instance().getFramebufferStack()->push(framebuffer);
  glClearColor(0, 0, 0, 0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
  world->renderOpaque(mvp, camera.getPosition(), frustum);
  auto opaqueRender = Window::instance().getFramebufferStack()->pop();

  world->renderTransparent(mvp, camera.getPosition(), frustum, zNear, zFar, opaqueRender);


  if (WorldRayCast ray{camera.getPosition(), camera.getLookDirection(), *world, Player::Reach}) {
    outline.render(mvp * glm::translate(ray.getHitTarget().position));
  }

  for (auto& effect: postProcessingEffects) {
    effect->render();
  }
}

void Scene::renderMenu() {}
void Scene::renderIntermediateTextures() {}

void Scene::renderGui() {
  TRACE_FUNCTION();
  if (showIntermediateTextures) {
    renderIntermediateTextures();
  }

  if (isMenuOpen) {
    renderMenu();
  }
}

void Scene::onResized(int32_t width, int32_t height) {
  TRACE_FUNCTION();
  float aspectRatio = width == 0 || height == 0 ? 0 : static_cast<float>(width) / static_cast<float>(height);
  projectionMatrix = glm::perspective<float>(glm::radians(100.0f), aspectRatio, zNear, zFar);
}

void Scene::onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode) {
  TRACE_FUNCTION();
  if (key == GLFW_KEY_ESCAPE) {
    if (action == GLFW_PRESS) {
      toggleMenu();
    }
    return;
  }
  if (!isMenuOpen) {
    player.onKeyEvent(key, scancode, action, mode);
  }
}

void Scene::onMouseButtonEvent(int32_t button, int32_t action, int32_t mods) {
  TRACE_FUNCTION();
  if (!isMenuOpen) {
    player.onMouseButtonEvent(button, action, mods);
  }
}

void Scene::onCursorPositionEvent(double x, double y) {
  TRACE_FUNCTION();
  if (!isMenuOpen) {
    player.onCursorPositionEvent(x, y);
  }
}

void Scene::onScrollEvent(double yOffset) {
  TRACE_FUNCTION();
  if (!isMenuOpen) {
    player.onScrollEvent(yOffset);
  }
}
