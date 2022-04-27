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
        else if (!elm.get_is_combo())
            std::cout << BOLD << std::to_string(i) << RESET << " ➜ "
                      << elm.get_name() << std::endl;
        else
        {
            if (elm.get_name().empty())
            {
                if (elm.get_combo_elements_().size() > 0)
                    std::cout << BOLD << std::to_string(i) << RESET << " ➜ "
                              << elm.get_combo_elements_()[0].get_name()
                              << std::endl;

                std::string space = " ";
                for (size_t i = 1; i < elm.get_combo_elements_().size(); i++)
                {
                    std::cout << space << RESET << " 🔸 "
                              << elm.get_combo_elements_()[i].get_name()
                              << std::endl;
                    // space += "  ";
                }
            }
            else
            {
                std::cout << BOLD << std::to_string(i) << RESET << " ➜ "
                          << BOLDRED << elm.get_name() << RESET << " 🔸"
                          << std::endl;
            }
        }
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
    std::cout << YELLOW << "\t exemple: git commit -m \"[?]\"\n" << RESET;
    std::cout << YELLOW << "\t usage: echo [?] | cat [?] [?] \n" << RESET;

    std::cout << BOLDWHITE << "\n---" << std::endl;
    std::cout << BOLDGREEN << "b- back to cpad" << std::endl;
    std::cout << RED << "q- quit cpad" << std::endl;
    std::cout << RESET;
    std::cout << std::endl;
}