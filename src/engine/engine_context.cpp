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
#include "except.hpp"
#include "engine_context.hpp"

bool dino::EngineContext::s_isInitialised = false;
std::vector<dino::Renderer*> dino::EngineContext::s_renderers {};

void dino::EngineContext::initialise() {
    int code = SDL_Init(SDL_INIT_VIDEO);

    if (code <= -1) {
        throw dino::EngineError(SDL_GetError(), code);
    }

    s_isInitialised = true;
}

dino::Renderer* dino::EngineContext::createRenderer(dino::TargetWindow* target) {
    if (!s_isInitialised) {
        throw dino::EngineError("Engine context must be initialised first.", dino::EngineError::E_TYPE_GENERAL);
    }

    auto renderer = new Renderer(target);
    s_renderers.push_back(renderer);

    return renderer;
}

void dino::EngineContext::shutdown() {
    if (!s_isInitialised) {
        throw dino::EngineError("Engine context must be initialised first.", dino::EngineError::E_TYPE_GENERAL);
    }

    for (auto renderer : s_renderers){
        delete renderer;
    }

    s_renderers.clear();
    SDL_Quit();
}

bool dino::EngineContext::isInitialised() {
    return s_isInitialised;
}
