/**************************************************************************
 *   game.h  --  This file is part of AFELIRIN.                           *
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

#ifndef _GAME_H
#define _GAME_H

#include <memory>
#include <list>

#include "core/shader.h"
#include "app/cog.h"
#include "app/cube_inward.h"

#include "core/shader_manager.h"
#include "core/models/mesh_factory.h"
#include "core/models/texture_factory.h"

class Game {
private:
    std::shared_ptr<Shader> shader;
    std::shared_ptr<Camera> camera;
    MeshFactory mf;
    TextureFactory tf;

    std::vector<std::unique_ptr<Entity> > entities;


public:
    Game(const std::shared_ptr<Camera>& _camera);

    void draw();

    void update(double dt);

    ~Game() {};

private:

};

#endif //_GAME_H
