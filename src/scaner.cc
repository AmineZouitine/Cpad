#include "scaner.hh"

#include <iostream>

Tokens Scaner::scan(std::string &user_input)
{
    std::string token;
    std::stringstream stream(user_input);
    stream >> token;
    ArgumentType::ELEMENT_TYPE element_type =
        ArgumentType::instance().convert_to_element_type(token);

    switch (element_type)
    {
    case ArgumentType::ELEMENT_TYPE::CREATE_FOLDER:
    case ArgumentType::ELEMENT_TYPE::CREATE_COMMAND:
        return scan_concact(user_input, 1);
    case ArgumentType::ELEMENT_TYPE::MOVE:
    case ArgumentType::ELEMENT_TYPE::DELETE:
    case ArgumentType::ELEMENT_TYPE::RESET_FOLDER:
    case ArgumentType::ELEMENT_TYPE::EXECUTION:
    case ArgumentType::ELEMENT_TYPE::RESET_ALL:
        return scan_simple(user_input);
    case ArgumentType::ELEMENT_TYPE::CREATE_COMBO:
        stream >> token;
        size_t start_concact = 1;
        if (token.size() >= 3 && token[0] == '{'
            && token[token.size() - 1] == '}')
            start_concact++;
        return scan_pattern(user_input, start_concact, "[cb]");
    }
    return Tokens();
}

Tokens Scaner::scan_concact(std::string &user_input, size_t start_concact)
{
    std::vector<std::string> tokens;
    ArgumentType::ELEMENT_TYPE element_type;

    std::stringstream stream(user_input);
    std::string current_token;

    for (size_t i = 0; i < start_concact && stream >> current_token; i++)
        if (!current_token.empty())
            tokens.push_back(current_token);

    current_token = concat_user_input(stream);
    if (!current_token.empty())
        tokens.push_back(current_token);

    element_type = ArgumentType::instance().convert_to_element_type(tokens[0]);

    return Tokens{ element_type, tokens };
}

Tokens Scaner::scan_simple(std::string &user_input)
{
    std::vector<std::string> tokens;
    ArgumentType::ELEMENT_TYPE element_type;

    std::stringstream stream(user_input);
    std::string current_token;
    while (stream >> current_token)
        if (!current_token.empty())
            tokens.push_back(current_token);

    element_type = ArgumentType::instance().convert_to_element_type(tokens[0]);

    return Tokens{ element_type, tokens };
}

Tokens Scaner::scan_pattern(std::string &user_input, size_t start_concact,
                            std::string pattern)
{
    std::vector<std::string> tokens;
    ArgumentType::ELEMENT_TYPE element_type;

    std::stringstream stream(user_input);
    std::string current_token;

    for (size_t i = 0; i < start_concact && stream >> current_token; i++)
        if (!current_token.empty())
            tokens.push_back(current_token);

    std::string current_element;
    while (
        !(current_element = concat_user_input(stream, true, pattern)).empty())
        tokens.push_back(current_element);

    element_type = ArgumentType::instance().convert_to_element_type(tokens[0]);

    return Tokens{ element_type, tokens };
}

std::string Scaner::concat_user_input(std::stringstream &stream,
                                      bool is_pattern, std::string pattern)
{
    std::string concact_result;
    std::string token;
    while (stream >> token)
    {
        if (is_pattern && token == pattern)
            break;
        concact_result.empty() ? concact_result += token
                               : concact_result += ' ' + token;
    }
    return concact_result;
}
