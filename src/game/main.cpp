/**
 * main.cpp - Execution begins here
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

#include "platform/logger.hpp"
#include "engine/except.hpp"
#include "engine/engine_context.hpp"
#include "game/platformer.hpp"

int main() {
    dino::EngineContext::initialise();
    dino::Logger::info("Starting Dino Platformer!");

    dino::Platformer* platformer;

    try {
        platformer = new dino::Platformer();

    } catch (dino::EngineError& error) {
        dino::Logger::fatal(error.what(), error.getCode());
        return EXIT_FAILURE;

    } catch (std::runtime_error& error) {
        dino::Logger::fatal(error.what());
        return EXIT_FAILURE;
    }

    platformer->createWorld();
    platformer->run();

    delete platformer;

    dino::EngineContext::shutdown();
    dino::Logger::info("Done!");

    return EXIT_SUCCESS;
}
