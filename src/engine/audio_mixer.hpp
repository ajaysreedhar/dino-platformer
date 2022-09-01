/**
 * audio_mixer.hpp - Audio mixer and manager utility
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

#include <map>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

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