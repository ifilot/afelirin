/**************************************************************************
 *   camera.cpp  --  This file is part of AFELIRIN.                       *
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

#include "camera.h"

/**
 * @brief       camera constructor
 *
 * @return      camera instance
 */
Camera::Camera() :
    position(0.0f, 0.0f, 5.0f),
    center(0.0f, 0.0f, -1.0f),
    up(0.0f, 1.0f, 0.0f)
{

    this->update();
}

Camera::Camera(const glm::vec3& _position) :
    position(_position),
    center(0.0f, 0.0f, -1.0f),
    up(0.0f, 1.0f, 0.0f)
{

    this->update();
}

/**
 * @brief       update the camera perspective matrix
 *
 * @return      void
 */
void Camera::update() {
    // calculate projection
    this->projection = glm::infinitePerspective(45.0f, this->aspect_ratio, 0.1f);

    // calculate view matrix
    this->view = glm::lookAt(
                    this->position,
                    this->position + this->center,
                    this->up
                );
}

/**
 * @brief      set camera position and up direction
 *
 * @param      camera position
 * @param      up direction
 * @return     void
 */
void Camera::set_camera_position(const glm::vec3& _position, const glm::vec3& _up) {
    this->update();
}
