#include "json-reader.hh"

#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
using json = nlohmann::json;


std::map<std::string, Folder> JsonReader::readJson(std::string path)
{
    auto map = std::map<std::string, Folder>();
    std::ifstream ifs(path);
    json json = json::parse(ifs);
    for (const auto &el : json.items())
    {
        std::vector<Element> elements;
        std::string key = el.key();
        for (const auto &elt : json[key].items())
        {
            bool is_folder = elt.key() == "folders";
            for (std::string name : elt.value())
                elements.push_back(Element(name, is_folder));
        }
        map.insert({ key, Folder(elements) });
    }

    return map;
}

void JsonReader::saveToJson(std::string path, Folder &currentObject)
{
    return;
}
