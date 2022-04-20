#include <iostream>
#include "json-reader.hh"


int main(int argc, char **argv)
{
    auto folders = JsonReader::instance().readJson("../../test-ressources/json1.json");
    for (const auto& format : folders)
        std::cout << format.second;
}