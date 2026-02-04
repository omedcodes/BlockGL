#pragma once

#include "../../Application/Window.h"
#include "PostProcessEffect.h"

class CrosshairEffect : public PostProcessEffect {
private:
  float crosshairSize = 0.015f;
  float crosshairVerticalWidth = 0.2f;
  float crosshairHorizontalWidth = 0.15f;

public:
  CrosshairEffect(bool enabled)
      : PostProcessEffect(
            AssetManager::instance().loadShaderProgram("assets/shaders/crosshair"),
            enabled) {}

  void renderGui() override {}

  void update() override {
    auto& window = Window::instance();
    float aspectRatio = window.getWindowHeight() == 0 ? 0.0f :
                        static_cast<float>(window.getWindowWidth()) / window.getWindowHeight();

    shader->setFloat("size", crosshairSize);
    shader->setFloat("verticalWidth", crosshairVerticalWidth);
    shader->setFloat("horizontalWidth", crosshairHorizontalWidth);
    shader->setFloat("aspectRatio", aspectRatio);
  }
};
