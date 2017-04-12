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

#ifndef _COMMAND_ON_MOUSE_CURSOR
#define _COMMAND_ON_MOUSE_CURSOR

#include <memory>

class EngineCommandOnMouseCursor : public Command {
private:
    std::shared_ptr<Mouse> mouse;

public:
    EngineCommandOnMouseCursor(const std::shared_ptr<Mouse> _mouse) :
    mouse(_mouse) { }

    void execute() {
        const double xpos = this->get_param<double>("xpos");
        const double ypos = this->get_param<double>("ypos");

        this->mouse->set_cursor(xpos, ypos);
    }
};

#endif // _COMMAND_ON_MOUSE_CURSOR
