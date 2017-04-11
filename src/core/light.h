/**************************************************************************
 *   light.h  --  This file is part of AFELIRIN.                          *
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

#ifndef _LIGHT_H
#define _LIGHT_H

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#include "util/singleton_holder.h"
#include "core/camera.h"

class LightImpl {
private:
    glm::vec3 position;

public:
    LightImpl();

    inline const glm::vec3& get_position() const {
        return this->position;
    }

    void update();

};

typedef SingletonHolder<LightImpl> Light;

#endif //_LIGHT_H
