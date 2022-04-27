#include "element.hh"

Element::Element(std::string name, bool is_folder)
    : is_folder_(is_folder)
    , name_(name)
    , is_combo_(false)
{
}

Element::Element(bool is_combo)
    : is_folder_(false)
    , name_("")
    , is_combo_(is_combo)
{
}


bool Element::get_is_folder() const
{
    return is_folder_;
}

std::string &Element::get_name()
{
    return name_;
}

bool Element::get_is_combo() const
{
    return is_combo_;
}

std::vector<Element>& Element::get_combo_elements_()
{
    return combo_elements_;
}