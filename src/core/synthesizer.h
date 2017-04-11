/**************************************************************************
 *   synthesizer.h  --  This file is part of AFELIRIN.                    *
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

#ifndef _SYNTHESIZER_H
#define _SYNTHESIZER_H

#include "core/asset_manager.h"

#include <iostream>
#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>
#include <cstring>
#include <string>
#include <vector>
#include <vorbis/codec.h>
#include <vorbis/vorbisfile.h>

#include "util/singleton_holder.h"

/**
 * @class SynthesizerImpl class
 * @brief class that manages sound play
 */
class SynthesizerImpl {
private:
    ALCdevice* device;              //!< reference to sound device
    std::vector<ALuint> buffers;    //!< vector holding sound buffers
    std::vector<ALuint> sources;    //!< vector holding sound sources

public:
    SynthesizerImpl();

    inline void play(unsigned int sound_id) {
        alSourcePlay(this->sources[sound_id]);
    }

    inline void set_gain(unsigned int sound_id, float gain) {
        alSourcef (this->sources[sound_id], AL_GAIN, gain);
    }

    ~SynthesizerImpl();

private:
    void load_wav_file(const std::string& filename);

    void load_ogg_file(const std::string filename);

    void set_listener();

    void delete_buffers_and_sources();

    void bind_source_to_last_buffer();
};

#endif //_SYNTHESIZER_H
