/**************************************************************************
 *   texture_factory.h  --  This file is part of AFELIRIN.                *
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

#ifndef _TEXTURE_MANAGER
#define _TEXTURE_MANAGER

#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <unordered_map>

#include "core/asset_manager.h"
#include "util/pngfuncs.h"

class TextureFactory {
private:
    std::unordered_map<std::string, GLuint> textures;

public:
    /**
     * @brief       sprite manager constructor
     *
     * @return      sprite manager instance
     */
    TextureFactory();

    GLuint get_texture(const std::string& name);

    ~TextureFactory();

private:
    void add_texture(const std::string& name);

    GLuint load_texture(const std::string& filename);
};

#endif // _TEXTURE_MANAGER
