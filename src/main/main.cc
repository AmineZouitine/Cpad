#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

#include "../executor.hh"
#include "../json-reader.hh"

using json = nlohmann::json;

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cout << "Ajoute le un fichier test de ressource-test, exemple : "
                     "test-ressources/json1.json"
                  << '\n';
        return 1;
    }
    auto map = JsonReader::instance().readJson(argv[1]);
    std::string command_number;
    std::string command_name;
    std::string current_folder = ".";
    bool is_folder = false;
    do
    {
        // -> TON AFFICHAGE VALAT
        // display(current_folder, map);
        std::cout << "Choose your command -> ";
        std::cin >> command_number;
        command_name = map[current_folder]
                           .get_elements()[std::stoi(command_number) - 1]
                           .get_name();
        if (map[current_folder]
                .get_elements()[std::stoi(command_number) - 1]
                .get_is_folder())
        {
            current_folder = command_name;
            is_folder = true;
        }
        else
            is_folder = false;

    } while (command_number != "q" && !is_folder
             && Executor::instance().execute(command_name));
}