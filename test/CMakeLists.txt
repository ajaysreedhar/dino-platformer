find_package(SDL2 REQUIRED)

set(BASEPATH "${CMAKE_SOURCE_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/dist/test")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/dist/test")

# ---
# Testing graphics driver
# -
# Executable: driver-test
# =========================================================================
add_executable(driver-test driver_test.cpp)
target_link_libraries(driver-test PRIVATE dino-platform dino-engine)
target_include_directories(driver-test PRIVATE "${CMAKE_SOURCE_DIR}/src")
