/**
 * system_clock.hpp - System clock utilities declaration
 * -------------------------------------------------------------------------------
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
 * ===============================================================================
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
