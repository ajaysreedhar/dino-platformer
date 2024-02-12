/**
 * audio_mixer.hpp - Audio mixer and manager utility
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

#include <map>
#include <string>

#include "platform/standard.hpp"

#if defined (DINO_OS_TYPE_WINDOWS) && DINO_OS_TYPE_WINDOWS == 1
#include <SDL.h>
#include <SDL_mixer.h>
#elif defined (DINO_OS_TYPE_LINUX) && DINO_OS_TYPE_LINUX == 1 
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#endif // DINO_OS_TYPE_WINDOWS or DINO_OS_TYPE_LINUX

namespace dino {

/**
 * @brief Provides audio mixing and managing utilities.
 */
class AudioMixer {

private:
    /**
     * @brief Determines if the BGM is looping.
     */
    bool m_isLooping;

    /**
     * @brief Holds the BGM bytes.
     */
    Mix_Music* m_loopAudio;

    /**
     * @brief Holds additional sound effects mapped by an identifier.
     */
    std::map<unsigned int, Mix_Chunk*>* m_effectMap;

public:
    /**
     * @brief Initialises the instance.
     */
    AudioMixer();

    /**
     * @brief Cleans up when an instance is destroyed.
     *
     * This will pause the BGM and destroys all the loaded effects.
     */
    ~AudioMixer();

    /**
     * @brief Pauses the BGM.
     */
    void pauseLoopAudio();

    /**
     * @brief Loads an audio file and sets as game BGM.
     * @param audio_file Absolute path to the WAV file.
     * @throw dino::EngineError Thrown if audio loading fails.
     */
    void loadLoopAudio(const std::string&);

    /**
     * @brief Plays the loaded BGM infinitely or until paused.
     */
    void playLoopAudio();

    /**
     * Loads an audio file and maps it as an effect with and identifier.
     * @param effect_id Numeric identifier to identify this audio.
     * @param audio_file Absolute path to the WAV file.
     * @throw dino::EngineError Thrown if audio loading fails.
     */
    void loadEffectAudio(unsigned int, const std::string&);

    /**
     * @brief Plays a sound effect identified by an id.
     * @param effect_id The sound effect identifier.
     */
    void playEffectAudio(unsigned int);
};

} // namespace dino