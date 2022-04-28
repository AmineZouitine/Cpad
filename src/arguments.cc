
#include "arguments.hh"

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>

#include "convertor.hh"
#include "executor.hh"

void error_handling(std::map<std::string, Folder> &map, std::string &key,
                    std::string &user_input, Executor::ExecutionType &exec_type)
{
    exec_type = Executor::ExecutionType::NONE;
    std::stringstream ss(user_input);
    std::string token;
    std::string cmd_argument;
    ss >> token;

    if (token == "-ac")
    {
        concat_argument(ss, token, cmd_argument);
        if (cmd_argument.empty())
        {
            exec_type = Executor::ExecutionType::EMPTY_NAME;
            return;
        }
        for (auto &elm : map[key].get_elements())
        {
            if (elm.get_name() == cmd_argument && !elm.get_is_folder()
                && !elm.get_is_combo())
            {
                exec_type = Executor::ExecutionType::COMMAND_ERROR_NAME;
                return;
            }
        }
    }
    else if (token == "-af")
    {
        concat_argument(ss, token, cmd_argument);
        if (cmd_argument.empty())
        {
            exec_type = Executor::ExecutionType::EMPTY_NAME;
            return;
        }
        if (cmd_argument == ".")
        {
            exec_type = Executor::ExecutionType::FOLDER_ERROR_NAME;
            return;
        }
        for (auto &folder : map)
        {
            for (auto &element : folder.second.get_elements())
            {
                if (element.get_name() == cmd_argument
                    && element.get_is_folder())
                {
                    exec_type = Executor::ExecutionType::FOLDER_ERROR_NAME;
                    return;
                }
            }
        }
    }
    else if (token == "-de")
    {
        std::string input_number;
        ss >> input_number;
        if (input_number.empty())
        {
            exec_type = Executor::ExecutionType::DELETE_EMPTY_NAME;
            return;
        }
        if (!std::all_of(input_number.cbegin(), input_number.cend(), ::isdigit))
        {
            exec_type = Executor::ExecutionType::NO_INT_INDEX;
            return;
        }
        int value;
        try
        {
            value = std::stoi(input_number) - 1;
        }
        catch (...)
        {
            exec_type = Executor::ExecutionType::BIG_INDEX;
            return;
        }
        if ((size_t)value >= map[key].get_elements().size() || value < 0)
        {
            exec_type = Executor::ExecutionType::OUT_OF_RANGE;
            return;
        }
    }
    else if (token == "-rf")
    {
        std::string input_number;
        ss >> input_number;
        if (input_number.empty())
        {
            exec_type = Executor::ExecutionType::RESET_EMPTY_NAME;
            return;
        }
        if (!std::all_of(input_number.cbegin(), input_number.cend(), ::isdigit))
        {
            exec_type = Executor::ExecutionType::NO_INT_INDEX;
            return;
        }
        int value;
        try
        {
            value = std::stoi(input_number) - 1;
        }
        catch (...)
        {
            exec_type = Executor::ExecutionType::BIG_INDEX;
            return;
        }
        if ((size_t)value >= map[key].get_elements().size() || value < 0)
        {
            exec_type = Executor::ExecutionType::OUT_OF_RANGE;
            return;
        }
    }
    else if (token == "-ra")
    {}
    else if (token == "-mv")
    {
        std::string src_index;
        std::string dst_index;
        ss >> src_index;
        ss >> dst_index;
        int src_index_val;
        int dst_index_val;
        if (src_index.empty() || dst_index.empty())
        {
            exec_type = Executor::ExecutionType::EMPTY_INDEX;
            return;
        }
        else if (!std::all_of(src_index.begin(), src_index.end(), ::isdigit)
                 || !std::all_of(dst_index.begin(), dst_index.end(), ::isdigit))
        {
            exec_type = Executor::ExecutionType::NO_INT_INDEX;
            return;
        }
        try
        {
            src_index_val = std::stoi(src_index) - 1;
            dst_index_val = std::stoi(dst_index) - 1;
        }
        catch (...)
        {
            exec_type = Executor::ExecutionType::BIG_INDEX;
            return;
        }
        if ((size_t)src_index_val >= map[key].get_elements().size()
            || (size_t)dst_index_val >= map[key].get_elements().size()
            || dst_index_val < 0 || src_index_val < 0)
        {
            exec_type = Executor::ExecutionType::OUT_OF_RANGE;
            return;
        }
        bool src_wrong_index = false;
        bool dst_wrong_index = false;
        for (auto &elm : map[key].get_elements())
        {
            if (elm.get_name()
                == get_element_from_index(map, key, src_index_val).first)
                src_wrong_index = true;
            if (elm.get_name()
                == get_element_from_index(map, key, dst_index_val).first)
                dst_wrong_index = true;
        }
        if (!src_wrong_index || !dst_wrong_index)
        {
            exec_type = Executor::ExecutionType::SWAP_WRONG_INDEX;
            return;
        }
    }
    else if (token == "-cb")
    {
        concat_argument(ss, token, cmd_argument);
        if (cmd_argument.empty())
        {
            exec_type = Executor::ExecutionType::EMPTY_NAME;
            return;
        }
    }
}

std::pair<std::string, bool>
get_element_from_index(std::map<std::string, Folder> &map, std::string &key,
                       size_t index)
{
    auto current = map[key].get_elements()[index];
    std::pair<std::string, bool> result{ current.get_name(),
                                         current.get_is_folder() };
    return result;
}

bool is_command(std::string &cmd)
{
    return cmd == "-ac" || cmd == "-af" || cmd == "-de" || cmd == "-rf"
        || cmd == "-ra" || cmd == "-mv" || cmd == "-cb";
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

void parse_arg(std::string &arg, std::map<std::string, Folder> &map,
               std::string &key, std::string &home_path,
               Executor::ExecutionType &exec_type)
{
    error_handling(map, key, arg, exec_type);
    if (exec_type != Executor::ExecutionType::NONE)
        return;

    std::stringstream ss(arg);
    std::string token;
    std::string cmd_argument;
    ss >> token;
    if (token == "-ac")
    {
        concat_argument(ss, token, cmd_argument);
        arg = cmd_argument;
        exec_type = Executor::ExecutionType::CREATE_COMMAND;
        Convertor::instance().add_command(map, key, cmd_argument);
    }
    else if (token == "-af")
    {
        concat_argument(ss, token, cmd_argument);
        arg = cmd_argument;
        exec_type = Executor::ExecutionType::CREATE_FOLDER;
        Convertor::instance().add_folder(map, key, cmd_argument);
    }
    else if (token == "-de")
    {
        std::string input_number;
        ss >> input_number;
        size_t value = std::stoi(input_number) - 1;
        auto element = get_element_from_index(map, key, value);
        arg = element.first;
        if (element.second)
        {
            exec_type = Executor::ExecutionType::DELETE_FOLDER;
            Convertor::instance().remove_folder(map, key, element.first);
        }
        else
        {
            exec_type = Executor::ExecutionType::DELETE_COMMAND;
            Convertor::instance().remove_command(map, key, value + 1);
        }
    }
    else if (token == "-rf")
    {
        std::string input_number;
        ss >> input_number;
        size_t value = std::stoi(input_number) - 1;
        auto element = get_element_from_index(map, key, value);
        arg = element.first;
        exec_type = Executor::ExecutionType::RESET_FOLDER;
        Convertor::instance().reset_folder(map, element.first);
    }
    else if (token == "-ra")
    {
        exec_type = Executor::ExecutionType::RESET_ALL;
        Convertor::instance().reset_all(map);
    }
    else if (token == "-mv")
    {
        std::string src_index;
        std::string dst_index;
        ss >> src_index;
        ss >> dst_index;
        size_t src_index_val = std::stoi(src_index) - 1;
        size_t dst_index_val = std::stoi(dst_index) - 1;
        exec_type = Executor::ExecutionType::SWAP;
        Convertor::instance().move(map, key, src_index_val, dst_index_val);
    }
    else if (token == "-cb")
    {
        std::stringstream tmp_ss(arg);
        tmp_ss >> token;
        std::string command_name;
        size_t iteration = 0;

        while (tmp_ss >> token)
        {
            if (iteration == 0 && token[0] != '{')
            {
                command_name = "";
                break;
            }
            command_name.empty() ? command_name += token
                                 : command_name += ' ' + token;
            if (token[token.size() - 1] == '}')
                break;
            iteration++;
        }
        if (command_name.size() >= 2 && command_name[0] == '{'
            && command_name[command_name.size() - 1] == '}')
        {
            command_name = command_name.substr(1, command_name.size() - 2);
            ss >> token;
        }

        Element combo;
        if (!command_name.empty())
            combo.set_name(command_name);
        std::string current_command;

        while (ss >> token)
        {
            if (token == "[cb]")
            {
                combo.get_combo_elements_().push_back(
                    Element(current_command, false));
                current_command = "";
                continue;
            }
            current_command.empty() ? current_command += token
                                    : current_command += ' ' + token;
        }
        if (!current_command.empty())
            combo.get_combo_elements_().push_back(
                Element(current_command, false));
        Convertor::instance().combo(map, key, combo);
        exec_type = Executor::ExecutionType::COMBO;
    }
    Convertor::instance().write(map, home_path);
}