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
#include <boost/noncopyable.hpp>

#include "core/camera.h"
#include "core/screen.h"
#include "core/shader.h"

/**
 * @class Mouse class
 *
 * @brief class handling mouse actions such as raycasting
 *
 */
class Mouse : boost::noncopyable {
private:
    glm::vec2 cur_pos;                    //!< current cursor position
    glm::vec2 cur_pos_prev;               //!< previous cursor position
    glm::vec2 cur_pos_sw;                 //!< current cursor position with origin in SW position
    glm::vec2 cur_pos_ctr;                //!< current cursor w.r.t. center
    glm::vec2 cur_delta_pos;              //!< current cursor w.r.t. center
    bool start;

    std::shared_ptr<Screen> screen;

public:
    /**
     * @brief       mouse constructor
     */
    Mouse(const std::shared_ptr<Screen>& _screen);

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

    inline const glm::vec2& get_cursor_ctr() const {
        return this->cur_pos_ctr;
    }

    inline const glm::vec2& get_cursor_delta() const {
        return this->cur_delta_pos;
    }

    /*
     * @brief Update the current cursor position
     *
     * @param[in] xpos      current x position of the cursor on the screen
     * @param[in] xpos      current y position of the cursor on the screen
     */
    inline void set_cursor(double xpos, double ypos) {
        this->cur_pos_prev = this->cur_pos;

        this->cur_pos[0] = (float)xpos;
        this->cur_pos[1] = (float)ypos;

        this->cur_pos_sw[0] = (float)xpos;
        this->cur_pos_sw[1] = (float)this->screen->get_height() - (float)ypos;

        this->cur_pos_ctr[0] = (float)xpos - (float)this->screen->get_width() / 2.0f;
        this->cur_pos_ctr[1] = (float)ypos - (float)this->screen->get_height() / 2.0f;

        if(!this->start) {
            this->cur_delta_pos = this->cur_pos - this->cur_pos_prev;
        } else {
            this->cur_delta_pos = glm::vec2(0.0f, 0.0f);
            this->start = false;
        }
    }

private:
};

#endif //_MOUSE_H
