#include "display.hh"

#include <unistd.h>

void Display::execute(std::string &command, bool emoji, bool clear)
{
    if (is_template(command))
        remplace_templates(command, clear);

    std::cout << BOLDGREEN + (emoji ? std::string("🔧 ") : "") + "Execution of: "
              << RESET << command << std::endl;
    std::cout << "---\n";
    if (!cd_exec(command))
        system(command.c_str());
    std::cout << "---\n\n";
}

void Display::execute_combo(std::string &command, std::string display_line,
                            Element &element_combo, bool emoji)
{
    set_display_line(display_line, "COMBO EXECUTION:", "✔️ ", "", BOLDGREEN,
                     emoji);
    std::cout << RESET << display_line << RESET << WHITE << ' ' << command
              << RESET << '\n'
              << std::endl;
    for (auto &command : element_combo.get_combo_elements_())
    {
        Executor::executor_result exec =
            Executor::executor_result(Exec::COMMAND, command.get_name());
        display_executor(exec, command, emoji, false);
    }
}

void Display::set_display_line(std::string &display_line, std::string end_str,
                               std::string emoji_str, std::string replace,
                               std::string color, bool emoji)
{
    if (emoji)
        display_line = color + emoji_str + end_str;
    else
        display_line = color + replace + end_str;
    display_line += RESET;
}

bool Display::cd_exec(std::string command)
{
    std::stringstream ss(command);
    std::string token;
    ss >> token;
    if (token == "cd")
    {
        ss >> token;
        if (command.size() == 2)
            token = std::string(getenv("HOME"));
        chdir(token.c_str());
        return true;
    }
    return false;
}

bool Display::is_template(std::string command)
{
    if (command == "[?]")
        return true;
    return command.find("[?]") != std::string::npos;
}

void Display::remplace_templates(std::string &command, bool clear)
{
    size_t index = 1;

    while (true)
    {
        if (command.find("[?]", 0) == std::string::npos)
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

void Display::display_error(ErrorHandling::Error error, bool emoji)
{
    system("clear");
    std::string display_line;
    switch (error)
    {
    case Error::COMMAND_ERROR_NAME:
        set_display_line(
            display_line,
            "You can't have the same commands in the same folder twice.", "❌ ",
            "", BOLDRED, emoji);
        break;
    case Error::FOLDER_ERROR_NAME:
        set_display_line(display_line,
                         "You can't have two folders with the same name in the "
                         "whole project.",
                         "❌ ", "", BOLDRED, emoji);
        break;
    case Error::INVALID_INPUT:
        set_display_line(display_line, "Your input is invalid", "❌ ", "",
                         BOLDRED, emoji);
        break;
    case Error::OUT_OF_RANGE:
        set_display_line(
            display_line,
            "Your arguments must be in the interval of your folder.", "❌ ", "",
            BOLDRED, emoji);
        break;
    case Error::NEED_MORE_ARGUMENTS:
        set_display_line(display_line,
                         "Your function needs more arguments to be executed.",
                         "❌ ", "", BOLDRED, emoji);
        break;
    case Error::TOO_MUCH_ARGUMENTS:
        set_display_line(display_line,
                         "Your function needs less arguments to be executed.",
                         "❌ ", "", BOLDRED, emoji);
        break;
    case Error::BIG_INDEX:
        set_display_line(display_line, "Your index is too big.", "❌ ", "",
                         BOLDRED, emoji);
        break;
    case Error::NONE:
        break;
    }
    std::cout << RESET << display_line << RESET << std::endl;
    std::cout << RESET << YELLOW << "     Press " << RESET << BOLDGREEN << "h"
              << RESET << YELLOW << " to see the documentation." << RESET
              << '\n'
              << std::endl;
}

void Display::display_executor(Executor::executor_result executor,
                               Element &element_combo, bool emoji, bool clear)
{
    if (clear)
        system("clear");
    std::string display_line;
    switch (executor.first)
    {
    case Executor::ExecutionType::COMMAND:
        return execute(executor.second, emoji, clear);
    case Executor::ExecutionType::CREATE_COMMAND:
        set_display_line(display_line, "Creation of command:", "✔️ ", "",
                         BOLDGREEN, emoji);
        break;
    case Executor::ExecutionType::CREATE_COMBO:
        set_display_line(display_line, "Creation of combo:", "✔️ ", "",
                         BOLDGREEN, emoji);
        break;
    case Executor::ExecutionType::CREATE_FOLDER:
        set_display_line(display_line, "Creation of the folder:", "✔️ ", "",
                         BOLDGREEN, emoji);
        break;
    case Executor::ExecutionType::DELETE_COMMAND:
        set_display_line(display_line, "Deletion of command:", "✔️ ", "",
                         BOLDGREEN, emoji);
        break;
    case Executor::ExecutionType::DELETE_FOLDER:
        set_display_line(display_line, "Deletion of folder:", "✔️ ", "",
                         BOLDGREEN, emoji);
        break;
    case Executor::ExecutionType::DELETE_COMBO:
        set_display_line(display_line, "Deletion of combo:", "✔️ ", "",
                         BOLDGREEN, emoji);
        break;
    case Executor::ExecutionType::BACK_FOLDER:
        set_display_line(display_line, "You have returned to your old file",
                         "✔️ ", "", BOLDGREEN, emoji);
        break;
    case Executor::ExecutionType::MOVE_FOLDER:
        set_display_line(display_line, "You move into the folder:", "✔️ ",
                         "", BOLDGREEN, emoji);
        break;
    case Executor::ExecutionType::RESET_FOLDER:
        set_display_line(display_line, "You reset the folder:", "✔️ ", "",
                         BOLDGREEN, emoji);
        break;
    case Executor::ExecutionType::MOVE:
        set_display_line(display_line, "You move elements:", "✔️ ", "",
                         BOLDGREEN, emoji);
        break;
    case Executor::ExecutionType::RESET_ALL:
        set_display_line(display_line, "You reset all folders:", "✔️ ", "",
                         BOLDGREEN, emoji);
        break;
    case Executor::ExecutionType::DISPLAY_HELP:
        display_helper();
        std::cout << "➜ ";
        std::getline(std::cin, display_line);
        system("clear");
        return;
    case Executor::ExecutionType::QUIT:
        set_display_line(display_line, "See you soon !", "👋 ", "", BOLDGREEN,
                         emoji);
        break;
    case Executor::ExecutionType::COMBO_EXECUTION:
        return execute_combo(executor.second, display_line, element_combo,
                             emoji);
    case Executor::ExecutionType::CLEAR:
        set_display_line(display_line, "CLEAR !", "✔️ ", "", BOLDGREEN,
                         emoji);
        break;
    }
    std::cout << RESET << display_line << RESET << WHITE << ' '
              << executor.second << RESET << '\n'
              << std::endl;
}

void Display::display(std::map<std::string, Folder> &map,
                      std::string &current_folder, bool emoji)
{
    std::cout << (emoji ? "📁 : " : "Current folder: ") << BOLDGREEN
              << current_folder << std::endl
              << std::endl;
    std::cout << RESET;
    int i = 1;
    auto elms = map[current_folder].get_elements();
    for (auto elm : elms)
    {
        if (elm.get_is_folder())
            std::cout << BOLD << std::to_string(i) << RESET
                      << (emoji ? " ➜ " : " - ") << BOLDBLUE << elm.get_name()
                      << (emoji ? " 📁 " : "") << std::endl;
        else if (!elm.get_is_combo())
            std::cout << BOLD << std::to_string(i) << RESET
                      << (emoji ? " ➜ " : " - ") << elm.get_name() << std::endl;
        else
        {
            if (elm.get_name().empty())
            {
                if (elm.get_combo_elements_().size() > 0)
                    std::cout << BOLD << std::to_string(i) << RESET
                              << (emoji ? " ➜ " : " - ")
                              << elm.get_combo_elements_()[0].get_name()
                              << std::endl;

                std::string space = " ";
                for (size_t i = 1; i < elm.get_combo_elements_().size(); i++)
                {
                    std::cout << space << RESET << (emoji ? " 🔸 " : " - ")
                              << elm.get_combo_elements_()[i].get_name()
                              << std::endl;
                }
            }
            else
            {
                std::cout << BOLD << std::to_string(i) << RESET
                          << (emoji ? " ➜ " : " - ") << BOLDRED
                          << elm.get_name() << RESET << (emoji ? " 🔸 " : "")
                          << std::endl;
            }
        }
        std::cout << RESET;
        i++;
    }
    std::cout << BOLDWHITE << "\n---" << std::endl;
    if (current_folder != ".")
        std::cout << BOLDGREEN << "b- .." << std::endl;
    std::cout << YELLOW << "h- help" << std::endl;

    std::cout << RED << "q- quit " << (emoji ? "😥" : "") << std::endl;
    std::cout << RESET;
    std::cout << std::endl;
}

void Display::display_helper()
{
    std::cout << BOLDCYAN << "-------- HELPER PAGE --------\n\n" << RESET;
    std::cout << BOLDGREEN << "-ac" << RESET
              << ": Add a new command to the current file\n";
    std::cout << BOLDWHITE << "\t usage: -ac new_command\n" << RESET;
    std::cout << YELLOW << "\t exemple: -ac ls -a\n\n" << RESET;

    std::cout << BOLDGREEN << "-cb" << RESET
              << ": Allows you to create a new command combo, allowing you to "
                 "launch several commands in a row by pressing a single key\n";
    std::cout << BOLDWHITE
              << "\t usage: -cb command_1 [cb] command_2 [cb] command_n \n"
              << RESET;
    std::cout << BOLDWHITE
              << "\t usage: -cb {combo_name} command_1 [cb] command_2 "
                 "[cb] command_n \n"
              << RESET;
    std::cout << YELLOW << "\t exemple: -cb ls -a [cb] pwd [cb] echo [?] \n"
              << RESET;
    std::cout << YELLOW
              << "\t exemple: -cb {PUSH} git add [?] [cb] git status [cb] git "
                 "commit -m \"[?]\" [cb] git push origin [?]\n\n"
              << RESET;

    std::cout << BOLDGREEN << "-af" << RESET
              << ": Add a new folder in de current directory\n";
    std::cout << BOLDWHITE << "\t usage: -af new_folder\n" << RESET;
    std::cout << YELLOW << "\t exemple: -af git commands\n\n" << RESET;

    std::cout << BOLDGREEN << "-de" << RESET
              << ": Delete a command or a folder\n";
    std::cout << BOLDWHITE << "\t usage: -de number_command_or_folder\n"
              << RESET;
    std::cout << YELLOW << "\t exemple: -de 5\n\n" << RESET;

    std::cout << BOLDGREEN << "-rf" << RESET
              << ": Reset the contents of a folder\n";
    std::cout << BOLDWHITE << "\t usage: -rf number_of_the_folder\n" << RESET;
    std::cout << YELLOW << "\t exemple: -rf 5\n\n" << RESET;

    std::cout << BOLDGREEN << "-ra" << RESET
              << ": Reset the contents of the entire folder\n";
    std::cout << BOLDWHITE << "\t usage: -ra \n" << RESET;

    std::cout << BOLDGREEN << "-mv" << RESET
              << ": Move element to another position\n";
    std::cout << BOLDWHITE
              << "\t usage: -mv source_position destination_position \n"
              << RESET;
    std::cout << YELLOW << "\t exemple: -mv 2 5\n\n" << RESET;

    std::cout << BOLDGREEN << "[?]" << RESET
              << ": If you add [?] during the creation of your command, "
                 "during the execution you will have the possibility to "
                 "replace them by the content of your choice\n";
    std::cout << BOLDWHITE << "\t usage: [?]\n" << RESET;
    std::cout << YELLOW << "\t exemple: -ac git commit -m \"[?]\"\n" << RESET;
    std::cout << YELLOW << "\t exemple: -cb ls [?] [cb] cd [?] \n" << RESET;

    std::cout << BOLDWHITE << "\n---" << std::endl;
    std::cout << BOLDGREEN << "Press " << RESET << BOLDRED << "Enter" << RESET
              << BOLDGREEN << " to back to Cpad" << std::endl;
    std::cout << RESET;
    std::cout << std::endl;
}