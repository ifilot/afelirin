/**************************************************************************
 *   engine.h  --  This file is part of AFELIRIN.                         *
 *                                                                        *
 *   Copyright (C) 2016, Ivo Filot                                        *
 *                                                                        *
 *   AFELIRIN is free software:                                           *
 *   you can redistribute it and/or modify it under the terms of the      *
 *   GNU General Public License as published by the Free Software         *
 *   Foundation, either version 3 of the License, or (at your option)     *
 *   any later version.                                                   *
 *                                                                        *
 *   AFELIRIN is distributed in the hope that it will be useful,          *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty          *
 *   of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.              *
 *   See the GNU General Public License for more details.                 *
 *                                                                        *
 *   You should have received a copy of the GNU General Public License    *
 *   along with this program.  If not, see http://www.gnu.org/licenses/.  *
 *                                                                        *
 **************************************************************************/

#ifndef _VISUALIZER_H
#define _VISUALIZER_H

#include <boost/lexical_cast.hpp>
#include <boost/noncopyable.hpp>
#include <stdexcept>

#include "core/engine_client.h"
#include "core/mouse.h"
#include "core/shader.h"
#include "core/screen.h"
#include "core/camera_fps.h"
#include "core/font_writer.h"
#include "core/light.h"
#include "core/post_processor.h"

#include "core/commands/engine/engine_commands.h"
#include "core/commands/camera/camera_commands.h"

#include "app/game.h"

/**
 * @class Engine class
 * @brief Initializes entities and handles time propagation.
 */
class Engine : private boost::noncopyable {
private:
    /**
     * @var accumulator
     * @brief Time accumulation tracker
     *
     * After each frame, the accumulator is incremented by the time corresponding
     * to the target frame rate. The accumulator can only be decremented by
     * performing update (integration) actions. This procedure guarantees that
     * the visualizer as the same pace independent of machine performance.
     */
    double accumulator;

    /**
     * @var frmae_start
     * @brief Current time after start of the execution
     */
    double frame_start;

    /**
     * @var dt
     * @brief Time between two frame intervals based on the target framerate.
     */
    double dt;

    /**
     * @var fps
     * @brief Target framerate
     */
    double fps;

    double angle;

    /**
     * @var state
     * @brief interface state important for handling input
     */
    unsigned int state;

    unsigned int num_frames;

    std::unique_ptr<EngineClient> engine_client;
    std::shared_ptr<PostProcessor> post_processor;
    std::shared_ptr<Screen> screen;
    std::shared_ptr<Camera> camera;
    std::shared_ptr<Mouse> mouse;
    std::shared_ptr<FontWriter> font_writer;

    std::unique_ptr<Game> game;

public:
    /**
     * @fn Engine method
     * @brief Engine constructor method
     *
     * Loads up the display and initializes all entities.
     *
     */
    Engine();

    /**
     * @fn run method
     * @brief Constructs a new game
     *
     * In the run method, a while loop is started wherin the game state is
     * propagated over time.
     *
     * @return void
     */
    void run(int argc, char* argv[]);

private:
    /**
     * @fn update method
     * @brief Handles time integration
     *
     * Function handling time propagation
     *
     * @param dt Time integration constant
     */
    void update(double dt);

    /**
     * @brief Perform these actions at every second the program is running
     */
    void update_second();

    void pre_draw();

    void draw();

    void post_draw();

    void bind_commands();
};

#endif // _VISUALIZER_H
