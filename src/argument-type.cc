#include "argument-type.hh"

#include <iostream>

ArgumentType::ELEMENT_TYPE
ArgumentType::convert_to_element_type(std::string &argument)
{
    if (argument == "-ac")
        return ELEMENT_TYPE::CREATE_COMMAND;
    else if (argument == "-af")
        return ELEMENT_TYPE::CREATE_FOLDER;
    else if (argument == "-de")
        return ELEMENT_TYPE::DELETE;
    else if (argument == "-rf")
        return ELEMENT_TYPE::RESET_FOLDER;
    else if (argument == "-ra")
        return ELEMENT_TYPE::RESET_ALL;
    else if (argument == "-mv")
        return ELEMENT_TYPE::MOVE;
    else if (argument == "-cb")
        return ELEMENT_TYPE::CREATE_COMBO;
    return ELEMENT_TYPE::EXECUTION;
}

int ArgumentType::number_arguments_expected(ELEMENT_TYPE element_type)
{
    switch (element_type)
    {
    case ArgumentType::ELEMENT_TYPE::CREATE_COMMAND:
    case ArgumentType::ELEMENT_TYPE::CREATE_FOLDER:
    case ArgumentType::ELEMENT_TYPE::DELETE:
    case ArgumentType::ELEMENT_TYPE::RESET_FOLDER:
        return 2;
    case ArgumentType::ELEMENT_TYPE::MOVE:
        return 3;
    case ArgumentType::ELEMENT_TYPE::EXECUTION:
    case ArgumentType::ELEMENT_TYPE::RESET_ALL:
        return 1;
    case ArgumentType::ELEMENT_TYPE::CREATE_COMBO:
        return -1;
    }
    return -1;
}