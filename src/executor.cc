#include "executor.hh"

#include <iostream>
#include <memory>
#include <stack>
#include <stdlib.h>
#include <unistd.h>
#include "argument-type.hh"
#include "arguments.hh"


Element&
get_element_from_index(std::map<std::string, Folder> &map, std::string &key,
                       size_t index)
{
    return map[key].get_elements()[index];
}
    // EXECUTION OR MOVE FOLDER OR COMBO OR DISPLAY HELP OR QUIT
std::pair<Executor::ExecutionType, std::string>
Executor::execute_execution(std::map<std::string, Folder> &map,
                            std::string &current_folder, Tokens &tokens,
                            std::string &home_path)
{
    if (tokens.second[0] == "h")
        return std::pair<ExecutionType, std::string>(ExecutionType::DISPLAY_HELP, "");
    else if (tokens.second[0] == "q")
        return std::pair<ExecutionType, std::string>(ExecutionType::QUIT, "");
    else if (tokens.second[0] == "-cb")
    {}
    else
    {
        size_t input_value = std::stoi(tokens.second[1]);
        auto element = get_element_from_index(map, current_folder, input_value);

        if (element.)
        
    }
    }

    Executor::ExecutionType Executor::execute_create_command(std::map<std::string, Folder> &map,
                          std::string &current_folder, Tokens &tokens,
                          std::string &home_path)
    {

    }

    Executor::ExecutionType Executor::execute_create_folder(std::map<std::string, Folder> &map,
                          std::string &current_folder, Tokens &tokens,
                          std::string &home_path)
    {

    }

    Executor::ExecutionType Executor::execute_delete(std::map<std::string, Folder> &map,
                          std::string &current_folder, Tokens &tokens,
                          std::string &home_path)
    {

    }

    Executor::ExecutionType Executor::execute_move(std::map<std::string, Folder> &map,
                          std::string &current_folder, Tokens &tokens,
                          std::string &home_path)
    {

    }

    Executor::ExecutionType Executor::execute_reset_folder(std::map<std::string, Folder> &map,
                          std::string &current_folder, Tokens &tokens,
                          std::string &home_path)
    {

    }

    Executor::ExecutionType Executor::execute_reset_all(std::map<std::string, Folder> &map,
                          std::string &current_folder, Tokens &tokens,
                          std::string &home_path)
    {

    }

    Executor::ExecutionType Executor::execute_create_combo(std::map<std::string, Folder> &map,
                          std::string &current_folder, Tokens &tokens,
                          std::string &home_path)
    {

    }


Executor::ExecutionType Executor::execute(std::map<std::string, Folder> &map,
                                          std::string &current_folder,
                                          Tokens &tokens,
                                          std::string &home_path)
{
    ArgumentType::ELEMENT_TYPE element_type =
        ArgumentType::instance().convert_to_element_type(tokens.second[0]);
    
    switch (element_type)
    {
    case ArgumentType::ELEMENT_TYPE::EXECUTION:
        return check_execution(map, tokens, current_folder);
    case ArgumentType::ELEMENT_TYPE::CREATE_COMMAND:
        return check_create_command(tokens);
    case ArgumentType::ELEMENT_TYPE::CREATE_FOLDER:
        return check_create_folder(map, tokens);
    case ArgumentType::ELEMENT_TYPE::DELETE:
        return check_delete(map, tokens, current_folder);
    case ArgumentType::ELEMENT_TYPE::MOVE:
        return check_move(map, tokens, current_folder);
    case ArgumentType::ELEMENT_TYPE::RESET_FOLDER:
        return check_reset_folder(map, tokens, current_folder);
    case ArgumentType::ELEMENT_TYPE::RESET_ALL:
        return check_reset_all();
    case ArgumentType::ELEMENT_TYPE::CREATE_COMBO:
        return check_create_combo(tokens);
    }
}