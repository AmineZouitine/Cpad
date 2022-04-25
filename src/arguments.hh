#include <algorithm>
#include <cstddef>
#include <cstring>
#include <ctype.h>
#include <fstream>
#include <iostream>
#include <stack>
#include <string>
#include <sstream>

#include "convertor.hh"
#include "display.hh"
#include "executor.hh"

void parse_cmd(int argc, char **argv, std::map<std::string, Folder> &map,
               std::string &path, std::string &folder);

void parse_folder(int argc, char **argv, std::map<std::string, Folder> &map,
                  std::string &path, std::string &folder);

void parse_arg(std::string &arg, std::map<std::string, Folder> &map, std::string &key, std::string &home_path, Executor::ExecutionType& exec_type);

bool is_command(std::string &cmd);

void concat_argument(std::string &arg, std::string token,
                      std::string &cmd_argument);