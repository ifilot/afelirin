/**************************************************************************
 *   game.cpp  --  This file is part of OBJ2BIT.                          *
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

#include "game.h"

Game::Game(const std::shared_ptr<Camera>& _camera) :
    camera(_camera) {

    // create shader object here
    this->shader = ShaderManager::get().get_shader("model_shader");

    Mesh mesh;
    MeshLoader ml;
    MeshParser mp;

    mp.read_obj(AssetManager::get().get_root_directory() + "assets/meshes/gear.obj", &mesh);
    GLuint vao;
    GLuint vbo[3];
    unsigned int nr_indices;

    ml.load_mesh(&vao, &vbo[0], &nr_indices, &mesh);

    this->entities.emplace_back(glm::vec3(-.70f,-.70f,0), vao, nr_indices);
    this->entities.back().set_color(glm::vec3(1,0,0));
    this->entities.emplace_back(glm::vec3(.70f , .70f,0), vao, nr_indices);
    this->entities.back().set_rotation_speed(-1.0f);
    this->entities.back().set_rotation(M_PI * 2.0 / 24);
    this->entities.back().set_color(glm::vec3(0,1,0));
}

void Game::draw() {
    this->shader->link_shader();

    const glm::mat4 projection = this->camera->get_projection();
    const glm::mat4 view = this->camera->get_view();
    this->shader->set_uniform("view", &view[0][0]);

    for(auto& entity : this->entities) {
        const glm::mat4 trans = glm::translate(entity.get_position());
        const glm::mat4 rot = glm::rotate(entity.get_rotation(), glm::vec3(0,0,1));
        const glm::mat4 scale = glm::mat4(1.0f);
        const glm::mat4 model = trans * rot * scale;
        const glm::mat4 mvp = projection * view * model;

        this->shader->set_uniform("model", &model[0][0]);
        this->shader->set_uniform("mvp", &mvp[0][0]);
        this->shader->set_uniform("color", &entity.get_color());

        entity.draw();
    }

    this->shader->unlink_shader();
}

void Game::update(double dt) {
    for(auto& entity : this->entities) {
        entity.update(dt);
    }
}