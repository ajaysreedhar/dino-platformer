find_package(SDL2 REQUIRED)

set(BASEPATH "${CMAKE_SOURCE_DIR}/src")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/dist")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/dist/lib")

add_library(dino-platform SHARED platform/logger.cpp platform/logger.hpp)

add_library(dino-engine SHARED
        engine/except.hpp
        engine/sprite_material.cpp engine/sprite_material.hpp
        engine/renderer.cpp engine/renderer.hpp
        engine/audio_mixer.cpp engine/audio_mixer.hpp
        engine/engine_context.cpp engine/engine_context.hpp)
target_link_libraries(dino-engine PUBLIC -lGL -lSDL2 -lSDL2_image dino-platform)
target_include_directories(dino-engine PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

add_executable(dino-bin game/platformer.cpp game/platformer.hpp game/main.cpp)
target_link_libraries(dino-bin PRIVATE dino-platform dino-engine)
target_include_directories(dino-bin PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
