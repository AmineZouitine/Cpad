#include <algorithm>
#include <cstddef>
#include <cstring>
#include <ctype.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stack>
#include <string>

#include "convertor.hh"
#include "display.hh"
#include "executor.hh"

void parse_arg(std::string &arg, std::map<std::string, Folder> &map,
               std::string &key, std::string &home_path,
               Executor::ExecutionType &exec_type);

bool is_command(std::string &cmd);

void concat_argument(std::stringstream &ss, std::string token,
                     std::string &cmd_argument);


void error_handling(std::map<std::string, Folder> &map, std::string &key,
                    std::string &user_input,
                    Executor::ExecutionType &exec_type);