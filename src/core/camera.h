/**************************************************************************
 *   camera.h  --  This file is part of AFELIRIN.                         *
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

#ifndef _CAMERA_H
#define _CAMERA_H

#define GLM_SWIZZLE
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <iostream>
#include <algorithm>
#include <boost/noncopyable.hpp>

#include "util/singleton_holder.h"
#include "core/screen.h"

#include <glm/gtx/euler_angles.hpp>

/**
 * @class Camera class
 * @brief class handling the camera
 */
class Camera : private boost::noncopyable {
private:
    glm::mat4 projection;               //!< perspective matrix
    glm::mat4 view;                     //!< view matrix

    glm::vec3 position;                 //!< position of the camera in world space
    glm::vec3 up;                       //!< up direction of the camera
    glm::vec3 center;                   //!< center direction of the camera
    glm::vec3 right;                    //!< right direction of the camera

    glm::mat3 rotmat;

    float aspect_ratio;                     //!< aspect ratio of the window

public:
    Camera();

    //*************************
    // GETTERS
    //*************************

    /**
     * @brief       get current view matrix
     *
     * @return      view matrix
     */
    inline const glm::mat4& get_view() const {
        return this->view;
    }

    /**
     * @brief       get current projection matrix
     *
     * @return      projection matrix
     */
    inline const glm::mat4& get_projection() const {
        return this->projection;
    }

    /**
     * @brief       get current camera position
     *
     * @return      position
     */
    inline const glm::vec3& get_position() const {
        return this->position;
    }

    /**
     * @brief       get current camera center direction
     *
     * @return      position
     */
    inline const glm::vec3& get_center() const {
        return this->center;
    }

    /**
     * @brief       get current camera up direction
     *
     * @return      position
     */
    inline const glm::vec3& get_up() const {
        return this->up;
    }

    //*************************
    // SETTERS
    //*************************

    /**
     * @brief       set the camera aspect ratio
     *
     * @param       aspect ratio
     * @return      void
     */
    inline void set_aspect_ratio(float _aspect_ratio) {
        this->aspect_ratio = _aspect_ratio;
    }

    /**
     * @brief       set the projection matrix
     *
     * @param       projection matrix
     * @return      void
     */
    inline void set_projection(const glm::mat4& _projection) {
        this->projection = _projection;
    }

    /**
     * @brief       update the camera perspective matrix
     *
     * @return      void
     */
    void update();

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

    /**
     * @brief      set camera position and up direction
     *
     * @param      camera position
     * @param      up direction
     * @return     void
     */
    void set_camera_position(const glm::vec3& _position, const glm::vec3& _up);

};

#endif // _CAMERA_H
