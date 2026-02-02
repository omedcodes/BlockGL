#pragma once

#include "../../Application/Window.h"
#include "PostProcessEffect.h"

class CrosshairEffect : public PostProcessEffect {
  float crosshairSize = 0.015f;
  float crosshairVerticalWidth = 0.2f;
  float crosshairHorizontalWidth = 0.15f;

public:
  CrosshairEffect(bool enabled)
      : PostProcessEffect(
            AssetManager::instance().loadShaderProgram("assets/shaders/crosshair"),
            enabled) {}

  void renderGui() override {
/*
    ImGui::Checkbox("Enable crosshair", &enabled);
    if (enabled) {
      ImGui::SliderFloat("Crosshair size", &crosshairSize, 0.01f, 1.0f);
      ImGui::SliderFloat("Crosshair vertical width", &crosshairVerticalWidth, 0.01f, 1.0f);
      ImGui::SliderFloat("Crosshair horizontal width", &crosshairHorizontalWidth, 0.01f, 1.0f);
    }
*/
  }

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
