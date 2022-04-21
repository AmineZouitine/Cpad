#pragma once

#include "folder.hh"
#include "singleton.hh"

#include <map>
#include <string>

class JsonReader : public Singleton<JsonReader> {
public:
  std::map<std::string, Folder> readJson(std::string path);
  void saveToJson(std::string path, Folder &currentObject);
};