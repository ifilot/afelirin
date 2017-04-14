/**************************************************************************
 *   camera_fps.cpp  --  This file is part of AFELIRIN.                   *
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

#include "camera_fps.h"

CameraFPS::CameraFPS() {}

CameraFPS::CameraFPS(const glm::vec3& _position) :
    Camera(_position) {}

/**
 * @brief       translate the camera
 *
 * @param       translation vector
 *
 * @return      void
 */
void CameraFPS::translate(const glm::vec3& trans) {
    this->position += this->right * trans[0] + this->up * trans[1] - glm::normalize(glm::vec3(this->center.x, 0.0f, this->center.z)) * trans[2];
    this->update();
}

/**
 * @brief       rotate the camera
 *
 * @param       Euler angle
 *
 * @return      void
 */
void CameraFPS::rotate(const glm::vec3& rot) {
    this->center = glm::mat3(glm::rotate(rot[0], this->up)) * this->center;

    this->right = glm::normalize(glm::cross(this->center, this->up));

    this->center = glm::mat3(glm::rotate(rot[1], this->right)) * this->center;

    this->update();
}
