#include <algorithm>
#include <cstddef>
#include <ctype.h>
#include <fstream>
#include <iostream>
#include <stack>
#include <string>

#include "../arguments.hh"
#include "../convertor.hh"
#include "../display.hh"
#include "../executor.hh"

void args_count_check(int argc)
{
    if (argc != 1)
    {
        std::cout << "Le main ne prend aucun argument" << '\n';
        exit(1);
    }
}

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

void parse_arg(int argc, char **argv, std::map<std::string, Folder> &map, std::string &path)
{
    if (argv[1] == "-ac")
        parse_cmd(argc, argv, map, path);
    else if (argv[1] == "-af")
        parse_folder(argc, argv);

    else
    {
        std::cerr << "Invalid argument: " << argv[1] << "\n";
        exit(1);
    }
}

void parse_cmd(int argc, char **argv, std::map<std::string, Folder> &map, std::string &path)
{
    std::string folder;
    std::string command;
    if (argv[argc - 1][0] == '[')
        folder =
            argv[argc - 1].substr(1, argv[argc - 1].length() - 2) else folder =
                ".";
    for (size_t i = 2; i < argc; i++)
    {
        command += argv[i];
    }
    Convertor::instance().add_command(map, folder, command);
    Convertor::instance().write(map, path);
}

std::string bracket_less(std::string &str)
{
    std::string res;
    for (size_t i = 1; i < str.length() - 1; i++)
    {
        res.append(str[i]);
    }
    return res;
}

int main(int argc, char **argv)
{
    std::string home_path = std::string(getenv("HOME")) + "/.cpad";
    std::ifstream json_file;
    home_file_check(json_file, home_path);
    auto map = Convertor::instance().read(home_path);
    if (argc != 1)
    {
        parse_arg(argc, argv, home_path);
    }
    // args_count_check(argc);
    else
    {
        std::string command_input;
        std::string command_name;
        std::string current_folder = ".";

        command_launcher(map, command_input, current_folder, command_name);
    }
}