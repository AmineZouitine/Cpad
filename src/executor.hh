#pragma once

#include <map>
#include <string>

#include "folder.hh"
#include "singleton.hh"

class Executor : public Singleton<Executor>
{
public:
    enum class ExecutionType
    {
        COMMAND,
        CREATE_COMMAND,
        DELETE_COMMAND,
        CREATE_FOLDER,
        DELETE_FOLDER,
        MOVE_FOLDER,
        RESET_FOLDER,
        RESET_ALL,
        SWAP,
        CREATE_COMBO,
        COMBO,
        NONE
    };
    bool execute(std::string &command_name, Executor::ExecutionType &exec_type,
                 Element &combot_element, bool clear = true);
    void command_launcher(std::map<std::string, Folder> &map,
                          std::string &home_path);
    bool is_template(std::string command);
    void remplace_templates(std::string &command, bool clear);
};