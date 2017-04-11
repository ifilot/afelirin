/**************************************************************************
 *   engine.cpp  --  This file is part of AFELIRIN.                       *
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

#include "engine.h"

/**
 * @fn Engine method
 * @brief Engine constructor method
 *
 * Loads up the display and initializes all entities.
 *
 * @return Engine class
 */
Engine::Engine():
    accumulator(0.0),       /* default accumulator should be zero */
    fps(60.0),              /* set the target framerate */
    num_frames(0) {

    this->angle = 0.0;

    /* calculate the time interval */
    this->dt = 1.0 / fps;

    /* set the time at the frame start */
    this->frame_start = glfwGetTime();

    // set-up engine
    this->engine_client = std::unique_ptr<EngineClient>(new EngineClient);

    // load screen
    this->screen = std::shared_ptr<Screen>(new Screen());

    // load PostProcessor
    this->post_processor = std::shared_ptr<PostProcessor>(new PostProcessor(this->screen));
    this->post_processor->window_reshape();

    // load camera
    this->camera = std::shared_ptr<Camera>(new Camera());

    // Load font writer and fonts
    this->font_writer = std::shared_ptr<FontWriter>(new FontWriter(this->screen));
    this->font_writer->add_font("./assets/fonts/retro.ttf",
                                    14,              // font size
                                    0.43f, 0.25f,    // sdf settings
                                    32,             // start char
                                    222             // number of chars
                                    );

    this->screen->set_resolution_x(Settings::get().get_uint_from_keyword("settings.screen.resolution_x"));
    this->screen->set_resolution_y(Settings::get().get_uint_from_keyword("settings.screen.resolution_y"));

    // bind all commands to EngineClient
    this->bind_commands();
    this->engine_client->update_resolution();
}

/**
 * @fn run method
 * @brief Constructs a new game
 *
 * In the run method, a while loop is started wherein the game state is
 * propagated over time.
 *
 * @return void
 */
void Engine::run(int argc, char* argv[]) {
    if(argc > 2) {
        std::cerr << "Invalid number of arguments" << std::endl;
    }

    /**
     * @var num_frames
     * @brief Counts the number of frames in a single second
     */
    this->num_frames = 0;

    /**
     * @var last_time
     * @brief The time since the execution of the program after the
     *        last frame call.
     */
    double last_time = glfwGetTime();

    /* while the display runs, do at every frame */
    while(!this->engine_client->is_closed()) {

        /**
         * @var current_time
         * @brief The time since the execution of the program before the
         *        new integration step(s)
         */
        const double current_time = glfwGetTime();

        /* add passed time to the accumulator */
        this->accumulator += current_time - frame_start;

        /* keep integrating the game state until the accumulator
           is sufficiently depleted that a frame can be rendered */
        while(accumulator >= dt) {
            this->update(dt);
            this->accumulator -= dt;
        }

        /* calculate the FPS at every second and update the window
           title accordingly */
        if(current_time - last_time >= 1.0) {

            std::string sfps = boost::lexical_cast<std::string>(this->num_frames);
            this->engine_client->set_window_title("Quadtree");

            // place in the function any commands that should be done every second
            this->update_second();

            /* reset counters */
            last_time = glfwGetTime();
            this->num_frames = 0;
        }

        /* set the start time of the frame rendering */
        this->frame_start = current_time;

        /* render the game state */
        this->num_frames++;            /* increment frame counter */

        // perform pre-drawing operations
        this->pre_draw();

        // start drawing from here
        this->draw();

        // perform post-drawing operations (post processing)
        this->post_draw();
    }
}

/**
 * @fn update method
 * @brief Handles time integration
 *
 * Function handling time propagation
 *
 * @param dt Time integration constant
 */
void Engine::update(double dt) {

}

void Engine::update_second() {

}

/**
 * @brief Setup drawing state
 *
 * Activates all draw classes and binds the frame buffer for the MSAA
 *
 */
void Engine::pre_draw() {
    this->screen->set_focus(glfwGetWindowAttrib(this->engine_client->get_window_ptr(), GLFW_FOCUSED));
    this->engine_client->open_frame();   /* start new frame */

    // first create a texture map
    Light::get().update();

    // then perform the normal rendering in the PostProcessor texture
    this->post_processor->bind_frame_buffer();
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, this->screen->get_resolution_x(), this->screen->get_resolution_y());
    this->camera->update();
}

/**
 * @brief Draw call
 *
 * Draw all sprites on the screen
 *
 */
void Engine::draw() {
    this->font_writer->write_text(0, 50.f, 50.f, 0.f, glm::vec3(1,1,1), "Quadtree");
}

/**
 * @brief Post draw routine
 *
 * Unbind frame buffer, render MSAA and draw the GUI
 *
 */
void Engine::post_draw() {
    this->post_processor->unbind_frame_buffer();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glViewport(0, 0, this->screen->get_width(), this->screen->get_height());
    this->post_processor->draw();

    this->engine_client->close_frame();
}

void Engine::bind_commands() {
    if(!this->screen) {
        throw std::logic_error("Illegal bind command found, you have to initialize screen first.");
    }
    if(!this->post_processor) {
        throw std::logic_error("Illegal bind command found, you have to initialize post_processor first.");
    }
    if(!this->camera) {
        throw std::logic_error("Illegal bind command found, you have to initialize camera first.");
    }

    this->engine_client->bind_command_on_resize(new CommandOnResize(this->screen, this->post_processor, this->camera));
}