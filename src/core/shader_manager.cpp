/**************************************************************************
 *   shader_manager.cpp  --  This file is part of AFELIRIN.               *
 *                                                                        *
 *   Copyright (C) 2016, Ivo Filot                                        *
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

#include "shader_manager.h"

ShaderManagerImpl::ShaderManagerImpl() {
    this->construct_shaders();
}

void ShaderManagerImpl::construct_shaders() {
    std::shared_ptr<Shader> shader;
    this->shaders.emplace("line_shader", std::make_shared<Shader>("assets/shaders/line"));
    this->shaders.emplace("node_shader", std::make_shared<Shader>("assets/shaders/node"));
    this->shaders.emplace("curve_shader", std::make_shared<Shader>("assets/shaders/curve"));

    shader = this->get_shader("line_shader");
    shader->add_attribute(ShaderAttribute::POSITION, "position");
    shader->add_uniform(ShaderUniform::MAT4, "mvp");
    shader->add_uniform(ShaderUniform::VEC4, "color");
    shader->add_uniform(ShaderUniform::FLOAT, "z");
    shader->bind_uniforms_and_attributes();

    shader = this->get_shader("node_shader");
    shader->add_attribute(ShaderAttribute::POSITION, "position");
    shader->add_uniform(ShaderUniform::MAT4, "mvp");
    shader->add_uniform(ShaderUniform::VEC4, "color");
    shader->add_uniform(ShaderUniform::FLOAT, "z");
    shader->bind_uniforms_and_attributes();

    shader = this->get_shader("curve_shader");
    shader->add_attribute(ShaderAttribute::POSITION, "position");
    shader->add_uniform(ShaderUniform::MAT4, "mvp");
    shader->add_uniform(ShaderUniform::VEC4, "color");
    shader->add_uniform(ShaderUniform::FLOAT, "z");
    shader->add_uniform(ShaderUniform::INT, "num_steps");
    shader->bind_uniforms_and_attributes();
}

const std::shared_ptr<Shader>& ShaderManagerImpl::get_shader(const std::string& shader_name) {
    auto search = this->shaders.find(shader_name);
    if(search != this->shaders.end()) {
        return search->second;
    } else {
        std::cerr << "[ERROR] Could not find " << shader_name << "!" << std::endl;
    }
}
