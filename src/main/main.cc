#include <algorithm>
#include <cstddef>
#include <cstring>
#include <ctype.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stack>
#include <string>

#include "../argument-type.hh"
#include "../convertor.hh"
#include "../display.hh"
#include "../executor.hh"
#include "../scaner.hh"
#include "../utils.hh"

void manage_directory(std::stack<std::string> &last_folders,
                      std::string &current_folder,
                      Executor::executor_result executor)
{
    if (executor.first == Executor::ExecutionType::RESET_ALL)
    {
        current_folder = ".";
        last_folders = std::stack<std::string>();
    }
    else if (executor.first == Executor::ExecutionType::MOVE_FOLDER)
    {
        last_folders.emplace(current_folder);
        current_folder = executor.second;
    }
    else if (executor.first == Executor::ExecutionType::BACK_FOLDER)
    {
        current_folder = last_folders.top();
        last_folders.pop();
    }
}

void launch(std::map<std::string, Folder> &map, std::string &home_path,
            bool display_emoji)
{
    std::stack<std::string> last_folders;
    std::string current_folder = ".";

    Executor::executor_result executor;
    std::string command_input;
    do
    {
        Element combo;
        executor =
            Executor::executor_result(Executor::ExecutionType::CLEAR, "");

        Display::instance().display(map, current_folder, display_emoji);
        std::cout << "Choose your command ➜ ";
        std::getline(std::cin, command_input);
        if (command_input.empty())
        {
            Display::instance().display_executor(executor, combo, true,
                                                 display_emoji);
            continue;
        }

        auto tokens = Scaner::instance().scan(command_input);
        auto error =
            ErrorHandling::instance().check_error(map, tokens, current_folder);

        if (error != ErrorHandling::Error::NONE)
        {
            Display::instance().display_error(error, display_emoji);
            continue;
        }

        executor = Executor::instance().execute(
            map, current_folder, tokens, home_path, combo, display_emoji);
        Display::instance().display_executor(executor, combo, display_emoji);
        manage_directory(last_folders, current_folder, executor);
    } while (executor.first != Executor::ExecutionType::QUIT);
}

int main(int argc, char **argv)
{
    auto home_path = std::string(getenv("HOME")) + "/.cpad";
    std::ifstream cpad_file;
    home_file_check(cpad_file, home_path);

    auto lines = get_all_lines(home_path);
    bool display_emoji = check_arguments(argc, lines, argv);

    rewrite(home_path, lines, display_emoji);
    auto map = Convertor::instance().read(home_path, display_emoji);

    launch(map, home_path, display_emoji);
}