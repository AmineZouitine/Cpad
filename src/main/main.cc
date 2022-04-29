#include <algorithm>
#include <cstddef>
#include <cstring>
#include <ctype.h>
#include <fstream>
#include <iostream>
#include <stack>
#include <string>

#include "../scaner.hh"
#include "../argument-type.hh"
#include "../convertor.hh"
#include "../display.hh"
#include "../executor.hh"

void home_file_check(std::ifstream &cpad_file, std::string &home_path)
{
    cpad_file.open(home_path);
    if (!cpad_file)
    {
        std::ofstream outfile(home_path);
        outfile << "CURRENT .\n--STOP--";
    }
}

void launch(std::map<std::string, Folder> &map, std::string &home_path)
{

    std::string command_input;
    std::string current_folder = ".";
    std::stack<std::string> last_folders;
    Executor::ExecutionType executor = Executor::ExecutionType::QUIT;
    do
    {
        Display::instance().display(map, current_folder);
        std::getline(std::cin, command_input);

        if (command_input.empty())
            continue;
        
        auto tokens = Scaner::instance().scan(command_input);
        auto error = ErrorHandling::instance().check_error(map, tokens, current_folder);

        if (error != ErrorHandling::Error::NONE)
        {
            Display::instance().display_error(error);
            continue;
        }
        auto executor = Executor::instance().execute(map, current_folder, tokens, home_path);
        if (executor == Executor::ExecutionType::MOVE_FOLDER)
        {
            last_folders.emplace(current_folder);
            current_folder = 
        }
        else
        {
            
        }
    } while (executor != Executor::ExecutionType::QUIT);
}

int main()
{
    std::string home_path = std::string(getenv("HOME")) + "/.cpad";
    std::ifstream cpad_file;
    home_file_check(cpad_file, home_path);
    auto map = Convertor::instance().read(home_path);

    launch(map, home_path);
}