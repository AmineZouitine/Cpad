#include "folder.hh"

Folder::Folder(std::vector<Element> &elements)
    : elements_(elements)
{}

void Folder::add_command(std::string &command_name)
{
    elements_.push_back(Element(command_name, false));
}

void Folder::add_folder(std::string &folder_name)
{
    elements_.push_back(Element(folder_name, true));
}

std::vector<Element> &Folder::get_elements()
{
    return elements_;
}