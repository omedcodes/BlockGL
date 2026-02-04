#pragma once

#include "PostProcessEffect.h"

class VignetteEffect : public PostProcessEffect {
private:
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

  void renderGui() override {}
};
