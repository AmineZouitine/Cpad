#include "command.hh"

Command::Command(std::string &command_name, bool is_combo)
    : Element(command_name), is_combo_(is_combo)
{}

bool Command::get_is_combo() const
{
    return is_combo_;
}