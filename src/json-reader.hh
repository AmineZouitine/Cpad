#pragma once

#include "singleton.hh"
#include "folder.hh"

#include <map>
#include <string>

class JsonReader : public Singleton<JsonReader>
{
public:
    std::map<std::string, Folder>& readJson(std::string path);
    void saveToJson(std::string path, Folder& currentObject);
};