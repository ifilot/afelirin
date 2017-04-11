/**************************************************************************
 *   singleton_holder.h  --  This file is part of AFELIRIN.               *
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

#ifndef _SINGLETON_HOLDER_H
#define _SINGLETON_HOLDER_H

#include <stdexcept>

template <class Singleton>
class SingletonHolder {
private:
    static Singleton* instance;     //!< pointer to Singleton class
    static bool flag_destroyed;     //!< boolean whether singleton has been destroyed

public:
    static Singleton& get() {
        if(!instance) {
            if(flag_destroyed) {
                throw std::runtime_error("Dead reference detected");
            }

            // create the singleton object
            create_singleton();
        }
        return *instance;
    }

private:
    virtual ~SingletonHolder() {
        this->instance = 0;
        this->flag_destroyed = true;
    }

    SingletonHolder();

    static void create_singleton() {
        static Singleton the_instance;
        instance = &the_instance;
    }

    SingletonHolder(SingletonHolder const&) = delete;
    void operator=(SingletonHolder const&)  = delete;
};

template <class Singleton>
bool SingletonHolder<Singleton>::flag_destroyed = false;

template <class Singleton>
Singleton* SingletonHolder<Singleton>::instance = 0;

#endif //_SINGLETON_HOLDER_H
