#pragma once

#include "../Rendering/VertexArray.h"

class CubeMesh {
private:
  Ref<VertexArray> cubeVertexArray;

public:
  CubeMesh();
  void render() const;
};
