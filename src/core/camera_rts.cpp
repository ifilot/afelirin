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

#include "camera_rts.h"

CameraRTS::CameraRTS() {}

CameraRTS::CameraRTS(const glm::vec3& _position) :
    Camera(_position) {

    static const glm::vec3 rot(0.0f, glm::radians(30.0f), 0.0f);

    this->center = glm::mat3(glm::rotate(rot[0], this->up)) * this->center;

    this->right = glm::normalize(glm::cross(this->center, this->up));

    this->center = glm::mat3(glm::rotate(rot[1], this->right)) * this->center;

    this->update();
}

/**
 * @brief       translate the camera
 *
 * @param       translation vector
 *
 * @return      void
 */
void CameraRTS::translate(const glm::vec3& trans) {
    this->position += trans;
    this->update();
}

/**
 * @brief       rotate the camera
 *
 * @param       Euler angle
 *
 * @return      void
 */
void CameraRTS::rotate(const glm::vec3& rot) {
    // do not perform any rotate commands
}
