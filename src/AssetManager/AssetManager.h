#pragma once

#include "../Rendering/Shader.h"
#include "../Rendering/ShaderProgram.h"
#include "../glBlocks.h"
#include "AssetRegistry.h"
#include "CubeMapRegistry.h"
#include "ImageRegistry.h"
#include "ShaderProgramRegistry.h"
#include "ShaderRegistry.h"
#include "TextRegistry.h"
#include "TextureArrayRegistry.h"
#include "TextureRegistry.h"

class AssetManager {
  static AssetManager *instancePtr;

  TextRegistry textRegistry;
  ImageRegistry imageRegistry;
  TextureRegistry textureRegistry;
  TextureArrayRegistry textureArrayRegistry;
  CubeMapRegistry cubeMapRegistry;
  ShaderRegistry shaderRegistry;
  ShaderProgramRegistry shaderProgramRegistry;
};
