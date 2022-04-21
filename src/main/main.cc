#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

#include "../json-reader.hh"
#include "../executor.hh"

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
    for (auto &elem : map)
    {
        std::cout << "key: " << elem.first << '\n';
        for (size_t i = 0; i < elem.second.get_elements().size(); i++)
            std::cout << "values[" << i << "] = name -> "
                      << elem.second.get_elements()[i].get_name()
                      << " || is_folder -> "
                      << elem.second.get_elements()[i].get_is_folder() << '\n';
        std::cout << "\n";
    }
    std::string current_folder = ".";
    std::string command_number;
    std::cout << "Choose your command -> ";
    std::cin >> command_number;
    auto command_name = map[current_folder].get_elements()[std::stoi(command_number) - 1].get_name();
    Executor::instance().execute(command_name);
}