/**************************************************************************
 *   entity.h  --  This file is part of OBJ2BIT.                          *
 *                                                                        *
 *   Copyright (C) 2017, Ivo Filot (ivo@ivofilot.nl)                      *
 *                                                                        *
 *   OBJ2BIT is free software:                                            *
 *   you can redistribute it and/or modify it under the terms of the      *
 *   GNU General Public License as published by the Free Software         *
 *   Foundation, either version 3 of the License, or (at your option)     *
 *   any later version.                                                   *
 *                                                                        *
 *   OBJ2BIT is distributed in the hope that it will be useful,           *
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

#include <glm/glm.hpp>
#include <GL/glew.h>

class Entity {
private:
    glm::vec3 pos;
    GLuint vao;
    unsigned int nr_indices;
    float rotation;
    float rotation_speed;
    glm::vec3 color;

public:
    Entity(const glm::vec3& _pos, GLuint _vao, unsigned int _nr_indices);

    void update(double dt);

    void draw();

    inline void set_position(const glm::vec3& _pos) {
        this->pos = _pos;
    }

    inline void set_color(const glm::vec3& _color) {
        this->color = _color;
    }

    inline void set_rotation(float _rotation) {
        this->rotation = _rotation;
    }

    inline void set_rotation_speed(float _rotation_speed) {
        this->rotation_speed = _rotation_speed;
    }

    inline const glm::vec3& get_position() const {
        return this->pos;
    }

    inline const glm::vec3& get_color() const {
        return this->color;
    }

    inline float get_rotation() const {
        return this->rotation;
    }

private:
};

#endif //_ENTITY_H
