#pragma once

#include <string>

#include "element.hh"

class Command : public Element
{
public:
    Command(std::string &command_name);
    void execute_command() const;
};