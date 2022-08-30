find_package(SDL2 REQUIRED)

set(BASEPATH "${CMAKE_SOURCE_DIR}/src")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/dist")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/dist/lib")

add_library(dino-platform SHARED platform/logger.cpp platform/logger.hpp)

add_library(dino-engine SHARED engine/renderer.cpp engine/renderer.hpp)
target_link_libraries(dino-engine PUBLIC -lSDL2 -lSDL2_image dino-platform)

add_executable(dino-bin game/main.cpp)
target_link_libraries(dino-bin PRIVATE dino-platform dino-engine)