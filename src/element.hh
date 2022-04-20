#pragma once

#include <string>

class Element
{
public:

    Element(std::string& name, bool is_folder = true);
    bool get_is_folder() const;
    std::string& get_name() const;

private:
    bool is_folder_;
    std::string& name_;
};