#include "executor.hh"

#include <iostream>
#include <memory>
#include <stack>
#include <stdlib.h>
#include <unistd.h>
#include "argument-type.hh"
#include "convertor.hh"

Element&
Executor::get_element_from_index(std::map<std::string, Folder> &map, std::string &current_folder,
                       size_t index)
{
    return map[current_folder].get_elements()[index];
}

Executor::executor_result
Executor::execute_execution(std::map<std::string, Folder> &map,
                            std::string &current_folder, Tokens &tokens,
                            Element& element_combo)
{
    if (tokens.second[0] == "h")
        return executor_result(ExecutionType::DISPLAY_HELP, "");
    else if (tokens.second[0] == "q")
        return executor_result(ExecutionType::QUIT, "");
    else if (tokens.second[0] == "b")
        return executor_result(ExecutionType::BACK_FOLDER, "");
    size_t input_value = std::stoi(tokens.second[0]);
    auto element = get_element_from_index(map, current_folder, input_value - 1);
    if (element.get_is_folder())
        return executor_result(ExecutionType::MOVE_FOLDER, element.get_name());
    else if (element.get_is_combo())
    {
        element_combo = element;
        return executor_result(ExecutionType::COMBO_EXECUTION, element.get_name());
    }
    return executor_result(ExecutionType::COMMAND, element.get_name());
}


Executor::executor_result
Executor::execute_create_command(std::map<std::string, Folder> &map,
                                 std::string &current_folder, Tokens &tokens)
{
    Convertor::instance().add_command(map, current_folder, tokens.second[1]);
    return executor_result(Executor::ExecutionType::CREATE_COMMAND, tokens.second[1]);
}

Executor::executor_result
Executor::execute_create_folder(std::map<std::string, Folder> &map,
                                std::string &current_folder, Tokens &tokens)
{
    Convertor::instance().add_folder(map, current_folder, tokens.second[1]);
    return executor_result(Executor::ExecutionType::CREATE_FOLDER, tokens.second[1]);
}

Executor::executor_result
Executor::execute_delete(std::map<std::string, Folder> &map,
                         std::string &current_folder, Tokens &tokens)
{
    size_t input_value = std::stoi(tokens.second[1]);
    auto element = get_element_from_index(map, current_folder, input_value - 1);
    ExecutionType execution;
    if (element.get_is_folder())
    {
        Convertor::instance().remove_folder(map, current_folder, element.get_name());
        execution = Executor::ExecutionType::DELETE_FOLDER;
    }
    else if (element.get_is_combo())
    {
        Convertor::instance().remove_command(map, current_folder, input_value);
        execution = Executor::ExecutionType::DELETE_COMBO;
    }
    else
    {
        Convertor::instance().remove_command(map, current_folder, input_value);
        execution = Executor::ExecutionType::DELETE_COMMAND;
    }
    return executor_result(execution, element.get_name());
}

Executor::executor_result
Executor::execute_move(std::map<std::string, Folder> &map,
                       std::string &current_folder, Tokens &tokens)
{
    size_t src_index_val = std::stoi(tokens.second[1]) - 1;
    size_t dst_index_val = std::stoi(tokens.second[2]) - 1;
    Convertor::instance().move(map, current_folder, src_index_val, dst_index_val);
    return executor_result(Executor::ExecutionType::MOVE, tokens.second[1] + " " + tokens.second[2]);
}

Executor::executor_result
Executor::execute_reset_folder(std::map<std::string, Folder> &map,
                               std::string &current_folder, Tokens &tokens)
{
    size_t value = std::stoi(tokens.second[1]) - 1;
    auto element = get_element_from_index(map, current_folder, value);
    Convertor::instance().reset_folder(map, element.get_name());
    return executor_result(Executor::ExecutionType::RESET_FOLDER, tokens.second[1]);
}

Executor::executor_result
Executor::execute_reset_all(std::map<std::string, Folder> &map)
{
    Convertor::instance().reset_all(map);
    return executor_result(Executor::ExecutionType::RESET_ALL, "");
}

Executor::executor_result
Executor::execute_create_combo(std::map<std::string, Folder> &map,
                               std::string &current_folder, Tokens &tokens)
{
    std::string combo_name;
    auto token_name = tokens.second[1];
    size_t token_size = token_name.size();

    if (token_name.size() >= 3 && token_name[0] == '{'
        && token_name[token_size - 1] == '}')
        combo_name = token_name.substr(1, token_size - 2);
    
    Element combo;
    if (!combo_name.empty())
        combo.set_name(combo_name);
    
    size_t i = combo_name.empty() ? 1 : 2;
    for (; i < tokens.second.size(); i++) 
        combo.get_combo_elements_().push_back(Element(tokens.second[i], false));

    Convertor::instance().combo(map, current_folder, combo);
    return executor_result(Executor::ExecutionType::CREATE_COMBO, combo_name);
}


Executor::executor_result Executor::execute(std::map<std::string, Folder> &map,
                                          std::string &current_folder,
                                          Tokens &tokens,
                                          std::string& home_path,
                                          Element& element)
{
    ArgumentType::ELEMENT_TYPE element_type =
        ArgumentType::instance().convert_to_element_type(tokens.second[0]);
    
    executor_result execution_type;
    switch (element_type)
    {
    case ArgumentType::ELEMENT_TYPE::EXECUTION:
        execution_type = execute_execution(map, current_folder, tokens, element);
        break;
    case ArgumentType::ELEMENT_TYPE::CREATE_COMMAND:
        execution_type = execute_create_command(map, current_folder, tokens);
        break;
    case ArgumentType::ELEMENT_TYPE::CREATE_FOLDER:
        execution_type = execute_create_folder(map, current_folder, tokens);
        break;
    case ArgumentType::ELEMENT_TYPE::DELETE:
        execution_type = execute_delete(map, current_folder, tokens);
        break;
    case ArgumentType::ELEMENT_TYPE::MOVE:
        execution_type = execute_move(map, current_folder, tokens);
        break;
    case ArgumentType::ELEMENT_TYPE::RESET_FOLDER:
        execution_type = execute_reset_folder(map, current_folder, tokens);
        break;
    case ArgumentType::ELEMENT_TYPE::RESET_ALL:
        execution_type = execute_reset_all(map);
        break;
    case ArgumentType::ELEMENT_TYPE::CREATE_COMBO:
        execution_type = execute_create_combo(map, current_folder, tokens);
        break;
    }
    Convertor::instance().write(map, home_path);
    return execution_type;
}