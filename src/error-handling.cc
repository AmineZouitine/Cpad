#include "error-handling.hh"

#include <algorithm>
#include <unistd.h>

ErrorHandling::Error ErrorHandling::parsing_int(std::map<std::string, Folder> &map,
                  std::string &current_folder, std::string &input)
{
    int value;
    try
    {
        value = std::stoi(input) - 1;
    }
    catch (...)
    {
        return Error::BIG_INDEX;
    }
    size_t value_t = static_cast<size_t>(value);
    if (value_t >= map[current_folder].get_elements().size() || value < 0)
        return Error::OUT_OF_RANGE;
    return Error::NONE;
}

ErrorHandling::Error ErrorHandling::check_arguments_size(Tokens &tokens)
{
    int arguments_expected =
        ArgumentType::instance().number_arguments_expected(tokens.first);
    int current_size = tokens.second.size();
    if (current_size > arguments_expected)
        return Error::TOO_MUCH_ARGUMENTS;
    else if (current_size < arguments_expected)
        return Error::NEED_MORE_ARGUMENTS;
    return Error::NONE;

}

ErrorHandling::Error ErrorHandling::check_error(std::map<std::string, Folder> &map, Tokens &tokens, std::string& current_folder)
{
    auto error_arguments_size = check_arguments_size(tokens);
    if (error_arguments_size != Error::NONE)
        return error_arguments_size;

    switch (tokens.first)
    {
    case ArgumentType::ELEMENT_TYPE::EXECUTION:
        return check_execution(map, tokens, current_folder);
    case ArgumentType::ELEMENT_TYPE::CREATE_COMMAND:
        return check_create_command(map, tokens, current_folder);
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

    return Error::INVALID_INPUT;
}

ErrorHandling::Error ErrorHandling::check_execution(std::map<std::string, Folder> &map, Tokens &tokens, std::string& current_folder)
{
    std::string argument = tokens.second[0];
    bool is_number = std::all_of(argument.cbegin(), argument.cend(),
                         ::isdigit);
    bool is_valid_command = (current_folder != "." && argument == "b")
        || argument == "h" || argument == "q";

    if (!is_number && !is_valid_command)
        return Error::INVALID_INPUT;
    
    return parsing_int(map, current_folder, argument);
}

ErrorHandling::Error ErrorHandling::check_create_command(std::map<std::string, Folder> &map, Tokens &tokens, std::string& current_folder)
{
    std::string argument = tokens.second[1];
    for (auto &elm : map[current_folder].get_elements())
    {
        if (elm.get_name() == argument && !elm.get_is_folder()
            && !elm.get_is_combo())
        {
            return Error::COMMAND_ERROR_NAME;
        }
    }
    return Error::NONE;
}

ErrorHandling::Error ErrorHandling::check_create_folder(std::map<std::string, Folder> &map, Tokens &tokens)
{
    std::string argument = tokens.second[1];
    if (argument == ".")
        return Error::FOLDER_ERROR_NAME;

    for (auto &folder : map)
    {
        for (auto &element : folder.second.get_elements())
        {
            if (element.get_name() == argument && element.get_is_folder())
                return Error::FOLDER_ERROR_NAME;
        }
    }
    return Error::NONE;
}

ErrorHandling::Error ErrorHandling::check_move(std::map<std::string, Folder> &map, Tokens &tokens, std::string& current_folder)
{
    std::string src_index = tokens.second[1];
    std::string dst_index = tokens.second[2];

    if (!std::all_of(src_index.begin(), src_index.end(), ::isdigit)
        || !std::all_of(dst_index.begin(), dst_index.end(), ::isdigit))
        return Error::INVALID_INPUT;
    

    auto error_parsing_src = parsing_int(map, current_folder, src_index);
    auto error_parsing_dst = parsing_int(map, current_folder, dst_index);

    return error_parsing_src != Error::NONE || error_parsing_dst != Error::NONE
        ? error_parsing_src
        : Error::NONE;
}

ErrorHandling::Error ErrorHandling::check_reset_folder(std::map<std::string, Folder> &map, Tokens &tokens, std::string& current_folder)
{
    std::string argument = tokens.second[1];
    if (!std::all_of(argument.cbegin(), argument.cend(), ::isdigit))
        return Error::INVALID_INPUT;

    return parsing_int(map, current_folder, argument);
}

ErrorHandling::Error ErrorHandling::check_reset_all()
{
    return Error::NONE;
}

ErrorHandling::Error ErrorHandling::check_create_combo(Tokens &tokens)
{
    return tokens.second.size() == 1 ? Error::INVALID_INPUT : Error::NONE;
}

ErrorHandling::Error ErrorHandling::check_delete(std::map<std::string, Folder> &map, Tokens &tokens, std::string& current_folder)
{
    std::string argument = tokens.second[1];
    if (!std::all_of(argument.cbegin(), argument.cend(), ::isdigit))
        return Error::INVALID_INPUT;
    return parsing_int(map, current_folder, argument);
}

