/**
 * engine_context.hpp - Global Dino Engine context
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
