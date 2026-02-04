#pragma once

#include "../Rendering/ShaderProgram.h"
#include "CubeMesh.h"

class BlockOutline {
private:
  Ref<const ShaderProgram> outlinedBlockShader;
  Ref<const CubeMesh> blockMesh;

public:
  explicit BlockOutline(Ref<const CubeMesh> blockMesh);

  void render(const glm::mat4& transform) const;
};