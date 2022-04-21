#pragma once

#include <string>
#include "singleton.hh"

class Executor : public Singleton<Executor>
{
public:
    void execute(std::string& command_name);
};