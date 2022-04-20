#pragma once

#include <vector>
#include "command.hh"

class Folder
{
public:
    void add_command(std::string& command_name);
    void add_folder(std::string& folder_name);

    friend std::ostream &operator<<(std::ostream &ostr, Folder &folder);

    std::vector<Element>& get_elements();

private:
    std::vector<Element> elements_;
};

std::ostream& operator<<(std::ostream& ostr, const Folder& folder);