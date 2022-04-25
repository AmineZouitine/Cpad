#pragma once

#include <string>
#include <map>

#include "singleton.hh"
#include "folder.hh"

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
        NONE
    };
    bool execute(std::string &command_name, Executor::ExecutionType& exec_type);
    void command_launcher(std::map<std::string, Folder> &map,
                          std::string &home_path);
};