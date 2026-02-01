#include "Persistence.h"

#include <cstdlib>

#include "../Performance/Trace.h"

#define SERIALIZE_DATA

Persistence::Persistence(std::string newPath) : path(std::move(newPath)) {
  TRACE_FUNCTION();
#ifdef SERIALIZE_DATA
  std::ifstream file(path, std::ios::in | std::ios::binary);
  if (!file) {
    std::cerr << "Failed to open the file: " << path << std::endl;
    return;
  }

  file.seekg(0, std::ios::end);
  auto length = size_t(file.tellg());
  if (length == -1) {
    std::cerr << "Failed to read the file: " << path << std::endl;
    return;
  }

  file.seekg(0, std::ios::beg);

  file.read(reinterpret_cast<char*>(&camera), sizeof(camera));
  size_t chunkCount = (length - sizeof(Camera)) / (sizeof(glm::ivec2) + sizeof(Chunk::data));

  for (size_t i = 0; i < chunkCount; i++) {
    TRACE_SCOPE("Persistence::Persistence::loadChunk");
    glm::ivec2 worldPosition;
    file.read(reinterpret_cast<char*>(&worldPosition[0]), sizeof(glm::ivec2));

    Ref<Chunk> chunk = std::make_shared<Chunk>(worldPosition);
    file.read(reinterpret_cast<char*>(&chunk->data[0]), sizeof(Chunk::data));

    chunks[worldPosition] = chunk;
  }
#endif
}