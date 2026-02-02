#pragma once

#include <vector>

#include "../glBlocks.h"
#include "Buffer.h"


struct VertexAttribute {
  enum ComponentType {
    UShort = GL_UNSIGNED_SHORT,
    Int = GL_INT,
    UInt = GL_UNSIGNED_INT,
    Byte = GL_BYTE,
    Float = GL_FLOAT,
  };

  uint8_t componentCount;
  ComponentType type;
  bool shouldBeNormalized = false;
  int32_t vertexSize;
  uint32_t offset;

  VertexAttribute(uint8_t componentCount, ComponentType type, uint32_t offset)
      : componentCount(componentCount),
        type(type),
        shouldBeNormalized(false),
        vertexSize(0),
        offset(offset) {}
};