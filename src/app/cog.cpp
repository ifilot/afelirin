/**************************************************************************
 *   cog.cpp  --  This file is part of AFELIRIN.                          *
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

#include "cog.h"

Cog::Cog(const glm::vec3& _pos, GLuint _vao, unsigned int _nr_indices) :
    Entity(_pos, _vao, _nr_indices) {

}

void Cog::update(double dt) {
    Entity::update(dt);
}

void Cog::draw() {
    glBindVertexArray(this->vao);
    glDrawElements(GL_TRIANGLES, this->nr_indices, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
