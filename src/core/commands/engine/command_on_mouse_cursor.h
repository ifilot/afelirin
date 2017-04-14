/**************************************************************************
 *   command_on_mouse_cursor.h  --  This file is part of AFELIRIN.        *
 *                                                                        *
 *   Copyright (C) 2017, Ivo Filot                                        *
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

/*
 * @file: command_on_mouse_cursor.h
 *
 * Used in Command Design Pattern; this function is passed to the EngineClient
 * class and is executed when the mouse cursor is moved.
 *
 */

#ifndef _ENGINE_COMMAND_ON_MOUSE_CURSOR
#define _ENGINE_COMMAND_ON_MOUSE_CURSOR

#include <memory>
#include <glm/gtx/string_cast.hpp>

class EngineCommandOnMouseCursor : public Command {
private:
    std::shared_ptr<Mouse> mouse;
    std::shared_ptr<Camera> camera;

public:
    EngineCommandOnMouseCursor(const std::shared_ptr<Mouse> _mouse,
                               const std::shared_ptr<Camera> _camera) :
    mouse(_mouse),
    camera(_camera) { }

    void execute() {
        static const float c = 1e-3f;   //!< movement speed

        const double xpos = this->get_param<double>("xpos");
        const double ypos = this->get_param<double>("ypos");

        this->mouse->set_cursor(xpos, ypos);

        const glm::vec2 cur_pos_ctr = this->mouse->get_cursor_delta();

        const glm::vec3 trans(-cur_pos_ctr[0], cur_pos_ctr[1], 0.0f);

        this->camera->rotate(trans * c);
    }
};

#endif // _ENGINE_COMMAND_ON_MOUSE_CURSOR
