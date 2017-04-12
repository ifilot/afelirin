/**************************************************************************
 *   entity.cpp  --  This file is part of OBJ2BIT.                        *
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

#include "entity.h"

Entity::Entity(const glm::vec3& _pos, GLuint _vao, unsigned int _nr_indices) :
    pos(_pos),
    vao(_vao),
    nr_indices(_nr_indices) {

    this->rotation = 0.0f;
    this->rotation_speed = 1.0f;
    this->color = glm::vec3(1,1,1);
}

void Entity::update(double dt) {
    this->rotation += dt * this->rotation_speed;

    if(this->rotation >= 2 * M_PI) {
        this->rotation -= 2 * M_PI;
    }
}

void Entity::draw() {
    glBindVertexArray(this->vao);
    glDrawElements(GL_TRIANGLES, this->nr_indices, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
