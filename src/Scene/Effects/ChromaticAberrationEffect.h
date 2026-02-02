#pragma once

#include "PostProcessEffect.h"

class ChromaticAberrationEffect : public PostProcessEffect {
  float aberrationStart = 1.5f;
  float aberrationROffset = 0.005f;
  float aberrationGOffset = 0.01f;
  float aberrationBOffset = -0.005f;

public:
  ChromaticAberrationEffect(bool enabled)
      : PostProcessEffect(
            AssetManager::instance().loadShaderProgram("assets/shaders/chromatic_aberration_effect"),
            enabled) {}

  void renderGui() override {
/*
    ImGui::Checkbox("Enable chromatic aberration effect", &enabled);

    if (enabled) {
      ImGui::SliderFloat("Aberration start", &aberrationStart, 0.5f, 3.0f);
      ImGui::SliderFloat("Aberration R Offset", &aberrationROffset, -0.01f, 0.01f);
      ImGui::SliderFloat("Aberration G Offset", &aberrationGOffset, -0.01f, 0.01f);
      ImGui::SliderFloat("Aberration B Offset", &aberrationBOffset, -0.01f, 0.01f);
    }
*/
  }

  void update() override {
    shader->setFloat("start", aberrationStart);
    shader->setFloat("rOffset", aberrationROffset);
    shader->setFloat("gOffset", aberrationGOffset);
    shader->setFloat("bOffset", aberrationBOffset);
  }
};
