
#include "arguments.hh"

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>

#include "convertor.hh"
#include "executor.hh"

bool is_command(std::string &cmd)
{
    return cmd == "-ac" || cmd == "-af" || cmd == "-rc" || cmd == "-rf";
}

void concat_argument(std::stringstream &ss, std::string token,
                     std::string &cmd_argument)
{
    size_t count = 0;
    while (ss >> token)
    {
        if (count != 0)
            cmd_argument += ' ';
        cmd_argument += token;
        count++;
    }
}

void parse_cmd(int argc, char **argv, std::map<std::string, Folder> &map,
               std::string &path, std::string &folder)
{
    std::string command;
    for (int i = 2; i < argc; i++)
        command += argv[i];
    Convertor::instance().add_command(map, folder, command);
    Convertor::instance().write(map, path);
}

void parse_folder(int argc, char **argv, std::map<std::string, Folder> &map,
                  std::string &path, std::string &folder)
{
    std::string new_folder;
    for (int i = 2; i < argc; i++)
        new_folder += argv[i];
    Convertor::instance().add_folder(map, folder, new_folder);
    Convertor::instance().write(map, path);
}

void parse_arg(std::string &arg, std::map<std::string, Folder> &map,
               std::string &key, std::string &home_path,
               Executor::ExecutionType &exec_type)
{
    std::stringstream ss(arg);
    std::string token;
    std::string cmd_argument;
    ss >> token;
    concat_argument(ss, token, cmd_argument);
    arg = cmd_argument;
    if (token == "-ac")
    {
        exec_type = Executor::ExecutionType::CREATE_COMMAND;
        Convertor::instance().add_command(map, key, cmd_argument);
    }
    else if (token == "-af")
    {
        exec_type = Executor::ExecutionType::CREATE_FOLDER;
        Convertor::instance().add_folder(map, key, cmd_argument);
    }
    Convertor::instance().write(map, home_path);
}