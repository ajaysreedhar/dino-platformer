/**
 * renderer.hpp - Renderer module for displaying contents on the screen
 * ------------------------------------------------------------------------
 *
 * Copyright (c) 2022-present Ajay Sreedhar
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
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
};

}