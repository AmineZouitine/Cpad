#include "executor.hh"

#include <iostream>
#include <memory>
#include <stack>
#include <stdlib.h>
#include <unistd.h>
#include "argument-type.hh"
#include "convertor.hh"

Element&
get_element_from_index(std::map<std::string, Folder> &map, std::string &current_folder,
                       size_t index)
{
    return map[current_folder].get_elements()[index];
}

Executor::executor_result
Executor::execute_execution(std::map<std::string, Folder> &map,
                            std::string &current_folder, Tokens &tokens,
                            std::string &home_path)
{
    if (tokens.second[0] == "h")
        return executor_result(ExecutionType::DISPLAY_HELP, "");
    else if (tokens.second[0] == "q")
        return executor_result(ExecutionType::QUIT, "");
    else if (tokens.second[0] == "b")
        return executor_result(ExecutionType::BACK_FOLDER, current_folder);
    size_t input_value = std::stoi(tokens.second[1]);
    auto element = get_element_from_index(map, current_folder, input_value);

    if (element.get_is_folder())
        return ExecutionType::MOVE_FOLDER;
    else if (element.get_is_combo())
        return ExecutionType::COMBO_EXECUTION;
    return ExecutionType::COMMAND;
}


Executor::executor_result
Executor::execute_create_command(std::map<std::string, Folder> &map,
                                 std::string &current_folder, Tokens &tokens,
                                 std::string &home_path)
{
    Convertor::instance().add_command(map, current_folder, tokens.second[1]);
    return Executor::executor_result::CREATE_COMMAND;
}

Executor::executor_result
Executor::execute_create_folder(std::map<std::string, Folder> &map,
                                std::string &current_folder, Tokens &tokens,
                                std::string &home_path)
{
    Convertor::instance().add_folder(map, current_folder, tokens.second[1]);
    return Executor::executor_result::CREATE_FOLDER;
}

Executor::executor_result
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

Executor::executor_result
Executor::execute_move(std::map<std::string, Folder> &map,
                       std::string &current_folder, Tokens &tokens,
                       std::string &home_path)
{
    size_t src_index_val = std::stoi(tokens.second[1]) - 1;
    size_t dst_index_val = std::stoi(tokens.second[2]) - 1;
    Convertor::instance().move(map, current_folder, src_index_val, dst_index_val);
    return Executor::ExecutionType::MOVE;
}

Executor::executor_result
Executor::execute_reset_folder(std::map<std::string, Folder> &map,
                               std::string &current_folder, Tokens &tokens,
                               std::string &home_path)
{
    size_t value = std::stoi(tokens.second[1]) - 1;
    auto element = get_element_from_index(map, current_folder, value);
    Convertor::instance().reset_folder(map, element.get_name());
    return Executor::ExecutionType::RESET_FOLDER;
}

Executor::executor_result
Executor::execute_reset_all(std::map<std::string, Folder> &map,
                            std::string &current_folder, Tokens &tokens,
                            std::string &home_path)
{
    Convertor::instance().reset_all(map);
    return Executor::ExecutionType::RESET_ALL;
}

Executor::executor_result
Executor::execute_create_combo(std::map<std::string, Folder> &map,
                               std::string &current_folder, Tokens &tokens,
                               std::string &home_path)
{
    std::string combo_name;
    auto token_name = tokens.second[2];
    size_t token_size = token_name.size();

    if (token_name.size() >= 3 && token_name[0] == '{'
        && token_name[token_size - 1] == '}')
        combo_name = token_name.substr(1, token_size - 2);
    
    Element combo;
    if (!combo_name.empty())
        combo.set_name(combo_name);
    
    size_t i = combo_name.empty() ? 1 : 2;
    for (i; i < tokens.second.size(); i++) 
        combo.get_combo_elements_().push_back(Element(tokens.second[i], false));

    Convertor::instance().combo(map, current_folder, combo);
    return Executor::ExecutionType::CREATE_COMBO;
}


Executor::executor_result Executor::execute(std::map<std::string, Folder> &map,
                                          std::string &current_folder,
                                          Tokens &tokens,
                                          std::string &home_path)
{
    ArgumentType::ELEMENT_TYPE element_type =
        ArgumentType::instance().convert_to_element_type(tokens.second[0]);
    
    executor_result execution_type;
    switch (element_type)
    {
    case ArgumentType::ELEMENT_TYPE::EXECUTION:
        execution_type = execute_execution(map, current_folder, tokens, home_path);
        break;
    case ArgumentType::ELEMENT_TYPE::CREATE_COMMAND:
        execution_type = execute_execution(map, current_folder, tokens, home_path);
        break;
    case ArgumentType::ELEMENT_TYPE::CREATE_FOLDER:
        execution_type = execute_create_folder(map, current_folder, tokens, home_path);
        break;
    case ArgumentType::ELEMENT_TYPE::DELETE:
        execution_type = execute_delete(map, current_folder, tokens, home_path);
        break;
    case ArgumentType::ELEMENT_TYPE::MOVE:
        execution_type = execute_move(map, current_folder, tokens, home_path);
        break;
    case ArgumentType::ELEMENT_TYPE::RESET_FOLDER:
        execution_type = execute_reset_folder(map, current_folder, tokens, home_path);
        break;
    case ArgumentType::ELEMENT_TYPE::RESET_ALL:
        execution_type = execute_reset_all(map, current_folder, tokens, home_path);
        break;
    case ArgumentType::ELEMENT_TYPE::CREATE_COMBO:
        execution_type = execute_create_combo(map, current_folder, tokens, home_path);
        break;
    }
    Convertor::instance().write(map, home_path);
}