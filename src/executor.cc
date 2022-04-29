#include "executor.hh"

#include <iostream>
#include <memory>
#include <stack>
#include <stdlib.h>
#include <unistd.h>
#include "argument-type.hh"
#include "arguments.hh"


Element&
get_element_from_index(std::map<std::string, Folder> &map, std::string &current_folder,
                       size_t index)
{
    return map[current_folder].get_elements()[index];
}

Executor::ExecutionType
Executor::execute_execution(std::map<std::string, Folder> &map,
                            std::string &current_folder, Tokens &tokens,
                            std::string &home_path)
{
    if (tokens.second[0] == "h")
        return ExecutionType::DISPLAY_HELP;
    else if (tokens.second[0] == "q")
        return ExecutionType::QUIT;

    size_t input_value = std::stoi(tokens.second[1]);
    auto element = get_element_from_index(map, current_folder, input_value);

    if (element.get_is_folder())
        return ExecutionType::MOVE_FOLDER;
    else if (element.get_is_combo())
        return ExecutionType::COMBO_EXECUTION;
    return ExecutionType::COMMAND;
}


Executor::ExecutionType
Executor::execute_create_command(std::map<std::string, Folder> &map,
                                 std::string &current_folder, Tokens &tokens,
                                 std::string &home_path)
{
    Convertor::instance().add_command(map, current_folder, tokens.second[1]);
    return Executor::ExecutionType::CREATE_COMMAND;
}

Executor::ExecutionType
Executor::execute_create_folder(std::map<std::string, Folder> &map,
                                std::string &current_folder, Tokens &tokens,
                                std::string &home_path)
{
    Convertor::instance().add_folder(map, current_folder, tokens.second[1]);
    return Executor::ExecutionType::CREATE_FOLDER;
}

Executor::ExecutionType
Executor::execute_delete(std::map<std::string, Folder> &map,
                         std::string &current_folder, Tokens &tokens,
                         std::string &home_path)
{
    size_t input_value = std::stoi(tokens.second[1]);
    auto element = get_element_from_index(map, current_folder, input_value);
    if (element.get_is_folder())
    {
        Convertor::instance().remove_folder(map, current_folder, element.get_name());
        return Executor::ExecutionType::DELETE_FOLDER;
    }
    else if (element.get_is_combo())
    {
        Convertor::instance().remove_command(map, current_folder, input_value);
        return Executor::ExecutionType::DELETE_COMBO;
    }
    Convertor::instance().remove_command(map, current_folder, input_value);
    return Executor::ExecutionType::DELETE_COMMAND;
}

Executor::ExecutionType
Executor::execute_move(std::map<std::string, Folder> &map,
                       std::string &current_folder, Tokens &tokens,
                       std::string &home_path)
{
    size_t src_index_val = std::stoi(tokens.second[1]) - 1;
    size_t dst_index_val = std::stoi(tokens.second[2]) - 1;
    Convertor::instance().move(map, current_folder, src_index_val, dst_index_val);
    return Executor::ExecutionType::MOVE;
}

Executor::ExecutionType
Executor::execute_reset_folder(std::map<std::string, Folder> &map,
                               std::string &current_folder, Tokens &tokens,
                               std::string &home_path)
{
    
}

Executor::ExecutionType
Executor::execute_reset_all(std::map<std::string, Folder> &map,
                            std::string &current_folder, Tokens &tokens,
                            std::string &home_path)
{}

Executor::ExecutionType
Executor::execute_create_combo(std::map<std::string, Folder> &map,
                               std::string &current_folder, Tokens &tokens,
                               std::string &home_path)
{}


Executor::ExecutionType Executor::execute(std::map<std::string, Folder> &map,
                                          std::string &current_folder,
                                          Tokens &tokens,
                                          std::string &home_path)
{
    ArgumentType::ELEMENT_TYPE element_type =
        ArgumentType::instance().convert_to_element_type(tokens.second[0]);
    
    ExecutionType execution_type = ExecutionType::COMMAND;
    switch (element_type)
    {
    case ArgumentType::ELEMENT_TYPE::EXECUTION:
        execution_type = check_execution(map, tokens, current_folder);
        break;
    case ArgumentType::ELEMENT_TYPE::CREATE_COMMAND:
        execution_type =  check_create_command(tokens);
        break;
    case ArgumentType::ELEMENT_TYPE::CREATE_FOLDER:
        execution_type = check_create_folder(map, tokens);
        break;
    case ArgumentType::ELEMENT_TYPE::DELETE:
        execution_type = check_delete(map, tokens, current_folder);
        break;
    case ArgumentType::ELEMENT_TYPE::MOVE:
        execution_type = check_move(map, tokens, current_folder);
        break;
    case ArgumentType::ELEMENT_TYPE::RESET_FOLDER:
        execution_type = check_reset_folder(map, tokens, current_folder);
        break;
    case ArgumentType::ELEMENT_TYPE::RESET_ALL:
        execution_type = check_reset_all();
        break;
    case ArgumentType::ELEMENT_TYPE::CREATE_COMBO:
        execution_type = check_create_combo(tokens);
        break;
    }
    Convertor::instance().write(map, home_path);
}