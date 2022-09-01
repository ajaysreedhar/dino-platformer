/**
 * audio_mixer.cpp - Audio mixer and manager utility
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
