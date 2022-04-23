#include <algorithm>
#include <cstddef>
#include <ctype.h>
#include <fstream>
#include <iostream>
#include <stack>
#include <string>
#include <cstring>

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

void command_launcher(std::map<std::string, Folder> &map,
                      std::string &command_input, std::string &current_folder,
                      std::string &command_name)
{
    bool skip_execute = false;
    std::stack<std::string> last_folders;
    do
    {
        Display::instance().display(current_folder, map);
        auto elements = map[current_folder].get_elements();

        std::cout << "Choose your command -> ";
        std::cin >> command_input;

        if (!std::all_of(command_input.cbegin(), command_input.cend(),
                         ::isdigit))
            continue;

        size_t command_number = std::stoi(command_input);

        if (command_number > elements.size() || command_number < 1)
        {
            if (command_number == elements.size() + 1 && current_folder != ".")
            {
                current_folder = last_folders.top();
                last_folders.pop();
            }

            skip_execute = true;
            continue;
        }

        command_name = elements[command_number - 1].get_name();
        if (elements[command_number - 1].get_is_folder())
        {
            last_folders.emplace(current_folder);
            current_folder = command_name;
        }

        skip_execute = elements[command_number - 1].get_is_folder();

    } while (command_input != "q"
             && Executor::instance().execute(command_name, skip_execute));
}

int main(int argc, char **argv)
{
    std::string home_path = std::string(getenv("HOME")) + "/.cpad";
    std::ifstream json_file;
    home_file_check(json_file, home_path);
    auto map = Convertor::instance().read(home_path);
    if (argc != 1)
        parse_arg(argc, argv, map, home_path);
    else
    {
        std::string command_input;
        std::string command_name;
        std::string current_folder = ".";

        command_launcher(map, command_input, current_folder, command_name);
    }
}