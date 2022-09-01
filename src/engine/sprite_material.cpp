/**
 * sprite_material.cpp - Sprites for the game world
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

#include <vector>
#include <SDL2/SDL_image.h>
#include "assert.hpp"
#include "sprite_material.hpp"

#if defined(DINO_MODE_DEBUG) && DINO_MODE_DEBUG == 1
#include "platform/logger.hpp"
#endif

unsigned int dino::SpriteMaterial::s_counter = 0;

dino::SpriteMaterial::SpriteMaterial(SDL_Renderer* renderer, SDL_Surface* surface) {
    m_texture = SDL_CreateTextureFromSurface(renderer, surface);
    DINO_ASSERT_SDL_HANDLE(m_texture, dino::EngineError::E_TYPE_SDL_RESULT)

    SDL_QueryTexture(m_texture, nullptr, nullptr, &(m_properties.w), &(m_properties.h));

    m_attachment.w = m_properties.w;
    m_attachment.h = m_properties.h;

    s_counter = s_counter + 1;
}

dino::SpriteMaterial::SpriteMaterial(SDL_Texture* texture, const SDL_Rect& properties, const SDL_Rect& attachment) {
    m_texture = texture;
    m_properties.w = properties.w;
    m_properties.h = properties.h;
    m_properties.x = properties.x;
    m_properties.y = properties.y;
    m_attachment.w = attachment.w;
    m_attachment.h = attachment.h;
    m_attachment.x = attachment.x;
    m_attachment.y = attachment.y;
}

dino::SpriteMaterial *dino::SpriteMaterial::loadImage(SDL_Renderer *renderer, const std::string& file_path) {
    SDL_Surface* surface = IMG_Load(file_path.c_str());
    DINO_ASSERT_SDL_HANDLE(surface, dino::EngineError::E_TYPE_SDL_RESULT)

    auto material = new dino::SpriteMaterial(renderer, surface);

    SDL_FreeSurface(surface);
    return material;
}

dino::SpriteMaterial::~SpriteMaterial() {
    if (m_texture != nullptr) {
        SDL_DestroyTexture(m_texture);
        m_texture = nullptr;
        s_counter = s_counter - 1;

#if defined(DINO_MODE_DEBUG) && DINO_MODE_DEBUG == 1
        dino::Logger::debug("Sprite material", s_counter, "destroyed.");
#endif
    }
}

dino::SpriteMaterial* dino::SpriteMaterial::clone() {
    return new SpriteMaterial(m_texture, m_properties, m_attachment);
}

SDL_Texture *dino::SpriteMaterial::getTexture() const {
    return m_texture;
}

void dino::SpriteMaterial::setAttachment(int pos_x, int pos_y) {
    m_attachment.x = pos_x;
    m_attachment.y = pos_y;
}

const SDL_Rect* dino::SpriteMaterial::getProperties() const {
    return &m_properties;
}

int dino::SpriteMaterial::getWidth() const {
    return m_properties.w;
}

int dino::SpriteMaterial::getHeight() const {
    return m_properties.h;
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
