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
        FOLDER,
        CREATE_COMMAND,
        DELETE_COMMAND,
        CREATE_FOLDER,
        DELETE_FOLDER,
        MOVE_FOLDER,
        RESET_FOLDER,
        RESET_ALL,
        ERROR_NAME,
        NONE
    };
    bool execute(std::string &command_name, Executor::ExecutionType &exec_type);
    void command_launcher(std::map<std::string, Folder> &map,
                          std::string &home_path);
};