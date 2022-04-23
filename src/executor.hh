#pragma once

#include <string>

#include "singleton.hh"

class Executor : public Singleton<Executor>
{
public:
    bool execute(std::string &command_name, bool skip_execution);
};