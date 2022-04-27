#include "convertor.hh"

#include <fstream>
#include <iostream>
#include <sstream>

std::map<std::string, Folder> Convertor::read(std::string &path)
{
    auto map = std::map<std::string, Folder>();

    std::string line;
    std::ifstream file(path);
    std::vector<Element> elements_;
    std::string key;

    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string token;
        std::string current_element;
        ss >> token;
        if (token == "CURRENT")
        {
            size_t count = 0;
            while (ss >> token)
            {
                if (count != 0)
                    key += ' ';
                key += token;
                count++;
            }
        }
        else if (token == "FOLDER" || token == "COMMAND")
        {
            bool is_folder = token == "FOLDER";
            size_t count = 0;
            while (ss >> token)
            {
                if (count != 0)
                    current_element += ' ';
                current_element += token;
                count++;
            }
            elements_.push_back(Element(current_element, is_folder));
        }
        else // STOP TOKEN
        {
            map.insert({ key, elements_ });
            key.clear();
            elements_.clear();
        }
    }

    return map;
}

void Convertor::write(std::map<std::string, Folder> &map, std::string &path)
{
    std::ofstream MyFile(path);

    for (auto &folder : map)
    {
        MyFile << "CURRENT " + folder.first + '\n';
        for (auto &elem : folder.second.get_elements())
        {
            if (elem.get_is_folder())
                MyFile << "FOLDER ";
            else
                MyFile << "COMMAND ";
            MyFile << elem.get_name() << '\n';
        }
        MyFile << "--STOP--\n";
    }
    MyFile.close();
    return;
}

void Convertor::add_command(std::map<std::string, Folder> &map,
                            std::string &key, std::string &command)
{
    map[key].get_elements().push_back(Element(command, false));
}

void Convertor::remove_command(std::map<std::string, Folder> &map,
                               std::string &key, size_t command_number)
{
    map[key].get_elements().erase(map[key].get_elements().begin()
                                  + command_number - 1);
}

void Convertor::get_all_folders(std::map<std::string, Folder> &map,
                                std::string &key,
                                std::vector<std::string> &folders_name)
{
    for (auto &elem : map[key].get_elements())
    {
        if (elem.get_is_folder())
        {
            folders_name.push_back(elem.get_name());
            get_all_folders(map, elem.get_name(), folders_name);
        }
    }
}

void Convertor::remove_folder(std::map<std::string, Folder> &map,
                              std::string &current_folder,
                              std::string &folder_name)
{
    std::vector<std::string> folders_name;
    get_all_folders(map, folder_name, folders_name);
    for (auto &elem : folders_name)
        map.erase(elem);
    for (size_t i = 0; i < map[current_folder].get_elements().size(); i++)
    {
        auto elem = map[current_folder].get_elements()[i];
        if (elem.get_is_folder() && elem.get_name() == folder_name)
            remove_command(map, current_folder, i + 1);
    }
    map.erase(folder_name);
}

void Convertor::reset_folder(std::map<std::string, Folder> &map,
                             std::string &key)
{
    std::vector<std::string> folders_name;
    get_all_folders(map, key, folders_name);
    for (auto &elem : folders_name)
        map.erase(elem);
    map[key].get_elements().clear();
}

void Convertor::reset_all(std::map<std::string, Folder> &map)
{
    std::string source = ".";
    reset_folder(map, source);
}

void Convertor::add_folder(std::map<std::string, Folder> &map, std::string &key,
                           std::string &folder_name)
{
    map[key].get_elements().push_back(Element(folder_name));
    map.insert({ folder_name, Folder() });
}

void Convertor::move(std::map<std::string, Folder> &map, std::string &key, size_t src_index,
          size_t dst_index)
{
    std::swap(map[key].get_elements()[src_index], map[key].get_elements()[dst_index]);
}
