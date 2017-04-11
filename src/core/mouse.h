/**************************************************************************
 *   mouse.h  --  This file is part of AFELIRIN.                          *
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

#ifndef _MOUSE_H
#define _MOUSE_H

#include <iostream>
#include <memory>
#include <algorithm>

#include "core/camera.h"
#include "core/screen.h"
#include "core/shader.h"

#include "util/singleton_holder.h"

/**
 * @class MouseImpl class
 *
 * @brief class handling mouse actions such as raycasting
 *
 */
class MouseImpl {
private:
    glm::vec2 cur_pos;                    //!< current cursor position
    glm::vec2 cur_pos_sw;                 //!< current cursor position with origin in SW position

public:
    /**
     * @brief       mouse constructor
     */
    MouseImpl();

    /*
     * @brief Draw action so the mouse
     */
    void draw();

    inline const glm::vec2& get_cursor() const {
        return this->cur_pos;
    }

    inline const glm::vec2& get_cursor_sw() const {
        return this->cur_pos_sw;
    }

    /*
     * @brief Update the current cursor position
     *
     * @param[in] xpos      current x position of the cursor on the screen
     * @param[in] xpos      current y position of the cursor on the screen
     */
    inline void set_cursor(double xpos, double ypos) {
        this->cur_pos[0] = (float)xpos;
        this->cur_pos[1] = (float)ypos;
        this->cur_pos_sw[0] = (float)xpos;
        this->cur_pos_sw[1] = (float)Screen::get().get_height() - (float)ypos;
    }

private:
};

typedef SingletonHolder<MouseImpl> Mouse;

#endif //_MOUSE_H
