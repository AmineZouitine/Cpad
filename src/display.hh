#pragma once

#include <iostream>
#include <map>
// #include <windows.hh>

#include "element.hh"
#include "folder.hh"
#include "singleton.hh"

class Display : public Singleton<Display>
{
public:
    void display(std::string &key, std::map<std::string, Folder> &map);
    void display_helper();
};