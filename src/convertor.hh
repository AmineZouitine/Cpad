#pragma once

#include <map>
#include <string>

#include "folder.hh"
#include "singleton.hh"

class Convertor : public Singleton<Convertor>
{
public:
    std::map<std::string, Folder> read(std::string& path);
    void write(std::map<std::string, Folder>& map);
};