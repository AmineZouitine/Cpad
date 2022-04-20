#include "element.hh"

Element::Element(std::string& name, bool is_folder)
    : name_(name), is_folder_(is_folder)
{
}

bool Element::get_is_folder() const
{
    return is_folder_;
}

std::string& Element::get_name() const
{
    return name_;
}