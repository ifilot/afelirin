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

#include <unordered_map>
#include <string>
#include <stdexcept>

class Command {
protected:
    std::unordered_map<std::string, boost::any> params;

public:
    virtual ~Command() {}
    virtual void execute() = 0;

    Command* set_param(const std::string& name, const boost::any& value) {
        auto search = this->params.find(name);
        if(search != this->params.end()) {
            search->second = value;
        } else {
            params.emplace(name, value);
        }

        return this;
    }

    template<typename T>
    T get_param(const std::string& name) {
        return boost::any_cast<T>(this->get_value(name));
    }

protected:
    const boost::any& get_value(const std::string& name) {
        auto search = this->params.find(name);
        if(search != this->params.end()) {
            return search->second;
        } else {
            throw std::logic_error("Unknown parameter");
        }
    }
};

class CommandHolder {
private:
    std::unique_ptr<Command> cmd;

public:
    CommandHolder(Command* _cmd) : cmd(_cmd) {}

    inline void execute() {
        this->cmd->execute();
    }

    inline CommandHolder* set_param(const std::string& name, const boost::any& value) {
        this->cmd->set_param(name, value);
        return this;
    }

    inline Command* get() {
        return this->cmd.get();
    }
};

class CommandController {
private:
    std::unordered_map<std::string, CommandHolder> cmds;

public:
    CommandController() {}

    void add_cmd(const std::string& name, Command* _cmd) {
        this->cmds.emplace(name, _cmd);
    }

    void execute_cmd(const std::string& name) {
        this->get_cmd(name)->execute();
    }

    CommandHolder* get_cmd(const std::string& name) {
        auto search = this->cmds.find(name);
        if(search != this->cmds.end()) {
            return &search->second;
        } else {
            throw std::logic_error("Unknown command");
        }
    }

};

#endif //_COMMAND_H
