/**************************************************************************
 *   mesh_loader.h  --  This file is part of OBJ2BIT.                     *
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

#ifndef _MESH_LOADER_H
#define _MESH_LOADER_H

#include <string>
#include <stdexcept>
#include <fstream>
#include <iostream>
#include <GL/glew.h>

#include "mesh_simple.h"
#include "mesh_uv.h"

class MeshLoader {
private:

public:
    MeshLoader() {}

    void load_mesh(GLuint* vao, GLuint* vbo, unsigned int* nr_indices, MeshBase* mesh);

private:

};

#endif //_MESH_LOADER_H
