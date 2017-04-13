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
Camera::Camera() {
    this->position = glm::vec3(0.0f, 0.0f, 5.0f);
    this->update();
}

/**
 * @brief       update the camera perspective matrix
 *
 * @return      void
 */
void Camera::update() {
    this->projection = glm::infinitePerspective(45.0f, this->aspect_ratio, 0.1f);

    glm::vec3 euler = glm::eulerAngles(this->orientation);


    const glm::vec3 camera_dir = this->position + glm::rotate(this->orientation, glm::vec3(0,0,-1));
    const glm::vec3 camera_up = glm::rotate(this->orientation, glm::vec3(0,1,0));

    this->view = glm::lookAt(
                    this->position,
                    camera_dir,
                    camera_up
                );
}

/**
 * @brief       translate the camera in the clock-wise direction
 *
 * @return      void
 */
void Camera::translate(const glm::vec3& trans) {
    this->position += glm::toMat3(this->orientation) * trans;
    this->update();
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

void Camera::rotate(double x, double y) {
    static const float sensitity = 5e-4;

    if(x == 0 && y == 0) {
        return;
    }

    const glm::quat qx = glm::angleAxis((float)x * sensitity, glm::vec3(0,-1,0));
    const glm::quat qy = glm::angleAxis((float)y * sensitity, glm::vec3(-1,0,0));

    this->orientation = glm::normalize(qx * qy) * this->orientation;

    this->update();
}
