/**
 * audio_mixer.cpp - Audio mixer and manager utility
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

#include "assert.hpp"
#include "audio_mixer.hpp"

#if defined(DINO_MODE_DEBUG) && DINO_MODE_DEBUG == 1
#include "platform/logger.hpp"
#endif


dino::AudioMixer::AudioMixer() :
        m_isLooping(false),
        m_loopAudio(nullptr) {

    m_effectMap = new std::map<unsigned int, Mix_Chunk*>();
}

dino::AudioMixer::~AudioMixer() {
    if (m_isLooping) {
        Mix_PauseMusic();
    }

    Mix_FreeMusic(m_loopAudio);

    for (auto audio_it : *m_effectMap) {
        Mix_FreeChunk(audio_it.second);
    }

    m_effectMap->clear();
    delete m_effectMap;

#if defined(DINO_MODE_DEBUG) && DINO_MODE_DEBUG == 1
    dino::Logger::debug("Audio mixer destroyed.");
#endif
}

void dino::AudioMixer::loadEffectAudio(unsigned int effect_id, const std::string &audio_file) {
    auto mix_chunk = Mix_LoadWAV(audio_file.c_str());
    DINO_ASSERT_SDL_HANDLE(mix_chunk, dino::EngineError::E_TYPE_MIX_RESULT)

    m_effectMap->insert(std::pair(effect_id, mix_chunk));
}

void dino::AudioMixer::pauseLoopAudio() {
    if (m_isLooping) {
        Mix_PauseMusic();
        m_isLooping = false;
    }
}

void dino::AudioMixer::loadLoopAudio(const std::string &audio_file) {
    pauseLoopAudio();

    if (m_loopAudio != nullptr) {
        Mix_FreeMusic(m_loopAudio);
    }

    m_loopAudio = Mix_LoadMUS(audio_file.c_str());
    DINO_ASSERT_SDL_HANDLE(m_loopAudio, dino::EngineError::E_TYPE_MIX_RESULT)

    m_isLooping = false;
}

void dino::AudioMixer::playLoopAudio() {
    if (m_isLooping || m_loopAudio == nullptr){
        return void();
    }

    int result = Mix_PlayMusic(m_loopAudio, -1);
    DINO_ASSERT_SDL_RESULT(result)

    m_isLooping = true;
}

void dino::AudioMixer::playEffectAudio(unsigned int effect_id) {
    Mix_Chunk* mix_chunk;

    try {
        mix_chunk = m_effectMap->at(effect_id);

        if (mix_chunk == nullptr) {
            return void();
        }
    } catch (std::out_of_range& /* ignored */) {
#if defined(DINO_MODE_DEBUG) && DINO_MODE_DEBUG == 1
        dino::Logger::debug("Effect audio", effect_id, "does not exist.");
#endif
        return void();
    }

    Mix_PlayChannel(-1, mix_chunk, 0);
}
