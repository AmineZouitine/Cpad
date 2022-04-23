#include "executor.hh"

#include <iostream>
#include <memory>
#include <stdlib.h>

#define RESET "\033[0m"
#define BOLDBLUE "\033[1m\033[34m" /* Bold Blue */
#define BOLDRED "\033[1m\033[31m" /* Bold Red */
#define BOLDGREEN "\033[1m\033[32m" /* Bold Green */
#define YELLOW "\033[33m" /* Yellow */

bool Executor::execute(std::string &command_name, bool is_folder)
{
    system("clear");
    if (!is_folder)
    {
        std::cout << "\n\nExecution of -- " << BOLDGREEN << command_name
                  << RESET << std::endl;
        std::cout << "---\n";
        system(command_name.c_str());
        std::cout << "---\n\n";
    }
    return true;
}