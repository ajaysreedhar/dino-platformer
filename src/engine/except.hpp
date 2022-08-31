/**
 * except.hpp - Throwable Dino engine exception
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
