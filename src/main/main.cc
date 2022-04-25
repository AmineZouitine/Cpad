#include <algorithm>
#include <cstddef>
#include <cstring>
#include <ctype.h>
#include <fstream>
#include <iostream>
#include <stack>
#include <string>

#include "../arguments.hh"
#include "../convertor.hh"
#include "../display.hh"
#include "../executor.hh"

void home_file_check(std::ifstream &json_file, std::string &home_path)
{
    json_file.open(home_path);
    if (!json_file)
    {
        std::ofstream outfile(home_path);
        outfile << "CURRENT .\n--STOP--";
    }
}
int main()
{
    std::string home_path = std::string(getenv("HOME")) + "/.cpad";
    std::ifstream json_file;
    home_file_check(json_file, home_path);
    auto map = Convertor::instance().read(home_path);

    Executor::instance().command_launcher(map, home_path);
}