/**************************************************************************
 *   mesh_loader.cpp  --  This file is part of OBJ2BIT.                   *
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

#include "mesh_loader.h"

void MeshLoader::load_mesh(GLuint* vao, GLuint* vbo, unsigned int* nr_indices, Mesh* mesh) {

    // generate a vertex array object and store it in the pointer
    glGenVertexArrays(1, vao);
    glBindVertexArray(*vao);

    // generate a number of buffers (blocks of data on the GPU)
    glGenBuffers(3, vbo);

    /*
     * POSITIONS
     */

    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, mesh->get_vertices().size() * 3 * sizeof(float), &mesh->get_vertices()[0][0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    /*
     * NORMALS
     */

    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glBufferData(GL_ARRAY_BUFFER, mesh->get_normals().size() * 3 * sizeof(float), &mesh->get_normals()[0][0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

    /*
     * INDICES
     */

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[2]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->get_indices().size() * sizeof(unsigned int), &mesh->get_indices()[0], GL_STATIC_DRAW);

    glBindVertexArray(0);

    *nr_indices = mesh->get_indices().size();
}
