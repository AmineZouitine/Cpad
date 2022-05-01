#pragma once

#include <map>

#include "folder.hh"
#include "scaner.hh"
#include "singleton.hh"

class ErrorHandling : public Singleton<ErrorHandling>
{
public:
    enum class Error
    {
        COMMAND_ERROR_NAME,
        FOLDER_ERROR_NAME,
        BIG_INDEX,
        OUT_OF_RANGE,
        TOO_MUCH_ARGUMENTS,
        NEED_MORE_ARGUMENTS,
        INVALID_INPUT,
        NONE
    };

    Error check_error(std::map<std::string, Folder> &map, Tokens &tokens,
                      std::string &current_folder);

private:
    Error parsing_int(std::map<std::string, Folder> &map,
                      std::string &current_folder, std::string &input);

    Error check_arguments_size(Tokens &tokens);
    Error check_execution(std::map<std::string, Folder> &map, Tokens &tokens,
                          std::string &current_folder);
    Error check_create_command(std::map<std::string, Folder> &map,
                               Tokens &tokens, std::string &current_folder);
    Error check_create_folder(std::map<std::string, Folder> &map,
                              Tokens &tokens);
    Error check_move(std::map<std::string, Folder> &map, Tokens &tokens,
                     std::string &current_folder);
    Error check_reset_folder(std::map<std::string, Folder> &map, Tokens &tokens,
                             std::string &current_folder);
    Error check_reset_all();
    Error check_create_combo(Tokens &tokens);
    Error check_delete(std::map<std::string, Folder> &map, Tokens &tokens,
                       std::string &current_folder);
};