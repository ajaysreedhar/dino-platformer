/**
 * system_clock.hpp - System clock utilities declaration
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

#include <chrono>
#include <random>

namespace dino {

/**
 * @brief Utilities based on system clock.
 */
class SystemClock {

private:
    static bool s_isInitialised;
    static std::default_random_engine s_randomEngine;
    static std::uniform_int_distribution<unsigned int> s_wideDist;
    static std::uniform_int_distribution<unsigned int> s_narrowDist;

public:
    /**
     * @brief Initialises the random generator.
     */
    static void initialise();

    /**
     * Provides the current timestamp in seconds.
     * @return Timestamp in seconds.
     */
    static unsigned int unixTimestamp();

    /**
     * @brief Returns a random number based on the current timestamp seed.
     * @return Random number.
     */
    static unsigned int randomInteger();
};

} // namespace dino
