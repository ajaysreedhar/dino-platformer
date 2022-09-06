/**
 * platformer.hpp - Platformer game application
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

#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include "platform/system_clock.hpp"
#include "engine/renderer.hpp"
#include "engine/audio_mixer.hpp"

#define DINO_FLOOR_SCROLL_VELOCITY 5
#define DINO_WORLD_SCROLL_VELOCITY 1
#define DINO_SPRITE_CLIP_WIDTH 262

namespace dino {

/**
 * @brief Platformer game.
 */
class Platformer {

private:
    std::mutex m_positionMutex {};
    std::thread* m_positionThread = nullptr;
    std::thread* m_animateThread  = nullptr;

    /**
     * @brief Determines if the main loop is still running.
     */
    bool m_isRunning  = true;

    /**
     * @brief Determines if the game is being played or not.
     */
    bool m_isGameOver = false;

    /**
     * @brief Holds the timestamp at which last obstacle was placed.
     *
     * This will be used to synchronise obstacle placement.
     */
    unsigned int m_lastObstacle;

    TargetWindow*   m_window;
    Renderer*       m_renderer;
    AudioMixer*     m_audioMixer;

    SpriteMaterial* m_dinoSprite;

    std::vector<SpriteMaterial*>* m_baseTiles;
    std::vector<SpriteMaterial*>* m_worldScene;
    std::vector<SpriteMaterial*>* m_obstacles;

    /**
     * @brief Residual sprites.
     *
     * Holds the obstacle sprites that are currently not displayed
     * on the screen. When an obstacle needs to be placed on the
     * screen the sprite can be pulled from the residual queue instead
     * of creating a new instance.
     */
    std::queue<SpriteMaterial*>* m_residual;

public:
    /**
     * @brief Initialises the game scope.
     */
    Platformer();

    /**
     * @brief Cleans up after game ends.
     */
    ~Platformer();

    /**
     * @brief Creates the 2D game world.
     *
     * Loads sprites from images and positions them
     * accordingly on the screen.
     */
    void createWorld();

    /**
     * @brief Resets the world scene back to initial state.
     *
     * This method WILL NOT reload sprite materials. It simply
     * re-positions them back to the initial state.
     */
    void reloadWorld();

    /**
     * @brief Moves the camera on the horizontal X axis.
     * @return Move status. 0 if camera moved, 1 otherwise.
     */
    int moveCamera();

    /**
     * @brief Moves the player on the vertical Y axis.
     * @param pos_x Initial player position on X axis.
     * @param pos_y Initial player position on Y axis.
     */
    void movePlayer(int, int);

    /**
     * @brief Applies Run animation to the dino sprite.
     */
    void animateSprite();

    /**
     * @brief Randomly places the obstacles on the platform.
     * @return True if obstacle placed, false otherwise.
     *
     * This method attempts to place an object but without any
     * guarantee that the obstacle is actually placed.
     *
     * The method will not place an obstacle if the previous obstacle
     * was placed in less than 2 seconds ago.
     */
    bool placeObstacles();

    /**
     * @brief Runs the main loop.
     */
    void run();
};

} // namespace dino