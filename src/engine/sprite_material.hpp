/**
 * sprite_material.hpp - Sprites for the game world
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
#include <SDL2/SDL.h>

namespace dino {

/**
 * @brief Wraps a SDL texture for rendering on to the screen.
 */
class SpriteMaterial {

private: /* ===-=== Private Members ===-=== */

    /**
     * @brief Static member to hold the number of instances created.
     *
     * Increments when an instance is created and decrements when
     * an instance is destroyed.
     */
    static unsigned int s_counter;

    /**
     * @brief A handle to the SDL texture object which is wrapped.
     */
    SDL_Texture* m_texture;

    /**
     * @brief The properties of the SDL texture.
     */
    SDL_Rect m_properties {0, 0, 0, 0};

    /**
     * @brief Determines how the texture should be rendered on the screen.
     */
    SDL_Rect m_attachment {0, 0, 0, 0};

    /**
     * @brief Constructs an instance from a SDL renderer and surface.
     * @param renderer Handle to the current SDL window renderer.
     * @param surface SDL surface from which the texture will be created.
     * @throw dino::EngineError Thrown if image loading fails.
     */
    explicit SpriteMaterial(SDL_Renderer*, SDL_Surface*);

    /**
     * @brief Constructs an instance from a SDL texture and properties.
     * @param texture SDL texture to be wrapped.
     * @param properties Properties of the texture.
     * @param attachment Specifies how the texture should be rendered.
     */
    explicit SpriteMaterial(SDL_Texture*, const SDL_Rect&, const SDL_Rect&);

public: /* ===-=== Public Members ===-=== */
    /**
     * @brief Creates an instance holding a texture created from an image.
     * @param renderer Handle to the current SDL window renderer.
     * @param file_path Absolute path to the image file to be loaded.
     * @return An instance with the specified image data.
     * @throw dino::EngineError Thrown if image loading fails.
     */
    static SpriteMaterial* loadImage(SDL_Renderer*, const std::string&);

    /**
     * @brief Cleans up when an instance is destroyed.
     *
     * The texture will be destroyed and memory will be released.
     */
    ~SpriteMaterial();

    /**
     * @brief Clones a child instance from the parent instance.
     * @return A new child instance.
     *
     * The cloned child instance will have a reference to the same
     * SDL texture contained in the parent instance, but with different
     * properties and attachment description.
     *
     * Cloned instances need not e destroyed explicitly.
     */
    SpriteMaterial* clone();

    /**
     * @brief Sets the X and Y coordinates in pixels.
     * @param pos_x The X coordinate in pixels.
     * @param pos_y The Y coordinate in pixels.
     */
    void setAttachment(int, int);

    /**
     * @brief Returns the SDL texture.
     * @return SDL texture.
     */
    SDL_Texture* getTexture();

    /**
     * @brief Returns the texture properties.
     * @return The texture property structure.
     */
    [[nodiscard]] SDL_Rect getProperties() const;

    /**
     * @brief Returns the screen attachment properties.
     * @return The attachment property structure.
     */
    [[nodiscard]] SDL_Rect getAttachment() const;

    /**
     * @brief Returns the texture width in pixels.
     * @return The texture width.
     */
    [[nodiscard]] int getWidth() const;

    /**
     * @brief Returns the texture height in pixels.
     * @return The texture height.
     */
    [[nodiscard]] int getHeight() const;
};

} // namespace dino
