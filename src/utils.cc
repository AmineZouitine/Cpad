#include "utils.hh"

void home_file_check(std::ifstream &cpad_file, std::string &home_path)
{
    cpad_file.open(home_path);
    if (!cpad_file)
    {
        std::ofstream outfile(home_path);
        outfile << "EMOJI TRUE\nCURRENT .\n--STOP--";
    }
}


bool check_arguments(int argc, std::vector<std::string>& lines, char** argv)
{
    std::string False = "0";
    std::string True = "1";
    if (argc == 2 && argv[1] == False)
        return false;
    if (argc == 2 && argv[1] == True)
        return true;
    std::stringstream stream(lines[0]);
    std::string token;
    stream >> token;
    stream >> token;
    return token == "TRUE" ? true : false;
    
}

bool is_same_emoji_value(std::vector<std::string>& lines, bool value)
{
    std::stringstream stream(lines[0]);
    std::string token;
    stream >> token;
    stream >> token;
    return (token == "TRUE" && value == true) || (token == "FALSE" && value == false);
}

void rewrite(std::string& path, std::vector<std::string>& lines, bool display_emoji)
{
    if (is_same_emoji_value(lines, display_emoji))
        return;

    std::ofstream MyFile(path);
    MyFile << "EMOJI " << (display_emoji ? "TRUE" : "FALSE") << '\n';
    for (size_t i = 1; i < lines.size(); i++)
        MyFile << lines[i] << '\n';
}

std::vector<std::string> get_all_lines(std::string& home_path)
{
    std::vector<std::string> lines;
    std::string line;
    std::ifstream file(home_path);
    while (std::getline(file, line))
        lines.push_back(line);
        

    return lines;
}