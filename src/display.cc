#include "display.hh"

#define RESET "\033[0m"
#define BOLD "\033[1m"
#define BOLDBLUE "\033[1m\033[34m" /* Bold Blue */
#define BOLDRED "\033[1m\033[31m" /* Bold Red */
#define BOLDGREEN "\033[1m\033[32m" /* Bold Green */
#define YELLOW "\033[33m" /* Yellow */
#define RED "\033[31m" /* RED */
#define BOLDWHITE "\033[1m\033[37m" /* Bold White */
#define BOLDCYAN "\033[1m\033[36m" /* Bold Cyan */

void Display::display(std::string &key, std::map<std::string, Folder> &map)
{
    std::cout << "📁 : " << BOLDGREEN << key << std::endl << std::endl;
    std::cout << RESET;
    int i = 1;
    auto elms = map[key].get_elements();
    for (auto elm : elms)
    {
        if (elm.get_is_folder())
            std::cout << BOLD << std::to_string(i) << RESET << " ➜ " << BOLDBLUE
                      << elm.get_name() << " 📁 " << std::endl;
        else
            std::cout << BOLD << std::to_string(i) << RESET << " ➜ "
                      << elm.get_name() << std::endl;
        std::cout << RESET;
        i++;
    }
    std::cout << BOLDWHITE << "\n---" << std::endl;
    if (key != ".")
        std::cout << BOLDGREEN << "b- .." << std::endl;
    std::cout << YELLOW << "h- help" << std::endl;

    std::cout << RED << "q- quit 😥" << std::endl;
    std::cout << RESET;
    std::cout << std::endl;
}

void Display::display_helper()
{
    std::cout << BOLDCYAN << "-------- HELPER PAGE --------\n\n" << RESET;
    std::cout << "-ac : add a new command to the current file\n";
    std::cout << BOLDWHITE << "\t usage : -ac new_command\n\n" << RESET;

    std::cout << "-af : add a new folder in de current directory\n";
    std::cout << BOLDWHITE << "\t usage : -af new_folder\n\n" << RESET;

    std::cout << "-de : delete a command or a folder\n";
    std::cout << BOLDWHITE << "\t usage : -de number_command_or_folder\n\n"
              << RESET;

    std::cout << "-rf : reset the contents of a folder\n";
    std::cout << BOLDWHITE << "\t usage : -rf number_of_the_folder\n\n"
              << RESET;

    std::cout << "-ra : reset the contents of the entire folder\n";
    std::cout << BOLDWHITE << "\t usage : -ra \n\n" << RESET;

    std::cout << "[?] : If you add [?] during the creation of your command, "
                 "during the execution you will have the possibility to "
                 "replace them by the content of your choice\n";
    std::cout << BOLDWHITE << "\t usage : git commit -m \"[?]\"\n" << RESET;
    std::cout << BOLDWHITE << "\t usage : echo [?] | cat [?] [?] \n" << RESET;

    std::cout << BOLDWHITE << "\n---" << std::endl;
    std::cout << BOLDGREEN << "b- back to cpad" << std::endl;
    std::cout << RED << "q- quit cpad" << std::endl;
    std::cout << RESET;
    std::cout << std::endl;
}