#pragma once

#include "singleton.hh"
#include <string>

class ArgumentType : public Singleton<ArgumentType>
{
public:
    enum class ELEMENT_TYPE
    {
        EXECUTION,
        CREATE_COMMAND,
        CREATE_FOLDER,
        DELETE,
        MOVE,
        RESET_FOLDER,
        RESET_ALL,
        CREATE_COMBO
    };


    ELEMENT_TYPE convert_to_element_type(std::string& argument);
    int number_arguments_expected(ELEMENT_TYPE element_type);
};