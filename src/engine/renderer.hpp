/**
 * renderer.hpp - Renderer module for displaying contents on the screen
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

#pragma once

#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include "assert.hpp"
#include "sprite_material.hpp"

namespace dino {

/**
 * @brief Window on to which renderer should display contents.
 */
struct target_window {
    int width = 800;
    int height = 600;
    SDL_Window* window = nullptr;

    /**
     * @brief Creates a window of specified width and height.
     *
     * @param title     Window title.
     * @param width     Window width.
     * @param height    Window height.
     */
    target_window(const std::string& title, int width, int height) {
        this->width = width;
        this->height = height;

        this->window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, this->width, this->height, SDL_WINDOW_VULKAN);
        DINO_ASSERT_SDL_HANDLE(this->window, dino::EngineError::E_TYPE_SDL_RESULT)

        SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN | SDL_WINDOW_FULLSCREEN_DESKTOP);
    }
};

typedef struct target_window TargetWindow;

/**
 * @brief Handles rendering operations.
 */
class Renderer {

private:
    /**
     * @brief SDL renderer handle.
     */
    SDL_Renderer* m_renderer;

public:
    /**
     * @brief Initialises with a target window.
     * @param window The window handle.
     * @throw EngineError Thrown if the constructor fails.
     */
    explicit Renderer(dino::TargetWindow*);

    /**
     * @brief Cleans up when an instance is destroyed.
     *
     * Destroys the SDL renderer upon exit.
     */
    ~Renderer();

    /**
     * @brief Loads a sprite material from an image.
     * @param image_file Absolute path to the image.
     * @return The sprite material.
     * @throw EngineError Thrown if sprite can not be loaded.
     */
    SpriteMaterial* loadSprite(const std::string&);

    /**
     * @brief Clears the screen before rendering the next frame.
     */
    void clear();

    /**
     * @brief Begins rendering a frame.
     *
     * The method is an alias for the Renderer::clear() method.
     */
    void begin();

    /**
     * @brief Copies a list of sprite materials to the renderer buffer.
     * @param materials Vector containing the sprite materials.
     * @throw EngineError Thrown if buffering of any sprite material fails.
     */
    void draw(std::vector<SpriteMaterial*>*);

    /**
     * @brief Copies a single sprite material to the renderer buffer.
     * @param material Sprite material.
     * @throw EngineError Thrown if buffering fails.
     */
    void draw(SpriteMaterial*);

    /**
     * @brief Draws the sprites on the screen.
     *
     */
    void commit();

    // TODO Improve implementation
    void blindScreen();
};

}