#include "executor.hh"
#include "display.hh"
#include "arguments.hh"

#include <iostream>
#include <memory>
#include <stack>
#include <stdlib.h>

#define RESET "\033[0m"
#define BOLDBLUE "\033[1m\033[34m" /* Bold Blue */
#define BOLDRED "\033[1m\033[31m" /* Bold Red */
#define BOLDGREEN "\033[1m\033[32m" /* Bold Green */
#define YELLOW "\033[33m" /* Yellow */

bool Executor::execute(std::string &command_name,
                       Executor::ExecutionType &exec_type)
{
    system("clear");
    switch (exec_type)
    {
    case Executor::ExecutionType::COMMAND:
        std::cout << "\n\nExecution of -- " << BOLDGREEN << command_name
                  << RESET << std::endl;
        std::cout << "---\n";
        system(command_name.c_str());
        std::cout << "---\n\n";
        break;
    case Executor::ExecutionType::FOLDER:
        std::cout << "\n\nCreation of -- " << BOLDGREEN << command_name
                  << RESET << std::endl;
        break;
    case Executor::ExecutionType::CREATE_COMMAND:
        break;
    case Executor::ExecutionType::CREATE_FOLDER:
        break;
    case Executor::ExecutionType::DELETE_COMMAND:
        break;
    case Executor::ExecutionType::DELETE_FOLDER:
        break;
    case Executor::ExecutionType::MOVE_FOLDER:
        break;
    default:
        break;
    }
    return true;
}

void command_launcher(std::map<std::string, Folder> &map,
                      std::string &home_path)
{
    Executor::ExecutionType exec_type = Executor::ExecutionType::NONE;
    std::string command_input;
    std::string command_name;
    std::string current_folder = ".";
    std::stack<std::string> last_folders;
    do
    {
        Display::instance().display(current_folder, map);
        auto elements = map[current_folder].get_elements();

        std::cout << "Choose your command -> ";
        std::getline(std::cin, command_input);
        if (!std::all_of(command_input.cbegin(), command_input.cend(),
                         ::isdigit))
        {
            std::string str = command_input.substr(0, 3);
            if (is_command(str))
            {
                // system("clear");
                parse_arg(command_input, map, current_folder, home_path,
                          exec_type);
            }
            continue;
        }

        size_t command_number = std::stoi(command_input);

        if (command_number > elements.size() || command_number < 1)
        {
            if (command_number == elements.size() + 1 && current_folder != ".")
            {
                current_folder = last_folders.top();
                last_folders.pop();
            }
            exec_type = Executor::ExecutionType::MOVE_FOLDER;
            continue;
        }

        command_name = elements[command_number - 1].get_name();
        if (elements[command_number - 1].get_is_folder())
        {
            last_folders.emplace(current_folder);
            current_folder = command_name;
        }
        exec_type = elements[command_number - 1].get_is_folder()
            ? Executor::ExecutionType::FOLDER
            : Executor::ExecutionType::COMMAND;

    } while (command_input != "q"
             && Executor::instance().execute(command_name, exec_type));
}