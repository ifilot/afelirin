/**************************************************************************
 *   game.cpp  --  This file is part of AFELIRIN.                         *
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

#include "game.h"

Game::Game(const std::shared_ptr<Camera>& _camera) :
    camera(_camera) {

    // create shader object here
    this->shader = ShaderManager::get().get_shader("model_uv_shader");

    // for(float x = -24.0f; x <=24.0f; x += 8.0f) {
    //     for(float y = -24.0f; y <=24.0f; y += 8.0f) {
    //         this->entities.emplace_back(reinterpret_cast<Entity*>(new Cog(glm::vec3(x, y, 0.0f), this->mf.get_vao("plane"), this->mf.get_nr_indices("plane"))));
    //         this->entities.back()->set_scale(glm::vec3(8.0f, 8.0f, 8.0f));
    //     }
    // }

    this->entities.emplace_back(reinterpret_cast<Entity*>(new Cog(glm::vec3(0.0f, 0.0f, 0.0f), this->mf.get_vao("tank"), this->mf.get_nr_indices("tank"))));
}

void Game::draw() {
    this->shader->link_shader();

    glActiveTexture(GL_TEXTURE1);
    GLuint tid = tf.get_texture("tank_diffuse");
    glBindTexture(GL_TEXTURE_2D, tid);
    const glm::mat4 projection = this->camera->get_projection();
    const glm::mat4 view = this->camera->get_view();
    this->shader->set_uniform("view", &view[0][0]);
    this->shader->set_uniform("tex", 1);

    for(auto& entity : this->entities) {
        const glm::mat4 trans = glm::translate(entity->get_position());
        const glm::mat4 rot = entity->get_rotation();
        const glm::mat4 scale = entity->get_scale();
        const glm::mat4 model = trans * rot * scale;
        const glm::mat4 mvp = projection * view * model;

        this->shader->set_uniform("model", &model[0][0]);
        this->shader->set_uniform("mvp", &mvp[0][0]);

        entity->draw();
    }

    glBindTexture(GL_TEXTURE_2D, 0);
    glActiveTexture(GL_TEXTURE0);
    this->shader->unlink_shader();
}

void Game::update(double dt) {
    for(auto& entity : this->entities) {
        entity->update(dt);
    }
}
