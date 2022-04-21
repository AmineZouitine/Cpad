#include "executor.hh"

#include <iostream>
#include <memory>
#include <stdlib.h>

bool Executor::execute(std::string &command_name, bool is_folder)
{
    if (!is_folder)
        system(command_name.c_str());
    return true;
}