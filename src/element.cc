#include "element.hh"

Element::Element(std::string name, bool is_folder)
    : is_folder_(is_folder)
    , name_(name)
{}

bool Element::get_is_folder() const
{
    return is_folder_;
}

std::string &Element::get_name()
{
    return name_;
}