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

void Convertor::write(std::map<std::string, Folder> &map)
{
    map.clear();
    return;
}
