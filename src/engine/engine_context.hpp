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

namespace dino {

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

class EngineContext {

private:
    static bool s_isInitialised;

    static std::vector<Renderer*> s_renderers;

public:
    typedef struct context_event Event;

    static void initialise();

    static void shutdown();

    static Renderer* createRenderer(TargetWindow*);

    static EngineContext::Event pollEvent();

    static bool isInitialised();

};

} // namespace dino