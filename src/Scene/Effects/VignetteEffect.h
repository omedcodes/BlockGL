#pragma once

#include "PostProcessEffect.h"

class VignetteEffect : public PostProcessEffect {
  float vignetteIntensity = 2.9f;
  float vignetteStart = 2.0f;

public:
  VignetteEffect(bool enabled)
      : PostProcessEffect(
            AssetManager::instance().loadShaderProgram("assets/shaders/vignette_effect"),
            enabled) {}

  void update() override {
    shader->setFloat("intensity", vignetteIntensity);
    shader->setFloat("start", vignetteStart);
  }

  void renderGui() override {
/*
    ImGui::Checkbox("Enable vignette effect", &enabled);

    if (enabled) {
      float invertedIntensity = 4.0f - vignetteIntensity;
      if (ImGui::SliderFloat("Vignette intensity", &invertedIntensity, 1.0f, 3.0f)) {
        vignetteIntensity = 4.0f - invertedIntensity;
      }

      ImGui::SliderFloat("Vignette start", &vignetteStart, 0.0f, 3.0f);
    }
*/
  }
};
