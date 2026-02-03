#pragma once

#include "../BlockGL.h"
#include "../World/World.h"

namespace MovementSimulation {
  bool canMove(const glm::vec3 &from, const glm::vec3 &to, World &world);
};
