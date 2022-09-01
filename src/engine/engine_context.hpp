/**
 * engine_context.hpp - Global Dino Engine context
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

#include <vector>
#include "renderer.hpp"
#include "audio_mixer.hpp"

namespace dino {

/**
 * @brief Defines an event polled from the global context.
 */
struct context_event {
    int kind = 404;

    enum EventKind: int {
        UNKNOWN = 404,
        PROCESS_QUIT = 500,
        WINDOW_CLOSE,
        KEY_PRESS_UP,
        KEY_PRESS_RIGHT,
        KEY_PRESS_Q,
        KEY_PRESS_R
    };
};

/**
 * @brief Represents the global game engine context.
 */
class EngineContext {

private: /* ===-=== Private Members ===-=== */

    /**
     * @brief Determines if the context is initialised or not.
     */
    static bool s_isInitialised;

    /**
     * @brief Holds a reference to all the renderers created.
     */
    static std::vector<Renderer*> s_renderers;

    /**
     * @brief Holds a reference to all the mixers created.
     */
    static std::vector<AudioMixer*> s_mixers;

public: /* ===-=== Public Members ===-=== */
    typedef struct context_event Event;

    /**
     * @brief Initialises the engine context.
     * @throw dino::EngineError Thrown if the engine fails to initialise.
     */
    static void initialise();

    /**
     * @brief Destroys and cleans up the engine context.
     */
    static void shutdown();

    /**
     * @brief Creates a renderer for a window.
     * @return New renderer.
     * @throw dino::EngineError Thrown if renderer can not be created.
     *
     * Only one renderer needs to be created for a window.
     * If there are multiple windows, every window requires
     * a renderer to be created.
     */
    static Renderer* createRenderer(TargetWindow*);

    /**
     * @brief Creates an audio mixer.
     * @return New audio mixer.
     * @throw dino::EngineError Thrown if mixer can not be created.
     */
    static AudioMixer* createMixer();

    /**
     * @brief Polls events from the global context.
     * @return The event details.
     */
    static EngineContext::Event pollEvent();

    /**
     * @brief Checks if the context is already initialised or not.
     * @return True if initialised, false otherwise.
     */
    static bool isInitialised();
};

} // namespace dino
