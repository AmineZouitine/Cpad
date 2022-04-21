#pragma once

#include <map>
#include <string>

#include "folder.hh"
#include "singleton.hh"

class JsonReader : public Singleton<JsonReader>
{
public:
    std::map<std::string, Folder> readJson(std::string path);
    void saveToJson(std::string path, Folder &currentObject);
};