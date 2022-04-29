#pragma once

#include <iostream>
#include <map>
// #include <windows.hh>

#include "element.hh"
#include "folder.hh"
#include "singleton.hh"
#include "error-handling.hh"
#include "executor.hh"

class Display : public Singleton<Display>
{
public:
    void display_error(ErrorHandling::Error error);
    void display_executor(Executor::ExecutionType execution);
    void display(std::map<std::string, Folder> &map, std::string& current_folder);
    void display_helper();
};