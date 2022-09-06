#include "platform/filesystem.hpp"
#include "platform/logger.hpp"
#include "engine/graphics_driver.hpp"

int main() {
    dino::Logger::print(dino::Filesystem::resource("texture", "001.png"));
    dino::Logger::print(dino::Filesystem::resource("audio", "001.wav"));

    dino::GraphicsDriver::initialise();

    dino::GraphicsDriver::printInfo();

    dino::GraphicsDriver::quit();

    return EXIT_SUCCESS;
}