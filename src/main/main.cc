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

void launch(std::map<std::string, Folder> &map, std::string &home_path)
{
    std::stack<std::string> last_folders;
    std::string current_folder = ".";

    Executor::executor_result executor;
    std::string command_input;
    do
    {
        Element combo;
        executor = Executor::executor_result(Executor::ExecutionType::CLEAR, "");

        Display::instance().display(map, current_folder);
        std::cout << "Choose your command ➜ ";
        std::getline(std::cin, command_input);
        if (command_input.empty())
        {
            Display::instance().display_executor(executor, combo, true);
            continue;
        }

        auto tokens = Scaner::instance().scan(command_input);
        auto error = ErrorHandling::instance().check_error(map, tokens, current_folder);

        if (error != ErrorHandling::Error::NONE)
        {
            Display::instance().display_error(error, true);
            continue;
        }

        executor = Executor::instance().execute(map, current_folder, tokens, home_path, combo);
        Display::instance().display_executor(executor, combo, true);
        manage_directory(last_folders, current_folder, executor);
    } while (executor.first != Executor::ExecutionType::QUIT);
}

bool check_arguments(int argc, char** argv)
{
    if (argc == 2 && argv[1] == "0")
        return false;
    return true;
}

void check_cpad_file(std::string& home_path, bool emoji)
{
    std::ofstream MyFile(home_path);
    std::ifstream file(home_path);

    std::string token;
    file >> token;
    if (token != "EMOJI")
    {
        std::string command_preprend = "echo -e \"EMOJI "
            + std::string(emoji ? "TRUE" : "FALSE") + "$(cat " + home_path
            + ")\" > " + home_path;
        system(command_preprend.c_str());
    }

}

int main(int argc, char** argv)
{
    bool display_emoji = check_arguments(argc, argv);
    auto home_path = std::string(getenv("HOME")) + "/.cpad";
    std::ifstream cpad_file;
    home_file_check(cpad_file, home_path);

    auto map = Convertor::instance().read(home_path);

    launch(map, home_path);
}