/**
 * renderer.cpp - Renderer module for displaying contents on the screen
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

#include "renderer.hpp"

#if defined(DINO_MODE_DEBUG) && DINO_MODE_DEBUG == 1
#include "platform/logger.hpp"
#endif

dino::Renderer::Renderer(dino::TargetWindow* target) {
    m_renderer = SDL_CreateRenderer(target->window, -1, SDL_RENDERER_ACCELERATED);
    DINO_ASSERT_SDL_HANDLE(m_renderer, dino::EngineError::E_TYPE_SDL_RESULT)
}

dino::Renderer::~Renderer() {
    SDL_DestroyRenderer(m_renderer);

#if defined(DINO_MODE_DEBUG) && DINO_MODE_DEBUG == 1
    dino::Logger::debug("Renderer destroyed.");
#endif
}

dino::SpriteMaterial *dino::Renderer::loadSprite(const std::string& image_file) {
    return dino::SpriteMaterial::loadImage(m_renderer, image_file);
}

void dino::Renderer::clear() {
    SDL_SetRenderDrawColor(m_renderer, 0x5E, 0x82, 0xAC, 0xff);
    int result = SDL_RenderClear(m_renderer);
    DINO_ASSERT_SDL_RESULT(result)
}

void dino::Renderer::begin() {
    this->clear();
}

void dino::Renderer::draw(std::vector<dino::SpriteMaterial*>* materials) {
    for (auto sprite : *materials) {
        auto properties = sprite->getProperties();
        auto attachment = sprite->getAttachment();

        auto result = SDL_RenderCopy(m_renderer, sprite->getTexture(), &properties, &attachment);
        DINO_ASSERT_SDL_RESULT(result)
    }
}

void dino::Renderer::draw(dino::SpriteMaterial* material) {
    auto properties = material->getProperties();
    auto attachment = material->getAttachment();
    SDL_RenderCopy(m_renderer, material->getTexture(), &properties, &attachment);
}

void dino::Renderer::commit() {
    SDL_RenderPresent(m_renderer);
    SDL_Delay(4);
}
