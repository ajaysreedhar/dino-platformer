/**
 * sprite_material.hpp - Sprites for the game world
 * -------------------------------------------------------------------------------
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
 * ===============================================================================
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
     * @brief Set to true if the instance is cloned.
     */
    bool m_isCloned = false;

    /**
     * @brief A handle to the SDL texture object which is wrapped.
     */
    SDL_Texture* m_texture;

    /**
     * @brief The scissor properties of the SDL texture.
     *
     * The scissor property determines what portion od the image
     * will be rendered on the screen.
     * When a sprite material is initialised, the X and Y values
     * are set to 0 and W and H are same as that of the source
     * image read from the disk.
     */
    SDL_Rect m_scissor {0, 0, 0, 0};

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
     * @brief Sets the X and Y attachment coordinates in pixels.
     * @param pos_x The X coordinate in pixels.
     * @param pos_y The Y coordinate in pixels.
     * @param width The attachment length from X position.
     * @param height The attachment length from Y position.
     */
    void setAttachment(int, int, int, int);

    /**
     * @brief Sets the X and Y attachment coordinates in pixels.
     * @param pos_x The X coordinate in pixels.
     * @param pos_y The Y coordinate in pixels.
     */
    void setAttachment(int, int);

    /**
     * @brief Sets the full scissor coordinates in pixels
     * @param pos_x The X coordinate in pixels.
     * @param pos_y The y coordinate in pixels.
     * @param width The clip length from X position.
     * @param height The clip length from Y position.
     */
    void setScissor(int, int, int, int);

    /**
     * @brief Sets the X and Y clip coordinates in pixels.
     * @param pos_x The X coordinate in pixels.
     * @param pox_y The Y coordinate in pixels.
     */
    void setScissor(int pos_x, int pox_y);

    /**
     * @brief Returns the SDL texture.
     * @return SDL texture.
     */
    [[nodiscard]] SDL_Texture* getTexture() const;

    /**
     * @brief Returns the texture properties.
     * @return The texture property structure.
     */
    [[nodiscard]] const SDL_Rect* getProperties() const;

    /**
     * @brief Returns the attachment details.
     * @return The attachment details.
     */
    [[nodiscard]] const SDL_Rect* getAttachment() const;

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

    /**
     * @brief Returns the X axis value of attachment property.
     * @return The X axis value in pixels.
     */
    [[nodiscard]] int getPositionX() const;

    /**
     * @brief Returns the Y axis value of attachment property.
     * @return The Y axis value in pixels.
     */
    [[nodiscard]] int getPositionY() const;

    /**
     * @brief Returns the X axis value of scissor rectangle.
     * @return The X axis value in pixels.
     */
    [[nodiscard]] int getScissorX() const;

    /**
     * @brief Returns the Y axis value of scissor rectangle.
     * @return The Y axis value in pixels.
     */
    [[nodiscard]] int getScissorY() const;
};

} // namespace dino
