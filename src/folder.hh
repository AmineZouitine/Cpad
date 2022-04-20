#pragma once

#include <vector>
#include "command.hh"

class Folder
{
public:
    std::vector<Element>& get_elements();
private:
    std::vector<Element> elements_;
};