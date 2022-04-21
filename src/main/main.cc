#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

#include "../executor.hh"
#include "../json-reader.hh"

using json = nlohmann::json;

void args_count_check(int argc)
{
    if (argc != 1)
    {
        std::cout << "Le main ne prend aucun argument" << '\n';
        exit(1);
    }
}

void home_file_check(std::ifstream &json_file, std::string &home_path)
{
    json_file.open(home_path);
    if (!json_file)
    {
        std::ofstream outfile(home_path);
        outfile << "{}";
    }
}

void command_launcher(std::map<std::string, Folder> &map,
                      std::string &command_number, std::string &current_folder,
                      std::string &command_name)
{
    bool is_folder = false;
    do
    {
        // -> TON AFFICHAGE VALAT
        // display(current_folder, map);
        std::cout << "Choose your command -> ";
        std::cin >> command_number;
        if (std::stoi(command_number)
            > map[current_folder].get_elements().size())
            continue;
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

    } while (command_number != "q"
             && Executor::instance().execute(command_name, is_folder));
}

int main(int argc, char **argv)
{
    args_count_check(argc);

    std::ifstream json_file;
    std::string home_path = std::string(getenv("HOME")) + "/.cpad.json";

    home_file_check(json_file, home_path);

    auto map = JsonReader::instance().readJson(home_path);

    std::string command_number;
    std::string command_name;
    std::string current_folder = ".";

    command_launcher(map, command_number, current_folder, command_name);
}