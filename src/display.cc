#include "display.hh"

#define RESET "\033[0m"
#define BOLD "\033[1m"
#define BOLDBLUE "\033[1m\033[34m" /* Bold Blue */
#define BOLDRED "\033[1m\033[31m" /* Bold Red */
#define BOLDGREEN "\033[1m\033[32m" /* Bold Green */
#define YELLOW "\033[33m" /* Yellow */
#define RED "\033[31m" /* RED */

void Display::display(std::string &key, std::map<std::string, Folder> &map)
{
    std::cout << "📁 : " << BOLDGREEN << key << std::endl << std::endl;
    std::cout << RESET;
    int i = 1;
    auto elms = map[key].get_elements();
    for (auto elm : elms)
    {
        if (elm.get_is_folder())
            std::cout << BOLD << std::to_string(i) << RESET << " ➜ " << BOLDBLUE << elm.get_name()
                      << " 🗂 " << std::endl;
        else
            std::cout << BOLD << std::to_string(i) << RESET << " ➜ " << elm.get_name()
                      << std::endl;
        std::cout << RESET;
        i++;
    }
    std::cout << BOLDGREEN << "---" << std::endl;
    if (key != ".")
        std::cout << "b- .." << std::endl;
    std::cout << YELLOW << "h- help" << std::endl;

    std::cout << RED << "q- quit" << std::endl;
    std::cout << RESET;
    std::cout << std::endl;
}