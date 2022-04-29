#pragma once

#include <map>
#include <string>

#include "folder.hh"
#include "singleton.hh"
#include "scaner.hh"

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
        MOVE,
        CREATE_COMBO,
        COMBO_EXECUTION,
        DISPLAY_HELP,
        QUIT
    };
    ExecutionType execute(std::map<std::string, Folder> &map,
                          std::string &current_folder, Tokens &tokens,
                          std::string &home_path);
private:

    Element&
    get_element_from_index(std::map<std::string, Folder> &map, std::string &current_folder,
                           size_t index);

    std::pair<ExecutionType, std::string> execute_execution(std::map<std::string, Folder> &map,
                          std::string &current_folder, Tokens &tokens,
                          std::string &home_path);

    ExecutionType execute_create_command(std::map<std::string, Folder> &map,
                          std::string &current_folder, Tokens &tokens,
                          std::string &home_path);

    ExecutionType execute_create_folder(std::map<std::string, Folder> &map,
                          std::string &current_folder, Tokens &tokens,
                          std::string &home_path);
    ExecutionType execute_delete(std::map<std::string, Folder> &map,
                          std::string &current_folder, Tokens &tokens,
                          std::string &home_path);
    ExecutionType execute_move(std::map<std::string, Folder> &map,
                          std::string &current_folder, Tokens &tokens,
                          std::string &home_path);
    ExecutionType execute_reset_folder(std::map<std::string, Folder> &map,
                          std::string &current_folder, Tokens &tokens,
                          std::string &home_path);
    ExecutionType execute_reset_all(std::map<std::string, Folder> &map,
                          std::string &current_folder, Tokens &tokens,
                          std::string &home_path);
    ExecutionType execute_create_combo(std::map<std::string, Folder> &map,
                          std::string &current_folder, Tokens &tokens,
                          std::string &home_path);

    void command_launcher(std::map<std::string, Folder> &map,
                          std::string &home_path);
    bool is_template(std::string command);
    void remplace_templates(std::string &command, bool clear);
};