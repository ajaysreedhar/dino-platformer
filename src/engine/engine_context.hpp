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

class EngineContext {

private:
    static bool s_isInitialised;

    static std::vector<Renderer*> s_renderers;

public:
    static void initialise();

    static void shutdown();

    static Renderer* createRenderer(TargetWindow*);

};

} // namespace dino
