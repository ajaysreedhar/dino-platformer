/**
 * except.hpp - Throwable Dino engine exception
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

#include <stdexcept>

namespace dino {

/**
 * @brief Defines a throwable error for the engine module.
 *
 * All sub-modules in the engine module must throw an
 * instance of this class if an exception occurs.
 */
class EngineError : public std::runtime_error {

private:
    int m_code = 0;

public:
    enum ErrorKind: int {
        E_TYPE_GENERAL = 311,
        E_TYPE_SDL_RESULT,
        E_TYPE_MIX_RESULT
    };

    /**
     * @brief Sets the error message and code.
     * @param message Error message.
     * @param code Custom error code.
     */
    EngineError(const char* message, int code) : std::runtime_error(message) {
        m_code = code;
    }

    /**
     * @brief Returns the error code.
     * @return Error code.
     */
    int getCode () {
        return m_code;
    }
};

} // namespace dino
