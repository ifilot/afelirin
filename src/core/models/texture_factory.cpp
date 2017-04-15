/**************************************************************************
 *   texture_factory.cpp  --  This file is part of AFELIRIN.              *
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

#include "texture_factory.h"

TextureFactory::TextureFactory() {

}

GLuint TextureFactory::get_texture(const std::string& name){
    auto search = this->textures.find(name);
    if(search != this->textures.end()) {
        return search->second;
    } else {
        this->add_texture(name);
        return this->get_texture(name);
    }
}

void TextureFactory::add_texture(const std::string& name) {
    GLuint texture_id = this->load_texture("assets/png/" + name + ".png");
    this->textures.emplace(name, texture_id);
}

GLuint TextureFactory::load_texture(const std::string& filename) {
    glActiveTexture(GL_TEXTURE1);

    GLuint texture_id;

    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);

    std::vector<uint8_t> pixels;
    png_uint_32 width, height;
    int col, bit_depth;

    PNG::load_image_buffer_from_png(AssetManager::get().get_root_directory() + filename,
                                    pixels,
                                    &width,
                                    &height,
                                    &col,
                                    &bit_depth,
                                    true);  // automatically invert the image

    switch(col) {
        case PNG_COLOR_TYPE_RGB:
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, &pixels[0]);
        break;
        case PNG_COLOR_TYPE_RGB_ALPHA:
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &pixels[0]);
        break;
    }

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glBindTexture(GL_TEXTURE_2D, 0);
    glActiveTexture(GL_TEXTURE0);

    return texture_id;
}

TextureFactory::~TextureFactory() {
    for(auto& item : this->textures) {
        glDeleteTextures(1, &item.second);
    }
}
