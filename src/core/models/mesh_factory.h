/**************************************************************************
 *   mesh_factory.h  --  This file is part of AFELIRIN.                   *
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

#ifndef _MESH_FACTORY_H
#define _MESH_FACTORY_H

#include <unordered_map>

#include "core/asset_manager.h"
#include "mesh_loader.h"
#include "mesh_parser.h"

class MeshFactory {
    class VertexBuffer {
        public:
            GLuint vao;
            GLuint vbo[4];
            Mesh* mesh;
            unsigned int type;
            unsigned int nr_indices;

            VertexBuffer();

            ~VertexBuffer();
    };

private:
    std::unordered_map<std::string, VertexBuffer> meshes;
    MeshLoader ml;
    MeshParser mp;

public:
    MeshFactory();

    void get_mesh_objects(const std::string& name, GLuint* vao, unsigned int* nr_indices);

    GLuint get_vao(const std::string& name);

    unsigned int get_nr_indices(const std::string& name);

private:
    void load_mesh(const std::string& name);

    const VertexBuffer* get_buffer(const std::string& name);
};

#endif //_MESH_FACTORY_H
