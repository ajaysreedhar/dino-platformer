/**
 * engine_context.cpp - Global Dino Engine context
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

            default:
                break;
        }
    }

    return dino_event;
}

bool dino::EngineContext::isInitialised() {
    return s_isInitialised;
}
