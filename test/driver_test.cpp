#include "engine/graphics_driver.hpp"

int main() {
    dino::GraphicsDriver::initialise();

    dino::GraphicsDriver::printInfo();

    dino::GraphicsDriver::quit();

    return EXIT_SUCCESS;
}