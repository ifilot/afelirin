/**************************************************************************
 *   camera_fps.h  --  This file is part of AFELIRIN.                     *
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

#ifndef _CAMERA_FPS_H
#define _CAMERA_FPS_H

#include "camera.h"

class CameraRTS : public Camera {
public:
    CameraRTS();

    CameraRTS(const glm::vec3& _position);

    /**
     * @brief       translate the camera
     *
     * @param       translation vector
     *
     * @return      void
     */
    void translate(const glm::vec3& trans);

    /**
     * @brief       rotate the camera
     *
     * @param       Euler angle
     *
     * @return      void
     */
    void rotate(const glm::vec3& trans);
};

#endif //_CAMERA_FPS_H
