#include "display.hh"

void Display::display (std::string &key, std::map<std::string, Folder> &map)
{
    //HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    std::cout << "Current folder : " << key << std::endl;
    int i = 1;
    auto elms = map[key].get_elements();
    for(auto elm : elms)
    {
        std::cout << std::to_string(i) << "- " << elm.get_name() << std::endl;
        i++;
    }
}