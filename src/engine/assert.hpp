/**
 * assert.hpp - Various macros for assertion
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

#include <SDL2/SDL.h>
#include "except.hpp"

#define DINO_ASSERT_SDL_HANDLE(handle, code)    \
if (handle == nullptr) {                        \
    auto message = SDL_GetError();              \
    throw dino::EngineError(message, code);     \
}

#define DINO_ASSERT_SDL_RESULT(result)          \
if (result <= -1) {                             \
    auto message = SDL_GetError();              \
    throw dino::EngineError(message, result);   \
}
