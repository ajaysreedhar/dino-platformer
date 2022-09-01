/**
 * logger.hpp - Custom logging utility declaration
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

#include <iostream>
#include <string>
#include <initializer_list>

namespace dino {

class Logger {

private:/* ===-=== Private Members ===-=== */
    static bool m_verbose;

    template<typename T>
    static void printUnpacked_(int level, T&& message) {
        switch (level) {
            case FATAL:
            case ERROR:
            case WARN:
                std::cerr << message << " ";
                break;

            default:
                std::cout << message << " ";
                break;
        }
    }

public: /* ===-=== Public Members ===-=== */
    enum LogLevel : int {
        FATAL = 0,
        ERROR,
        WARN,
        INFO,
        DEBUG,
        TRACE
    };

    static void verboseOn();

    static void verboseOff();

    template<typename... T> static void fatal(T&& ...messages) {
        std::cerr << "[FATAL] ";
        (printUnpacked_(FATAL, messages), ...);
        std::cerr << std::endl;
    }

    template<typename... T> static void error(T&& ...messages) {
        std::cerr << "[ERROR] ";
        (printUnpacked_(ERROR, messages), ...);
        std::cerr << std::endl;
    }

    template<typename... T> static void warn(T&& ...messages) {
        std::cerr << "[WARN ] ";
        (printUnpacked_(WARN, messages), ...);
        std::cerr << std::endl;
    }

    template<typename... T> static void info(T&& ...messages) {
        std::cout << "[INFO ] ";
        (printUnpacked_(INFO, messages), ...);
        std::cout << std::endl;
    }

    template<typename... T> static void debug(T&& ...messages) {
        std::cout << "[DEBUG] ";
        (printUnpacked_(DEBUG, messages), ...);
        std::cout << std::endl;
    }

    template<typename... T> static void trace(T&& ...messages) {
        std::cout << "[TRACE] ";
        (printUnpacked_(TRACE, messages), ...);
        std::cout << std::endl;
    }

    template<typename... T> static void print(T&& ...messages) {
        (printUnpacked_(INFO, messages), ...);
        std::cout << std::endl;
    }
};

} // namespace dino
