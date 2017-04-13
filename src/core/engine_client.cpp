/**************************************************************************
 *   engine_client.cpp  --  This file is part of AFELIRIN.                *
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

#include "engine_client.h"

/**
 * @brief EngineClient constructor
 *
 * Initializes the GLFW library, constructs a window and put it into context.
 * Callbacks are set-up and the GLEW library is initialized.
 *
 */
EngineClient::EngineClient() {
    // set the error callback
    glfwSetErrorCallback(error_callback);

    // initialize the library
    if(!glfwInit()) {
        exit(EXIT_FAILURE);
    }

    // set window hints
    //glfwWindowHint(GLFW_FLOATING, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
	glfwWindowHint(GLFW_DECORATED, GL_TRUE);

    int major, minor, rev;
    glfwGetVersion(&major, &minor, &rev);

    //
    if(Settings::get().get_boolean_from_keyword("settings.screen.full_screen")) {
        const unsigned int width = Settings::get().get_uint_from_keyword("settings.screen.resolution_x");
        const unsigned int height = Settings::get().get_uint_from_keyword("settings.screen.resolution_y");
        this->m_window = glfwCreateWindow(width, height, "AFELIRIN DEMO" , NULL, NULL);
    } else {
        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);
        this->m_window = glfwCreateWindow(mode->width, mode->height, "AFELIRIN DEMO" , monitor, NULL);
    }

    // check if the window is properly constructed
    if (!this->m_window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    // set the context for OpenGL
    glfwMakeContextCurrent(this->m_window);
    glfwSwapInterval(1);

    // set the key callback
    glfwSetKeyCallback(this->m_window, key_callback);

    // set mouse key callback
    glfwSetMouseButtonCallback(this->m_window, mouse_button_callback);

    // set framebuffer callback when a window is resized
	glfwSetFramebufferSizeCallback(this->m_window, framebuffer_size_callback);

    // set mouse cursor position callback
    glfwSetInputMode(this->m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(this->m_window, mouse_cursor_callback);

    // set scroll callback
    glfwSetScrollCallback(this->m_window, scroll_callback);

    // set drop callback
    glfwSetDropCallback(this->m_window, drop_callback);

    // set character callback
    glfwSetCharCallback(this->m_window, this->char_callback);

    // set user pointer
    glfwSetWindowUserPointer(this->m_window, (void*)this);

    // initialize GLEW
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Could not initialize GLEW" << std::endl;
    }

    // enable transparency
    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // enable culling
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
}

/**
 * @brief close frame function
 *
 * Perform these instructions at the start of each frame
 */
void EngineClient::open_frame() {

}

/**
 * @brief open frame function
 *
 * Perform these instructions at the end of each frame
 */
void EngineClient::close_frame() {
    glfwSwapBuffers(this->m_window);
    glfwPollEvents();
}

/*
 * @brief Checks if the window is closed and if so, terminates the program
 */
bool EngineClient::is_closed() {
    return glfwWindowShouldClose(this->m_window);
}

/**
 * @brief EngineClient destructor
 *
 * Destructs the display class and terminates the window and the glfw library
 */
EngineClient::~EngineClient() {
    glfwDestroyWindow(this->m_window);
    glfwTerminate();
}

/*
 * @brief center the mouse pointer
 *
 * @param window_name   the window name
 */
void EngineClient::set_window_title(const std::string& window_name) {
    glfwSetWindowTitle(this->m_window, window_name.c_str());
}

/*
 * @brief updates the resolution of the screen, camera and postprocessor
 */
void EngineClient::update_resolution() {
    // get values
    int width, height;
    glfwGetWindowSize(this->m_window, &width, &height);

    // set parameters
    this->cmdcont.get_cmd("on_resize")->set_param("width", width)
                                      ->set_param("height", height);

    // execute command
    this->cmdcont.execute_cmd("on_resize");
}

/*
 * *********
 * CALLBACKS
 * *********
 */

/**
 * @brief error callback function
 *
 * @param error         error code
 * @param description   error description
 *
 */
void EngineClient::error_callback(int error, const char* description) {
    std::cerr << description << std::endl;
}

/**
 * @brief Registers and handles key presses
 *
 * @param[in] window   pointer to window
 * @param[in] key      keyboard key
 * @param[in] scancode
 * @param[in] action
 * @param[in] mods
 *
 */
void EngineClient::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
        return;
    }

    // obtain pointer to this EngineClient
    EngineClient* ec = reinterpret_cast<EngineClient*>(glfwGetWindowUserPointer(window));

    switch(key) {
        case 'W':
            ec->cmdcont.get_cmd("on_key_w")->execute();
        break;
        case 'A':
            ec->cmdcont.get_cmd("on_key_a")->execute();
        break;
        case 'S':
            ec->cmdcont.get_cmd("on_key_s")->execute();
        break;
        case 'D':
            ec->cmdcont.get_cmd("on_key_d")->execute();
        break;
        default:
            // do nothing
        break;
    }
}

/**
 * @brief registers and handles mouse button presses
 *
 * @param[in] window   pointer to window
 * @param[in] button
 * @param[in] action
 * @param[in] mods
 *
 */
void EngineClient::mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {

}

/**
 * @brief registers and handles mouse button presses
 *
 * @param[in] window   pointer to window
 * @param[in] xoffset  scroll wheel offset in x direction
 * @param[in] yoffset  scroll wheel offset in y direction
 *
 */
void EngineClient::scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {

}

/**
 * @brief handles file dropping in the window
 *
 * @param[in] window    pointer to window
 * @param[in] count     number of files
 * @param[in] paths     pathnames
 *
 */
void EngineClient::drop_callback(GLFWwindow* window, int count, const char** paths) {

}

/**
 * @brief registers and handles mouse button presses
 *
 * @param[in] window    pointer to window
 * @param[in] xpos      x position of the mouse cursor on screen
 * @param[in] ypos      y position of the mouse cursor on screen
 *
 */
void EngineClient::mouse_cursor_callback(GLFWwindow* window, double xpos, double ypos) {
    static const std::string cmd_string = "on_mouse_cursor";

    // obtain pointer to this EngineClient
    EngineClient* ec = reinterpret_cast<EngineClient*>(glfwGetWindowUserPointer(window));

    // set parameters
    ec->cmdcont.get_cmd(cmd_string)->set_param("xpos", xpos)
                                   ->set_param("ypos", ypos);

    // execute command
    ec->cmdcont.execute_cmd(cmd_string);
}

/**
 * @brief parses input characters from keyboard
 *
 * @param[in] window    pointer to window
 * @param[in] window    key to parse
 *
 */
void EngineClient::char_callback(GLFWwindow* window, unsigned int key) {

}

/**
 * @brief perform window resizing
 */
void EngineClient::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    static const std::string cmd_string = "on_resize";

    // obtain pointer to this EngineClient
    EngineClient* ec = reinterpret_cast<EngineClient*>(glfwGetWindowUserPointer(window));

    // set parameters
    ec->cmdcont.get_cmd(cmd_string)->set_param("width", width)
                                   ->set_param("height", height);

    // execute command
    ec->cmdcont.execute_cmd(cmd_string);
}
