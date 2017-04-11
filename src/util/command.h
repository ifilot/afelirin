/**************************************************************************
 *   command.h  --  This file is part of AFELIRIN.                        *
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

#ifndef _COMMAND_H
#define _COMMAND_H

class CommandP0 {
public:
    virtual ~CommandP0() {}
    virtual void execute() = 0;
};

template<typename P0>
class CommandP1 {
public:
    virtual ~CommandP1() {}
    virtual void execute(P0) = 0;
};

template<typename P0, typename P1>
class CommandP2 {
public:
    virtual ~CommandP2() {}
    virtual void execute(P0, P1) = 0;
};

#endif //_COMMAND_H
