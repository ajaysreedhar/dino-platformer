/**
 * graphics_driver.cpp - Graphics driver abstraction
 * ------------------------------------------------------------------------
 *
 * MIT License
 *
 * Copyright (c) 2022-present Ajay Sreedhar
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * ========================================================================
 */

#include "platform/standard.hpp"

#if defined (DINO_OS_TYPE_WINDOWS) && DINO_OS_TYPE_WINDOWS == 1
#include <SDL.h>
#elif defined (DINO_OS_TYPE_LINUX) && DINO_OS_TYPE_LINUX == 1 
#include <SDL2/SDL.h>
#endif // DINO_OS_TYPE_WINDOWS or DINO_OS_TYPE_LINUX

#include "platform/logger.hpp"
#include "assert.hpp"
#include "graphics_driver.hpp"

// IMPLEMENTATION IS INCOMPLETE

dino::DisplayCaps dino::GraphicsDriver::s_displayCaps {};

void dino::GraphicsDriver::initDisplay_() {
    int display_len = SDL_GetNumVideoDisplays();
    DINO_ASSERT_SDL_RESULT(display_len);

    for (int index = 0; index < display_len; index++) {
        SDL_DisplayMode display_mode;
        SDL_Rect display_bounds {};

        int result = SDL_GetDesktopDisplayMode(index, &display_mode);
        DINO_ASSERT_SDL_RESULT(result);

        result = SDL_GetDisplayBounds(index, &display_bounds);
        DINO_ASSERT_SDL_RESULT(result);

        if (display_bounds.x == 0 && display_bounds.y == 0) {
            s_displayCaps.displayIndex = index;
            s_displayCaps.screenWidth  = display_bounds.w;
            s_displayCaps.screenHeight = display_bounds.h;
            s_displayCaps.displayName  = std::string(SDL_GetDisplayName(index));

            break;
        }
    }
}

void dino::GraphicsDriver::initialise() {
    if (!(SDL_INIT_VIDEO & SDL_WasInit(SDL_INIT_VIDEO))) {
        SDL_Init(SDL_INIT_VIDEO);
    }

    initDisplay_();
}

void dino::GraphicsDriver::quit() {
    SDL_VideoQuit();
    SDL_Quit();
}

void dino::GraphicsDriver::printInfo() {
    dino::Logger::print("Display Information");
    dino::Logger::print("*******************");
    dino::Logger::print("Index: ", s_displayCaps.displayIndex);
    dino::Logger::print("Name: ", s_displayCaps.displayName);
    dino::Logger::print("Resolution: ", s_displayCaps.screenWidth, "x", s_displayCaps.screenHeight);
    dino::Logger::print("\n");
}

const dino::DisplayCaps *dino::GraphicsDriver::getDisplayCaps() {
    return &s_displayCaps;
}
