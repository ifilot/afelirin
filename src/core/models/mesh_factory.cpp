/**************************************************************************
 *   mesh_factory.cpp  --  This file is part of AFELIRIN.                 *
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

#include "mesh_factory.h"

MeshFactory::VertexBuffer::VertexBuffer() {
    this->mesh = new Mesh();
}

MeshFactory::VertexBuffer::~VertexBuffer() {
    glDeleteBuffers(4, this->vbo);
    glDeleteVertexArrays(1, &this->vao);
    delete this->mesh;
}

MeshFactory::MeshFactory() {

}

void MeshFactory::get_mesh_objects(const std::string& name, GLuint* vao, unsigned int* nr_indices) {
    const VertexBuffer* buf = this->get_buffer(name);
    if(buf != nullptr) {
        *vao = buf->vao;
        *nr_indices = buf->nr_indices;
    } else {
        this->load_mesh(name);
        this->get_mesh_objects(name, vao, nr_indices);
    }
}

void MeshFactory::load_mesh(const std::string& name) {
    VertexBuffer* vb = new VertexBuffer();

    this->mp.read_bz2(AssetManager::get().get_root_directory() + "assets/meshes/" + name + ".mesh", vb->mesh);
    this->ml.load_mesh(&vb->vao, &vb->vbo[0], &vb->nr_indices, vb->mesh);

    this->meshes.emplace(name, *vb);
}

GLuint MeshFactory::get_vao(const std::string& name) {
    const VertexBuffer* buf = this->get_buffer(name);
    if(buf != nullptr) {
        return buf->vao;
    } else {
        this->load_mesh(name);
        return this->get_vao(name);
    }
}

unsigned int MeshFactory::get_nr_indices(const std::string& name) {
    const VertexBuffer* buf = this->get_buffer(name);
    if(buf != nullptr) {
        return buf->nr_indices;
    } else {
        this->load_mesh(name);
        return this->get_nr_indices(name);
    }
}

const MeshFactory::VertexBuffer* MeshFactory::get_buffer(const std::string& name) {
    auto search = this->meshes.find(name);
    if(search != this->meshes.end()) {
        return &search->second;
    } else {
        return nullptr;
    }
}
