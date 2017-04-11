/**************************************************************************
 *   command_on_resize.h  --  This file is part of AFELIRIN.              *
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

#ifndef _COMMAND_ON_RESIZE_H
#define _COMMAND_ON_RESIZE_H

#include <memory>

class CommandOnResize : public CommandP2<int, int> {
private:
    std::shared_ptr<Screen> screen;
    std::shared_ptr<PostProcessor> post_processor;
    std::shared_ptr<Camera> camera;

public:
    CommandOnResize(const std::shared_ptr<Screen> _screen,
                    const std::shared_ptr<PostProcessor> _postprocessor,
                    const std::shared_ptr<Camera> _camera) :
    screen(_screen),
    post_processor(_postprocessor),
    camera(_camera) { }

    void execute(int width, int height) {
        // // update screen settings
        this->screen->set_width(width);
        this->screen->set_height(height);

        // update camera settings
        this->camera->set_aspect_ratio(this->screen->get_aspect_ratio_resolution());
        this->camera->update();

        // update post processor
        this->post_processor->window_reshape();
    }
};

#endif // _COMMAND_ON_RESIZE_H
