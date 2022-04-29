#include "scaner.hh"

Tokens Scaner::scan_concact(std::string& user_input, size_t start_concact)
{
    std::vector<std::string> tokens;
    ArgumentType::ELEMENT_TYPE element_type;

    std::stringstream stream(user_input);
    std::string current_token;

    for (size_t i = 0; i < start_concact && stream >> current_token; i++)
        tokens.push_back(current_token);

    while (stream >> current_token) 
        tokens.push_back(concat_user_input(stream));
    
    element_type = ArgumentType::instance().convert_to_element_type(tokens[0]);

    return Tokens{element_type, tokens};
}

Tokens Scaner::scan(std::string &user_input)
{
    std::vector<std::string> tokens;
    ArgumentType::ELEMENT_TYPE element_type;

    std::stringstream stream(user_input);
    std::string current_token;

    while (stream >> current_token)
        tokens.push_back(current_token);

    element_type = ArgumentType::instance().convert_to_element_type(tokens[0]);

    return Tokens{element_type, tokens};
}

Tokens Scaner::scan_pattern(std::string &user_input,
                                       size_t start_concact,
                                       std::string pattern)
{
    std::vector<std::string> tokens;
    ArgumentType::ELEMENT_TYPE element_type;
    
    std::stringstream stream(user_input);
    std::string current_token;

    for (size_t i = 0; i < start_concact && stream >> current_token; i++)
        tokens.push_back(current_token);

    while (stream >> current_token) 
        tokens.push_back(concat_user_input(stream, true, pattern));
    
    element_type = ArgumentType::instance().convert_to_element_type(tokens[0]);

    return Tokens{element_type, tokens};
    
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
