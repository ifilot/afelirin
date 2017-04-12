/**************************************************************************
 *   engine_client.h  --  This file is part of AFELIRIN.                  *
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

#ifndef _DISPLAY_H
#define _DISPLAY_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <cstdlib> // EXIT_FAILURE
#include <iostream>
#include <memory>
#include <boost/format.hpp>
#include <boost/noncopyable.hpp>

#include "core/settings.h"

#include "util/command.h"

/**
 * @class EngineClient class
 *
 * @brief class handling the display
 *
 */
class EngineClient : private boost::noncopyable {
private:
    GLFWwindow* m_window;       //!< pointer to the window

    // list of command objects
    CommandController cmdcont;

public:
    /**
     * @brief EngineClient constructor
     *
     * Initializes the GLFW library, constructs a window and put it into context.
     * Callbacks are set-up and the GLEW library is initialized.
     *
     */
    EngineClient();

    /**
     * EngineClient destructor
     * Destructs the display class and terminates the window and the glfw library
     */
    virtual ~EngineClient();

    /**
     * @brief close frame function
     *
     * Perform these instructions at the start of each frame
     */
    void open_frame();

    /**
     * @brief open frame function
     *
     * Perform these instructions at the end of each frame
     */
    void close_frame();

    /*
     * @brief Checks if the window is closed and if so, terminates the program
     */
    bool is_closed();

    /*
     * @brief get aspect ratio function
     *
     * @return the aspect ratio
     */
    float get_aspect_ratio() const;

    /*
     * @brief center the mouse pointer
     *
     * @param window_name   the window name
     */
    void set_window_title(const std::string& window_name);

    /*
     * @brief updates the resolution of the screen; called by Engine after EngineClient is created
     */
    void update_resolution();

    /*
     * @brief get a pointer to the GLFW window
     *
     * @return the pointer to the window
     */
    inline GLFWwindow* get_window_ptr() {
        return this->m_window;
    }

    /**
     * @brief error callback function
     *
     * @param error         error code
     * @param description   error description
     *
     */
    static void error_callback(int error, const char* description);

    /**
     * @brief Registers and handles key presses
     *
     */
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

    /**
     * @brief registers and handles mouse button presses
     */
    static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

    /**
     * @brief perform window resizing
     */
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

    /**
     * @brief handle scroll callbacks
     */
    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

    /**
     * @brief handle cursor callbacks
     */
    static void mouse_cursor_callback(GLFWwindow* window, double xpos, double ypos);

    /**
     * @brief handle drop callback
     */
    static void drop_callback(GLFWwindow* window, int count, const char** paths);

    /**
     * @brief parses input characters from keyboard
     *
     * @param[in] window    pointer to window
     * @param[in] window    key to parse
     *
     */
    static void char_callback(GLFWwindow* window, unsigned int key);

    //---------------------------------------------
    // COMMAND SETTERS
    //---------------------------------------------

    inline void bind_command(const std::string& name, Command* _cmd) {
        this->cmdcont.add_cmd(name, _cmd);
    }
};

#endif // _DISPLAY_H
