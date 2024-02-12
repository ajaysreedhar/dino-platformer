/**
 * assert.hpp - Various macros for assertion
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

#pragma once

#include "platform/standard.hpp"

#if defined (DINO_OS_TYPE_WINDOWS) && DINO_OS_TYPE_WINDOWS == 1
#include <SDL_error.h>
#elif defined (DINO_OS_TYPE_LINUX) && DINO_OS_TYPE_LINUX == 1 
#include <SDL2/SDL_error.h>
#endif // DINO_OS_TYPE_WINDOWS or DINO_OS_TYPE_LINUX

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
