#pragma once

#include "../BlockGL.h"
#include "../Physics/MovementSimulation.h"
#include "../World/World.h"
#include "Camera.h"

class Player {
private:
  // The player is 0.6 blocks wide and 1.8 blocks tall, the eyes are approximately 0.3 units from the top

  Camera camera;

  Ref<World> world;
  Ref<Persistence> persistence;

  static constexpr int HotbarSize = 9;
  BlockData::BlockType blockToPlace = BlockData::BlockType::grass; // this variable holds current chosen block default=grass

  std::array<BlockData::BlockType, HotbarSize> hotbar = {
      BlockData::BlockType::grass,
      BlockData::BlockType::dirt,
      BlockData::BlockType::stone,
      BlockData::BlockType::sand,
      BlockData::BlockType::planks,
      BlockData::BlockType::cobblestone,
      BlockData::BlockType::oak_wood,
      BlockData::BlockType::glass,
      BlockData::BlockType::oak_leaves
  };
  int selectedHotbarSlot = 0;

  glm::vec3 gravity{0};

  float playerSpeedMovement = 1.14395f;
  float mouseSensitivity = .5;

  float gravityConstant = DefaultGravity;
  float playerJumpPower = 1.3;
  bool canJump = true;

  bool isRunning = false;
  bool survivalMode = true;  // i decided to set the player by default to survival
  bool shouldResetMouse = true;

public:
  static constexpr AABB PlayerAABB = AABB{
     {-0.3, -1.5, -0.3},
     {0.3, 0.3, 0.3},
  };

  static constexpr std::array<glm::vec3, 8> PlayerBoundingBox = {{
     {0.3, 0.3, 0.3},
     {0.3, 0.3, -0.3},
     {-0.3, 0.3, 0.3},
     {-0.3, 0.3, -0.3},
     {0.3, -1.5, 0.3},
     {0.3, -1.5, -0.3},
     {-0.3, -1.5, 0.3},
     {-0.3, -1.5, -0.3},
  }};

  static constexpr float DefaultGravity = 46.62f;
  static constexpr float Reach = 4.5f;

  explicit Player(const Ref<World> &world, const Ref<Persistence> &persistence);
  ~Player();

  void update(float deltaTime);

  [[nodiscard]] bool getIsSurvivalMode() const { return survivalMode; };
  void setSurvivalMovement(bool isSurvival) {
    gravity = glm::vec3(0);
    survivalMode = isSurvival;
  };

  [[nodiscard]] const Camera &getCamera() const { return camera; };

  [[nodiscard]] float getJumpHeightMultiplier() const { return playerJumpPower; };
  void setJumpHeightMultiplier(float multiplier) { playerJumpPower = multiplier; };

  [[nodiscard]] float getGravityConstant() const { return gravityConstant; };
  void setGravityConstant(float constant) { gravityConstant = constant; };

  [[nodiscard]] float getMovementSpeedMultiplier() const { return playerSpeedMovement; };
  void setMovementSpeedMultiplier(float movementSpeed) { playerSpeedMovement = movementSpeed; }

  [[nodiscard]] float getJumpSpeed() const { return playerJumpPower * gravityConstant / 4.5f; };
  [[nodiscard]] float getWalkingSpeed() const { return playerSpeedMovement * 4.317f; };
  [[nodiscard]] float getRunningSpeed() const { return playerSpeedMovement * 5.612f; };

  [[nodiscard]] BlockData::BlockType getBlockToPlace() const { return blockToPlace; };
  void setBlockToPlace(BlockData::BlockType block) { blockToPlace = block; };

  void onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode);
  void onMouseButtonEvent(int32_t button, int32_t action, int32_t mods);
  void onCursorPositionEvent(double d, double d1);
  void onScrollEvent(double yOffset);

  void resetMousePosition();
};
