#include "executor.hh"

#include <iostream>
#include <memory>
#include <stdlib.h>

bool Executor::execute(std::string &command_name)
{
    system(command_name.c_str());
    return true;
}