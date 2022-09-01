/**
 * standard.hpp - Standard platform definition
 * ------------------------------------------------------------------------
 *
 * Copyright (c) 2022 Ajay Sreedhar
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
 * ===------------------------------------------------------------------===
 */

#pragma once

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
#ifndef _WIN64
#error "Dino Platformer needs 64-bit Windows to compile!"
#endif // ifndef _WIN64
#define DINO_OS_TYPE_WINDOWS 1

#elif defined(__linux__) || defined(__gnu_linux__)
#define DINO_OS_TYPE_LINUX 1

#else
#error "Dino Platformer compiles only on Windows and Linux!"

#endif // defined(WIN32) || defined(__linux__)

#define DINO_MODE_DEBUG 1