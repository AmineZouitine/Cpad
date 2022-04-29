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
        MOVE_FOLDER,
        BACK_FOLDER,
        COMBO_EXECUTION,

        CREATE_COMMAND,
        CREATE_FOLDER,
        CREATE_COMBO,
        
        DELETE_COMMAND,
        DELETE_FOLDER,
        DELETE_COMBO,

        RESET_FOLDER,
        RESET_ALL,

        MOVE,
        
        DISPLAY_HELP,
        QUIT
    };
    using executor_result = std::pair<ExecutionType, std::string>;

    executor_result execute(std::map<std::string, Folder> &map,
                          std::string &current_folder, Tokens &tokens,
                          std::string &home_path);
private:

    Element&
    get_element_from_index(std::map<std::string, Folder> &map, std::string &current_folder,
                           size_t index);

    executor_result execute_execution(std::map<std::string, Folder> &map,
                          std::string &current_folder, Tokens &tokens,
                          std::string &home_path);
    

    executor_result execute_create_command(std::map<std::string, Folder> &map,
                          std::string &current_folder, Tokens &tokens,
                          std::string &home_path);

    executor_result execute_create_folder(std::map<std::string, Folder> &map,
                          std::string &current_folder, Tokens &tokens,
                          std::string &home_path);
    executor_result execute_delete(std::map<std::string, Folder> &map,
                          std::string &current_folder, Tokens &tokens,
                          std::string &home_path);
    executor_result execute_move(std::map<std::string, Folder> &map,
                          std::string &current_folder, Tokens &tokens,
                          std::string &home_path);
    executor_result execute_reset_folder(std::map<std::string, Folder> &map,
                          std::string &current_folder, Tokens &tokens,
                          std::string &home_path);
    executor_result execute_reset_all(std::map<std::string, Folder> &map,
                          std::string &current_folder, Tokens &tokens,
                          std::string &home_path);
    executor_result execute_create_combo(std::map<std::string, Folder> &map,
                          std::string &current_folder, Tokens &tokens,
                          std::string &home_path);

    bool is_template(std::string command);
    void remplace_templates(std::string &command, bool clear);
};