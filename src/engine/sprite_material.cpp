/**
 * sprite_material.cpp - Sprites for the game world
 * ------------------------------------------------------------------------------
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
 * ==============================================================================
 */

#include <vector>

#include "assert.hpp"
#include "sprite_material.hpp"

#if defined (DINO_OS_TYPE_WINDOWS) && DINO_OS_TYPE_WINDOWS == 1
#include <SDL_image.h>
#elif defined (DINO_OS_TYPE_LINUX) && DINO_OS_TYPE_LINUX == 1 
#include <SDL2/SDL_image.h>
#endif // DINO_OS_TYPE_WINDOWS or DINO_OS_TYPE_LINUX

#if defined(DINO_MODE_DEBUG) && DINO_MODE_DEBUG == 1
#include "platform/logger.hpp"
#endif

unsigned int dino::SpriteMaterial::s_counter = 0;

dino::SpriteMaterial::SpriteMaterial(SDL_Renderer* renderer, SDL_Surface* surface) {
    m_texture = SDL_CreateTextureFromSurface(renderer, surface);
    DINO_ASSERT_SDL_HANDLE(m_texture, dino::EngineError::E_TYPE_SDL_RESULT)

    SDL_QueryTexture(m_texture, nullptr, nullptr, &(m_scissor.w), &(m_scissor.h));

    m_attachment.w = m_scissor.w;
    m_attachment.h = m_scissor.h;

    s_counter = s_counter + 1;
}

dino::SpriteMaterial::SpriteMaterial(SDL_Texture* texture, const SDL_Rect& properties, const SDL_Rect& attachment) {
    m_texture = texture;
    m_scissor.w = properties.w;
    m_scissor.h = properties.h;
    m_scissor.x = properties.x;
    m_scissor.y = properties.y;
    m_attachment.w = attachment.w;
    m_attachment.h = attachment.h;
    m_attachment.x = attachment.x;
    m_attachment.y = attachment.y;

    m_isCloned = true;
}

dino::SpriteMaterial *dino::SpriteMaterial::loadImage(SDL_Renderer *renderer, const std::string& file_path) {
    SDL_Surface* surface = IMG_Load(file_path.c_str());
    DINO_ASSERT_SDL_HANDLE(surface, dino::EngineError::E_TYPE_SDL_RESULT)

    auto material = new dino::SpriteMaterial(renderer, surface);

    SDL_FreeSurface(surface);
    return material;
}

dino::SpriteMaterial::~SpriteMaterial() {
    if (!m_isCloned && m_texture != nullptr) {
        SDL_DestroyTexture(m_texture);
        m_texture = nullptr;
        s_counter = s_counter - 1;

#if defined(DINO_MODE_DEBUG) && DINO_MODE_DEBUG == 1
        dino::Logger::debug("Sprite material destroyed.", s_counter, "remaining.");
#endif
    }
}

dino::SpriteMaterial* dino::SpriteMaterial::clone() {
    return new SpriteMaterial(m_texture, m_scissor, m_attachment);
}

SDL_Texture *dino::SpriteMaterial::getTexture() const {
    return m_texture;
}

void dino::SpriteMaterial::setAttachment(int pos_x, int pos_y, int width, int height) {
    m_attachment.x = pos_x;
    m_attachment.y = pos_y;
    m_attachment.w = width;
    m_attachment.h = height;
}

void dino::SpriteMaterial::setAttachment(int pos_x, int pos_y) {
    m_attachment.x = pos_x;
    m_attachment.y = pos_y;
}

void dino::SpriteMaterial::setScissor(int pos_x, int pos_y, int width, int height) {
    m_scissor.x = pos_x;
    m_scissor.y = pos_y;
    m_scissor.w = width;
    m_scissor.h = height;
}

void dino::SpriteMaterial::setScissor(int pos_x, int pox_y) {
    m_scissor.x = pos_x;
    m_scissor.y = pox_y;
}

const SDL_Rect* dino::SpriteMaterial::getProperties() const {
    return &m_scissor;
}

int dino::SpriteMaterial::getWidth() const {
    return m_scissor.w;
}

int dino::SpriteMaterial::getHeight() const {
    return m_scissor.h;
}

int dino::SpriteMaterial::getPositionX() const {
    return m_attachment.x;
}

int dino::SpriteMaterial::getPositionY() const {
    return m_attachment.y;
}

const SDL_Rect* dino::SpriteMaterial::getAttachment() const {
    return &m_attachment;
}

int dino::SpriteMaterial::getScissorX() const {
    return m_scissor.x;
}

int dino::SpriteMaterial::getScissorY() const {
    return m_scissor.y;
}
