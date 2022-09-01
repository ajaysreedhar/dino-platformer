/**
 * system_clock.hpp - System clock utilities definition
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
#include "system_clock.hpp"

bool dino::SystemClock::s_isInitialised = false;

void dino::SystemClock::initialise() {
    dino::SystemClock::s_randomEngine = std::default_random_engine {unixTimestamp()};
    dino::SystemClock::s_wideDist = std::uniform_int_distribution<unsigned int>(10000, 23000);
    dino::SystemClock::s_narrowDist = std::uniform_int_distribution<unsigned int>(4000, 9000);

    s_isInitialised = true;
}

unsigned int dino::SystemClock::unixTimestamp() {
    auto current_time = std::chrono::system_clock::now().time_since_epoch();
    auto timestamp = std::chrono::duration_cast<std::chrono::seconds>(current_time);

    return timestamp.count();
}

unsigned int dino::SystemClock::randomInteger() {
    if (!s_isInitialised) {
        initialise();
    }

    auto wide_int   = s_wideDist(s_randomEngine);
    auto narrow_int = s_narrowDist(s_randomEngine);

    return (wide_int - narrow_int);
}
