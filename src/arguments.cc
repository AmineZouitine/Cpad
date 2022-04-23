
#include "arguments.hh"

void parse_cmd(int argc, char **argv, std::map<std::string, Folder> &map,
               std::string &path, std::string &folder)
{
    std::string command;
    for (int i = 2; i < argc; i++)
    {
        command += argv[i];
    }
    Convertor::instance().add_command(map, folder, command);
    Convertor::instance().write(map, path);
}

void parse_folder(int argc, char **argv, std::map<std::string, Folder> &map,
               std::string &path, std::string &folder)
{
    std::string new_folder;
    for (int i = 2; i < argc; i++)
    {
        new_folder += argv[i];
    }
    Convertor::instance().add_folder(map, folder, new_folder);
    Convertor::instance().write(map, path);
}

void parse_arg(int argc, char **argv, std::map<std::string, Folder> &map,
               std::string &path)
{
    std::string folder;
    if (argv[argc - 1][0] == '[')
        folder = argv[argc - 1].substr(1, argv[argc - 1].length() - 2);
    else
        folder = ".";
    // il faut gerer le cas ou l'utilisateur donne un folder inexistant ?
    if (strcmp(argv[1],"-ac") == 0)
        parse_cmd(argc, argv, map, path, folder);
    else if (strcmp(argv[1],"-af") == 0)
        parse_folder(argc, argv, map, path, folder);

    else
    {
        std::cerr << "Invalid argument: " << argv[1] << "\n";
        exit(1);
    }
}