#pragma once
#include <sstream>
#include <string>
#include <vector>

#include "argument-type.hh"
#include "singleton.hh"

using Tokens = std::pair<ArgumentType::ELEMENT_TYPE, std::vector<std::string>>;

class Scaner : public Singleton<Scaner>
{
public:
    Tokens scan(std::string &user_input);
    Tokens scan_simple(std::string &user_input);
    Tokens scan_concact(std::string &user_input, size_t start_concact);
    Tokens scan_pattern(std::string &user_input, size_t start_concact,
                        std::string pattern);

private:
    std::string concat_user_input(std::stringstream &stream,
                                  bool is_pattern = false,
                                  std::string pattern = "");
};