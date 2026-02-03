cmake_minimum_required(VERSION 3.22.1)
project(BlockGL)

set(CMAKE_CXX_STANDARD 23)

if (CMAKE_BUILD_TYPE MATCHES Release)
    set(CMAKE_CXX_FLAGS "-O3")
elseif (CMAKE_BUILD_TYPE MATCHES Trace)
    set(CMAKE_CXX_FLAGS "-O3")
    add_compile_definitions(ENABLE_TRACING)
elseif (CMAKE_BUILD_TYPE MATCHES Debug)
    set(CMAKE_CXX_FLAGS "-g")
endif ()

file(GLOB_RECURSE BlockGLSources
    ${CMAKE_SOURCE_DIR}/src/*.cpp
    ${CMAKE_SOURCE_DIR}/src/Application/*.cpp
    ${CMAKE_SOURCE_DIR}/src/AssetManager/*.cpp
    ${CMAKE_SOURCE_DIR}/src/Math/*.cpp
    ${CMAKE_SOURCE_DIR}/src/Performance/*.cpp
    ${CMAKE_SOURCE_DIR}/src/Persistence/*.cpp
    ${CMAKE_SOURCE_DIR}/src/Physics/*.cpp
    ${CMAKE_SOURCE_DIR}/src/Rendering/*.cpp
    ${CMAKE_SOURCE_DIR}/src/Scene/*.cpp
    ${CMAKE_SOURCE_DIR}/src/Scene/Behaviors/*.cpp
    ${CMAKE_SOURCE_DIR}/src/Scene/Effects/*.cpp
    ${CMAKE_SOURCE_DIR}/src/Util/*.cpp
    ${CMAKE_SOURCE_DIR}/src/World/*.cpp
)
add_executable(BlockGL ${BlockGLSources})

target_precompile_headers(BlockGL PRIVATE src/BlockGL.h)

add_subdirectory(third_party/glfw EXCLUDE_FROM_ALL)

add_subdirectory(third_party/GLAD EXCLUDE_FROM_ALL)

add_subdirectory(third_party/glm EXCLUDE_FROM_ALL)

include_directories(BlockGL third_party/FastNoiseLite)
include_directories(BlockGL third_party/FrustumCulling)

add_library(lodepng EXCLUDE_FROM_ALL third_party/lodepng/lodepng.h third_party/lodepng/lodepng.cpp)
include_directories(lodepng third_party/lodepng)

find_package(OpenAL REQUIRED)
find_package(SndFile REQUIRED)
target_link_libraries(BlockGL PRIVATE glfw glm glad lodepng OpenAL::OpenAL sndfile::sndfile)

add_custom_command(
        TARGET BlockGL PRE_BUILD COMMAND
        ${CMAKE_COMMAND} -E create_symlink
        ${CMAKE_SOURCE_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets
)
