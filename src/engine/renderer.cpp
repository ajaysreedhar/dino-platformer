/**
 * renderer.cpp - Renderer module for displaying contents on the screen
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

#include <cmath>
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
    dino::Logger::debug("Renderer instance destroyed.");
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
        auto const properties = sprite->getProperties();
        auto const attachment = sprite->getAttachment();

        auto result = SDL_RenderCopy(m_renderer, sprite->getTexture(), properties, attachment);
        DINO_ASSERT_SDL_RESULT(result)
    }
}

void dino::Renderer::draw(dino::SpriteMaterial* material) {
    auto const properties = material->getProperties();
    auto const attachment = material->getAttachment();
    SDL_RenderCopy(m_renderer, material->getTexture(), properties, attachment);
}

void dino::Renderer::commit() {
    SDL_RenderPresent(m_renderer);

    uint32_t frames_sec = 240;
    uint32_t start_time = SDL_GetTicks();

    if ((1000/frames_sec) > (SDL_GetTicks() - start_time)) {
        SDL_Delay((1000/frames_sec) - (SDL_GetTicks() - start_time));
    }

    //SDL_Delay(4);
}

void dino::Renderer::blindScreen() {
    unsigned int color_code;
    double radians = 0.0f;

#if defined (DINO_OS_TYPE_WINDOWS) && DINO_OS_TYPE_WINDOWS == 1
    while (radians <= M_PI) {

#elif defined (DINO_OS_TYPE_LINUX) && DINO_OS_TYPE_LINUX == 1 
    while (radians <= M_PIf) {
#endif // DINO_OS_TYPE_WINDOWS or DINO_OS_TYPE_LINUX
        int result = SDL_RenderClear(m_renderer);
        DINO_ASSERT_SDL_RESULT(result)

        color_code = static_cast<unsigned int>(125.0 * std::sin(radians));

        SDL_SetRenderDrawColor(m_renderer, color_code, 0x44, 0x44, 0xFF);
        SDL_RenderPresent(m_renderer);
        SDL_Delay(2);

        radians = radians + 0.01f;
    }
}
