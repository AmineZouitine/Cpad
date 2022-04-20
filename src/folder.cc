#include "folder.hh"

void Folder::add_command(std::string &command_name)
{
    elements_.push_back(Command(command_name));
}

void Folder::add_folder(std::string &folder_name)
{
    elements_.push_back(Element(folder_name, true));
}

std::vector<Element>& Folder::get_elements()
{
    return elements_;
}