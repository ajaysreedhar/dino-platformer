/**
 * engine_context.cpp - Global Dino Engine context
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

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "assert.hpp"
#include "except.hpp"
#include "engine_context.hpp"

#if defined(DINO_MODE_DEBUG) && DINO_MODE_DEBUG == 1
#include "platform/logger.hpp"
#endif

bool dino::EngineContext::s_isInitialised = false;
std::vector<dino::Renderer*> dino::EngineContext::s_renderers {};
std::vector<dino::AudioMixer*> dino::EngineContext::s_mixers  {};

void dino::EngineContext::initialise() {
    if (isInitialised()) {
        return void();
    }

    int result = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    DINO_ASSERT_SDL_RESULT(result)

    result = Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    DINO_ASSERT_SDL_RESULT(result)

    s_isInitialised = true;
}

void dino::EngineContext::shutdown() {
    if (!s_isInitialised) {
#if defined(DINO_MODE_DEBUG) && DINO_MODE_DEBUG == 1
        dino::Logger::debug("Attempting to shutdown engine context without initialising.");
#endif
        return void();
    }

    for (auto renderer : s_renderers){
        delete renderer;
    }

    for (auto mixer : s_mixers){
        delete mixer;
    }

    s_renderers.clear();
    s_mixers.clear();

    Mix_Quit();
    SDL_Quit();
}

dino::Renderer* dino::EngineContext::createRenderer(dino::TargetWindow* target) {
    if (!s_isInitialised) {
        throw dino::EngineError("Engine context must be initialised first.", dino::EngineError::E_TYPE_GENERAL);
    }

    auto renderer = new Renderer(target);
    s_renderers.push_back(renderer);

    return renderer;
}

dino::AudioMixer* dino::EngineContext::createMixer() {
    if (!s_isInitialised) {
        throw dino::EngineError("Engine context must be initialised first.", dino::EngineError::E_TYPE_GENERAL);
    }

    auto mixer = new AudioMixer();
    s_mixers.push_back(mixer);

    return mixer;
}

dino::EngineContext::Event dino::EngineContext::pollEvent() {
    SDL_Event sdl_event {};
    dino::EngineContext::Event dino_event {dino::EngineContext::Event::UNKNOWN};

    SDL_PollEvent(&sdl_event);

    if (sdl_event.type == SDL_QUIT) {
        dino_event.kind = dino::EngineContext::Event::PROCESS_QUIT;
        return dino_event;
    }

    if (sdl_event.type == SDL_KEYDOWN) {
        switch (sdl_event.key.keysym.scancode) {
            case SDL_SCANCODE_UP:
                dino_event.kind = dino::EngineContext::Event::KEY_PRESS_UP;
                return dino_event;

            case SDL_SCANCODE_RIGHT:
                dino_event.kind = dino::EngineContext::Event::KEY_PRESS_RIGHT;
                return dino_event;

            case SDL_SCANCODE_Q:
                dino_event.kind = dino::EngineContext::Event::KEY_PRESS_Q;
                return dino_event;

            case SDL_SCANCODE_R:
                dino_event.kind = dino::EngineContext::Event::KEY_PRESS_R;
                return dino_event;

            default:
                break;
        }
    }

    return dino_event;
}

bool dino::EngineContext::isInitialised() {
    return s_isInitialised;
}
