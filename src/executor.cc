#include "executor.hh"

#include <iostream>
#include <memory>
#include <stack>
#include <stdlib.h>
#include <unistd.h>

#include "arguments.hh"
#include "display.hh"

#define RESET "\033[0m"
#define BOLD "\033[1m"
#define WHITE "\033[37m"
#define BOLDBLUE "\033[1m\033[34m" /* Bold Blue */
#define BOLDRED "\033[1m\033[31m" /* Bold Red */
#define UNDERBOLDRED "\033[4m\033[1m\033[31m" /* Underligned Bold Red */
#define RED "\033[31m" /* RED */
#define BOLDGREEN "\033[1m\033[32m" /* Bold Green */
#define GREEN "\033[0m\033[32m" /*Green */
#define YELLOW "\033[33m" /* Yellow */

bool cd_exec(std::string command)
{
    std::stringstream ss(command);
    std::string token;
    ss >> token;
    if (token == "cd")
    {
        std::string cmd_argument;
        concat_argument(ss, token, cmd_argument);
        if (cmd_argument.empty())
            cmd_argument = std::string(getenv("HOME"));
        chdir(cmd_argument.c_str());
        return true;
    }
    return false;
}

bool Executor::is_template(std::string command)
{
    return command.find("[?]") != std::string::npos;
}

void Executor::remplace_templates(std::string &command, bool clear)
{
    size_t index = 1;

    while (true)
    {
        if (command.find("[?]", index) == std::string::npos)
            break;
        std::string user_input;

        std::cout << BOLDGREEN << "current_command: " << RESET << command
                  << "\n";
        std::cout << index++ << " ➜ remplace " << RED << "[?]" << RESET
                  << " ➜ ";
        std::getline(std::cin, user_input);
        std::cout << '\n';
        command.replace(command.find("[?]"), 3, user_input);
        if (clear)
            system("clear");
    }
}

bool Executor::execute(std::string &command_name,
                       Executor::ExecutionType &exec_type,
                       Element &combot_element, bool clear)
{
    if (clear)
        system("clear");
    std::string display_line;
    switch (exec_type)
    {
    case Executor::ExecutionType::COMMAND:
        if (is_template(command_name))
            remplace_templates(command_name, clear);
        std::cout << BOLDGREEN + std::string("🔧 ") + "Execution of: " << RESET
                  << command_name << std::endl;
        std::cout << "---\n";
        if (!cd_exec(command_name))
            system(command_name.c_str());
        std::cout << "---\n\n";
        return true;
    case Executor::ExecutionType::CREATE_COMMAND:
        display_line =
            BOLDGREEN + std::string("✔️ ") + "Creation of command:";
        break;
    case Executor::ExecutionType::CREATE_FOLDER:
        display_line =
            BOLDGREEN + std::string("✔️ ") + "Creation of folder:";
        break;
    case Executor::ExecutionType::DELETE_COMMAND:
        display_line =
            BOLDGREEN + std::string("✔️ ") + "Deletion of command:";
        break;
    case Executor::ExecutionType::DELETE_FOLDER:
        display_line =
            BOLDGREEN + std::string("✔️ ") + "Deletion of folder:";
        break;
    case Executor::ExecutionType::MOVE_FOLDER:
        display_line =
            BOLDGREEN + std::string("✔️ ") + "You move into the folder:";
        break;
    case Executor::ExecutionType::RESET_FOLDER:
        display_line =
            BOLDGREEN + std::string("✔️ ") + "You reset the folder:";
        break;
    case Executor::ExecutionType::SWAP:
        display_line =
            BOLDGREEN + std::string("✔️ ") + "You move elements:";
        break;
    case Executor::ExecutionType::COMMAND_ERROR_NAME:
        display_line = BOLDRED + std::string("✖️ ") + UNDERBOLDRED
            + std::string("You can't add same command twice:");
        break;
    case Executor::ExecutionType::FOLDER_ERROR_NAME:
        display_line = BOLDRED + std::string("✖️ ") + UNDERBOLDRED
            + std::string("You can't add same folder twice:");
        break;
    case Executor::ExecutionType::EMPTY_NAME:
        display_line = BOLDRED + std::string("✖️ ") + UNDERBOLDRED
            + std::string("You can't add empty name.") + RESET
            + std::string(" 👻");
        command_name = "";
        break;
    case Executor::ExecutionType::COMBO:
        display_line = BOLDGREEN + std::string("✔️ ") + "COMBO EXECUTION:";
        std::cout << RESET << display_line << RESET << WHITE << ' '
                  << command_name << RESET << '\n'
                  << std::endl;
        for (auto &command : combot_element.get_combo_elements_())
        {
            Executor::ExecutionType exec_type =
                Executor::ExecutionType::COMMAND;
            execute(command.get_name(), exec_type, combot_element, false);
        }
        return true;
    case Executor::ExecutionType::DELETE_EMPTY_NAME:
        display_line = BOLDRED + std::string("✖️ ") + UNDERBOLDRED
            + std::string("You can't delete without a name.") + RESET
            + std::string(" 👻");
        command_name = "";
        break;
    case Executor::ExecutionType::SWAP_WRONG_INDEX:
        display_line = BOLDRED + std::string("✖️ ") + UNDERBOLDRED
            + std::string("Move index doesn't exist.") + RESET;
        break;
    case Executor::ExecutionType::BIG_INDEX:
        display_line = BOLDRED + std::string("✖️ ") + UNDERBOLDRED
            + std::string("Move index too big.") + RESET;
        break;
    case Executor::ExecutionType::EMPTY_INDEX:
        display_line = BOLDRED + std::string("✖️ ") + UNDERBOLDRED
            + std::string("Need two index.") + RESET + std::string(" 👻");
        break;
    case Executor::ExecutionType::NO_INT_INDEX:
        display_line = BOLDRED + std::string("✖️ ") + UNDERBOLDRED
            + std::string("Index need to be int.");
        break;
    default:
        return true;
    }
    std::cout << RESET << display_line << RESET << WHITE << ' ' << command_name
              << RESET << '\n'
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
    Element combo_element;
    do
    {
        exec_type = Executor::ExecutionType::NONE;
        Display::instance().display(current_folder, map);
        auto elements = map[current_folder].get_elements();

        std::cout << "Choose your command ➜ ";
        std::getline(std::cin, command_input);

        if (command_input.empty())
            continue;

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
            else if (current_folder != "." && command_input == "b")
            {
                current_folder = last_folders.top();
                command_name = current_folder;
                exec_type = Executor::ExecutionType::MOVE_FOLDER;
                last_folders.pop();
            }
            else if (command_input == "h")
            {
                system("clear");
                Display::instance().display_helper();
                std::cout << "Choose your command ➜ ";
                std::getline(std::cin, command_input);
                str = command_input.substr(0, 3);
                if (is_command(str))
                {
                    parse_arg(command_input, map, current_folder, home_path,
                              exec_type);
                    command_name = command_input;
                }
            }
            continue;
        }

        size_t command_number;
        try
        {
            command_number = std::stoi(command_input);
        }
        catch (...)
        {
            exec_type = Executor::ExecutionType::BIG_INDEX;
            continue;
        }

        if (command_number > elements.size() || command_number < 1)
            continue;

        command_name = elements[command_number - 1].get_name();
        combo_element = elements[command_number - 1];
        if (elements[command_number - 1].get_is_folder())
        {
            last_folders.emplace(current_folder);
            current_folder = command_name;
        }

        exec_type = elements[command_number - 1].get_is_folder()
            ? Executor::ExecutionType::MOVE_FOLDER
            : elements[command_number - 1].get_is_combo()
            ? Executor::ExecutionType::COMBO
            : Executor::ExecutionType::COMMAND;

    } while (command_input != "q"
             && Executor::instance().execute(command_name, exec_type,
                                             combo_element));
}