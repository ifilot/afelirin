/**************************************************************************
 *   shader_manager.h  --  This file is part of AFELIRIN.                 *
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

#ifndef _SHADER_MANAGER_H
#define _SHADER_MANAGER_H

#include "shader.h"

class ShaderManagerImpl {
private:
    std::unordered_map<std::string, std::shared_ptr<Shader> > shaders;

public:
    /**
     * @brief       shader_manager constructor
     *
     * @return      shader_manager instance
     */
    ShaderManagerImpl();

    const std::shared_ptr<Shader>& get_shader(const std::string& shader_name);

private:
    void construct_shaders();
};

typedef SingletonHolder<ShaderManagerImpl> ShaderManager;

#endif //_SHADER_MANAGER_H
