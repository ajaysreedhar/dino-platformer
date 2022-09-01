/**
 * system_clock.hpp - System clock utilities definition
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

#include "system_clock.hpp"

bool dino::SystemClock::s_isInitialised = false;

std::default_random_engine dino::SystemClock::s_randomEngine{}; // NOLINT(cert-err51-cpp,cert-err58-cpp,cert-msc51-cpp)
std::uniform_int_distribution<unsigned int> dino::SystemClock::s_wideDist   {10000, 23000}; // NOLINT(cert-err58-cpp)
std::uniform_int_distribution<unsigned int> dino::SystemClock::s_narrowDist {4000, 9000};   // NOLINT(cert-err58-cpp)

void dino::SystemClock::initialise() {
    s_randomEngine.seed(unixTimestamp());
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
