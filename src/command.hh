#pragma once

#include <string>

#include "element.hh"

class Command : public Element
{
public:
    Command(std::string &command_name, bool is_combo = false);
    bool get_is_combo() const;
private:
    bool is_combo_;
};