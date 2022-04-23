#include <algorithm>
#include <cstddef>
#include <ctype.h>
#include <fstream>
#include <iostream>
#include <stack>
#include <string>
#include <cstring>

#include "convertor.hh"
#include "display.hh"
#include "executor.hh"

enum Arguments
{
    ac,
    af
};

void parse_cmd(int argc, char **argv, std::map<std::string, Folder> &map,
               std::string &path, std::string &folder);

void parse_folder(int argc, char **argv, std::map<std::string, Folder> &map,
               std::string &path, std::string &folder);

void parse_arg(int argc, char **argv, std::map<std::string, Folder> &map,
               std::string &path);