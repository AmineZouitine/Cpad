#include "executor.hh"

#include <iostream>
#include <memory>
#include <stack>
#include <stdlib.h>

#include "arguments.hh"
#include "display.hh"

#define RESET "\033[0m"
#define BOLDBLUE "\033[1m\033[34m" /* Bold Blue */
#define BOLDRED "\033[1m\033[31m" /* Bold Red */
#define BOLDGREEN "\033[1m\033[32m" /* Bold Green */
#define YELLOW "\033[33m" /* Yellow */

bool Executor::execute(std::string &command_name,
                       Executor::ExecutionType &exec_type)
{
    system("clear");
    std::string display_line;
    switch (exec_type)
    {
    case Executor::ExecutionType::COMMAND:
        std::cout << "Execution of -- " << BOLDGREEN << command_name << RESET
                  << std::endl;
        std::cout << "---\n";
        system(command_name.c_str());
        std::cout << "---\n\n";
        return true;
    case Executor::ExecutionType::FOLDER:
        display_line = "Creation of folder -- ";
        break;
    case Executor::ExecutionType::CREATE_COMMAND:
        display_line = "Creation of command -- ";
        break;
    case Executor::ExecutionType::CREATE_FOLDER:
        display_line = "Creation of folder -- ";
        break;
    case Executor::ExecutionType::DELETE_COMMAND:
        display_line = "Deletion of command -- ";
        break;
    case Executor::ExecutionType::DELETE_FOLDER:
        display_line = "Deletion of folder -- ";
        break;
    case Executor::ExecutionType::MOVE_FOLDER:
        display_line = "You move into the folder -- ";
        break;
    default:
        return true;
    }
    std::cout << display_line << BOLDGREEN << command_name << RESET << '\n'
              << std::endl;
    return true;
}

void Executor::command_launcher(std::map<std::string, Folder> &map,
                                std::string &home_path)
{
    std::string command_input;
    std::string command_name;
    std::string current_folder = ".";
    std::stack<std::string> last_folders;
    Executor::ExecutionType exec_type;
    do
    {
        exec_type = Executor::ExecutionType::NONE;
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
                parse_arg(command_input, map, current_folder, home_path,
                          exec_type);
                command_name = command_input;
            }
            continue;
        }

        size_t command_number = std::stoi(command_input);

        if (command_number > elements.size() || command_number < 1)
        {
            if (command_number == elements.size() + 1 && current_folder != ".")
            {
                current_folder = last_folders.top();
                command_name = current_folder;
                exec_type = Executor::ExecutionType::MOVE_FOLDER;
                last_folders.pop();
            }
            continue;
        }

        command_name = elements[command_number - 1].get_name();
        if (elements[command_number - 1].get_is_folder())
        {
            last_folders.emplace(current_folder);
            current_folder = command_name;
        }
        exec_type = elements[command_number - 1].get_is_folder()
            ? Executor::ExecutionType::MOVE_FOLDER
            : Executor::ExecutionType::COMMAND;

    } while (command_input != "q"
             && Executor::instance().execute(command_name, exec_type));
}