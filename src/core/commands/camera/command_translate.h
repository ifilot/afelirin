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

#ifndef _CAMERA_COMMAND_TRANSLATE
#define _CAMERA_COMMAND_TRANSLATE

#include <memory>

class CameraCommandTranslate : public Command {
private:
    std::shared_ptr<Camera> camera;
    glm::vec3 direction;

public:
    CameraCommandTranslate(const std::shared_ptr<Camera> _camera,
                           float speed,
                           const glm::vec3& _direction) :
    camera(_camera),
    direction(speed * _direction) { }

    void execute() {
        this->camera->translate(this->direction);
    }
};

#endif // _CAMERA_COMMAND_TRANSLATE
