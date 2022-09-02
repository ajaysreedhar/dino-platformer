/**
 * platformer.cpp - Platformer game application
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

#include <cmath>
#include "engine/except.hpp"
#include "engine/engine_context.hpp"
#include "platformer.hpp"

#if defined(DINO_MODE_DEBUG) && DINO_MODE_DEBUG == 1
#include "platform/logger.hpp"
#endif

dino::Platformer::Platformer() : m_lastObstacle(0) {
    if (!dino::EngineContext::isInitialised()) {
        throw std::runtime_error("Engine context is not initialised!");
    }

    m_window     = new dino::TargetWindow("Crazy Dino", 1920, 1080);
    m_renderer   = dino::EngineContext::createRenderer(m_window);
    m_audioMixer = dino::EngineContext::createMixer();

    m_baseTiles  = new std::vector<dino::SpriteMaterial*>();
    m_worldScene = new std::vector<dino::SpriteMaterial*>();
    m_obstacles  = new std::vector<dino::SpriteMaterial*>();
    m_residual   = new std::queue<dino::SpriteMaterial*>();

    m_dinoPlayer = m_renderer->loadSprite("texture/dino-player.png");

    m_audioMixer->loadLoopAudio("audio/game-bgm-score.mp3");
    m_audioMixer->loadEffectAudio(0, "audio/cartoon-jump.wav");
}

void dino::Platformer::createWorld() {
    auto base_tile = m_renderer->loadSprite("texture/base-tile-01.png");

    int next_x = 0;
    int next_y = m_window->height - base_tile->getHeight();

    base_tile->setAttachment(next_x, next_y);

    int sprite_count = m_window->width / base_tile->getWidth();
    m_baseTiles->push_back(base_tile);

    while (sprite_count >= 0) {
        auto next_tile = base_tile->clone();
        next_x = next_x + next_tile->getWidth();

        next_tile->setAttachment(next_x, next_y);
        m_baseTiles->push_back(next_tile);

        sprite_count--;
    }

    auto world_scene =  m_renderer->loadSprite("texture/world-bg.png");

    sprite_count = m_window->width / world_scene->getWidth();
    next_x = 0;
    next_y = m_window->height - base_tile->getHeight() - world_scene->getWidth();

    world_scene->setAttachment(next_x, next_y);
    m_worldScene->push_back(world_scene);

    while (sprite_count >= 0) {
        auto next_scene = world_scene->clone();
        next_x = next_x + next_scene->getWidth();

        next_scene->setAttachment(next_x, next_y);
        m_worldScene->push_back(next_scene);

        sprite_count--;
    }

    auto obstacle = m_renderer->loadSprite("texture/obstacle-type-01.png");
    obstacle->setAttachment(m_window->width, m_window->height - base_tile->getHeight() - obstacle->getHeight());
    m_obstacles->push_back(obstacle);

    m_lastObstacle = dino::SystemClock::unixTimestamp();

    for (int count = 0; count < 5; count++) {
        m_obstacles->push_back(obstacle->clone());
    }

    m_dinoPlayer->setAttachment(100, m_window->height - base_tile->getHeight() - m_dinoPlayer->getHeight());
}

void dino::Platformer::reloadWorld() {
    int next_x = 0;
    int next_y = m_window->height - m_baseTiles->at(0)->getHeight();

    m_dinoPlayer->setAttachment(100, next_y - m_dinoPlayer->getHeight());

    /* Re-position base tiles. */
    for (auto sprite : *m_baseTiles){
        sprite->setAttachment(next_x, next_y);
        next_x = next_x + sprite->getWidth();
    }

    /* Re-position obstacles. */
    for (auto sprite : *m_obstacles){
        sprite->setAttachment(m_window->width, sprite->getPositionY());
    }

    while (!m_residual->empty()) {
        m_residual->pop();
    }
}

void dino::Platformer::run() {
    m_audioMixer->playLoopAudio();

    while (m_isRunning) {
        auto event = dino::EngineContext::pollEvent();

        switch (event.kind) {
            case dino::EngineContext::Event::PROCESS_QUIT:
            case dino::EngineContext::Event::KEY_PRESS_Q:
            case dino::EngineContext::Event::WINDOW_CLOSE:
                m_isRunning = false;
                break;

            case dino::EngineContext::Event::KEY_PRESS_R:
                if (m_isGameOver) {
                    this->m_renderer->blindScreen();
                    this->reloadWorld();
                    this->m_audioMixer->playLoopAudio();

                    m_isGameOver = false;
                }
                break;

            case dino::EngineContext::Event::KEY_PRESS_UP:
                if (m_positionMutex.try_lock()) {
                    delete m_positionThread;

                    int pos_x = m_dinoPlayer->getPositionX();
                    int pos_y = m_window->height - m_baseTiles->at(0)->getHeight() - m_dinoPlayer->getHeight();

                    m_positionThread = new std::thread(&dino::Platformer::movePlayer, this, pos_x, pos_y);
                    m_positionThread->detach();

                    m_audioMixer->playEffectAudio(0);
                }

                break;

            default:
                break;
        }

        m_renderer->clear();

        if (!m_isGameOver) {
            moveCamera();
            placeObstacles();
        }

        m_renderer->draw(m_worldScene);
        m_renderer->draw(m_baseTiles);
        m_renderer->draw(m_obstacles);
        m_renderer->draw(m_dinoPlayer);

        m_renderer->commit();
    }
}

dino::Platformer::~Platformer() {
#if defined(DINO_MODE_DEBUG) && DINO_MODE_DEBUG == 1
    dino::Logger::debug("Cleaning up base tile sprites.");
#endif
    for (auto sprite : *m_baseTiles) {
        delete sprite;
    }

#if defined(DINO_MODE_DEBUG) && DINO_MODE_DEBUG == 1
    dino::Logger::debug("Cleaning up world scene sprites.");
#endif
    for (auto sprite : *m_worldScene) {
        delete sprite;
    }

#if defined(DINO_MODE_DEBUG) && DINO_MODE_DEBUG == 1
    dino::Logger::debug("Cleaning up obstacle sprites.");
#endif
    for (auto sprite : *m_obstacles) {
        delete sprite;
    }

#if defined(DINO_MODE_DEBUG) && DINO_MODE_DEBUG == 1
    dino::Logger::debug("Cleaning up player sprite.");
#endif
    delete m_dinoPlayer;

    SDL_DestroyWindow(m_window->window);

    m_baseTiles->clear();
    m_obstacles->clear();
    m_worldScene->clear();

    delete m_window;
    delete m_baseTiles;
    delete m_worldScene;
    delete m_obstacles;

    delete m_residual;
}

int dino::Platformer::moveCamera() {
    for (auto sprite : *m_baseTiles) {
        int pos_x = sprite->getPositionX();
        int pos_y = sprite->getPositionY();

        pos_x = pos_x - DINO_FLOOR_SCROLL_VELOCITY;

        if (pos_x <= 0 - sprite->getWidth()) {
            pos_x = static_cast<int>(m_baseTiles->size() - 1) * sprite->getWidth() - 15;
        }

        sprite->setAttachment(pos_x, pos_y);
    }

    for (auto sprite : *m_worldScene) {
        int pos_x = sprite->getPositionX();
        int pos_y = sprite->getPositionY();

        pos_x = pos_x - DINO_WORLD_SCROLL_VELOCITY;

        if (pos_x <= 0 - sprite->getWidth()) {
            pos_x = static_cast<int >(m_worldScene->size() - 1) * sprite->getWidth();
        }

        sprite->setAttachment(pos_x, pos_y);
    }

    int player_distance, player_elevation;

    for (auto sprite : *m_obstacles) {
        int pos_x = sprite->getPositionX();
        int pos_y = sprite->getPositionY();

        if (pos_x <= 0 - sprite->getWidth()) {
            if (pos_x <= 0 - sprite->getWidth() - 30) {
                continue;
            }

            pos_x = 0 - sprite->getWidth() - 30;

            sprite->setAttachment(pos_x, pos_y);
            m_residual->push(sprite);

            continue;
        } else {
            pos_x = pos_x - DINO_FLOOR_SCROLL_VELOCITY;
        }

        /* Collision detection. */
        player_distance  = pos_x - m_dinoPlayer->getPositionX();
        player_elevation = m_dinoPlayer->getPositionY() + (m_dinoPlayer->getHeight() - 100);

        if (player_distance > 0 && player_distance < m_dinoPlayer->getWidth() && player_elevation > sprite->getPositionY()) {
            m_isGameOver = true;
            m_audioMixer->pauseLoopAudio();
        }

        sprite->setAttachment(pos_x, pos_y);
    }

    return 0;
}

void dino::Platformer::movePlayer(int pos_x, int pos_y) {
    float radians = 0;
    int next_y    = 0;

    while (radians <= M_PIf) {
        next_y = pos_y - static_cast<int>(450.0f * std::sin(radians));
        m_dinoPlayer->setAttachment(pos_x, next_y);
        radians = radians + 0.01f;

        SDL_Delay(2);
    }

    m_positionMutex.unlock();
    return void();
}

bool dino::Platformer::placeObstacles() {

    /* Attempt to place only if there is at least 2
     * sprite materials in the residual queue. */
    if (m_residual->size() <= 1) {
        return false;
    }

    /* There should be at least 2 seconds gap between placing obstacles. */
    auto timestamp= dino::SystemClock::unixTimestamp();

    if (timestamp - m_lastObstacle < 1) {
        return false;
    }

    /* Use random numbers to randomly place obstacles. */
    unsigned int random_num = dino::SystemClock::randomInteger();

    if (random_num % 100 == 0) {
        m_lastObstacle = timestamp;

        auto obstacle = m_residual->front();
        m_residual->pop();

        if (obstacle != nullptr) {
            obstacle->setAttachment(m_window->width, obstacle->getPositionY());
        }
    }

    return true;
}
