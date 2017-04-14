/**************************************************************************
 *   entity.h  --  This file is part of AFELIRIN.                         *
 *                                                                        *
 *   Copyright (C) 2017, Ivo Filot (ivo@ivofilot.nl)                      *
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

#ifndef _ENTITY_H
#define _ENTITY_H

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/transform.hpp>
#include <GL/glew.h>

class Entity {
protected:
    GLuint vao;
    unsigned int nr_indices;

    // position and orientation
    glm::vec3 pos;
    glm::quat rot;
    glm::vec3 scale;

    // angular momentum
    glm::vec4 v_rot;

    glm::vec3 color;

public:
    Entity() {}

    Entity(const glm::vec3& _pos, GLuint _vao, unsigned int _nr_indices);

    virtual void update(double dt);

    virtual void draw() = 0;

    inline void set_position(const glm::vec3& _pos) {
        this->pos = _pos;
    }

    inline void set_scale(const glm::vec3& _scale) {
        this->scale = _scale;
    }

    inline void set_color(const glm::vec3& _color) {
        this->color = _color;
    }

    inline const glm::vec3& get_position() const {
        return this->pos;
    }

    inline const glm::vec3& get_color() const {
        return this->color;
    }

    inline glm::mat4 get_rotation() const {
        return glm::toMat4(this->rot);
    }

    inline glm::mat4 get_scale() const {
        return glm::scale(this->scale);
    }

    inline void rotate(float angle, const glm::vec3& axis) {
        this->rot *= glm::angleAxis(angle, axis);
    }

    inline void set_angular_momentum(float velocity, const glm::vec3& axis) {
        this->v_rot = glm::vec4(glm::normalize(axis), velocity);
    }

protected:
};

#endif //_ENTITY_H
