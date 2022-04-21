#include "../json-reader.hh"
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main(int argc, char **argv) {
  auto map = JsonReader::instance().readJson(
      "/home/aminou/Perso/Command-Note-Pad/test-ressources/json1.json");
  for (auto &elem : map) {
    std::cout << "key: " << elem.first << '\n';
    for (size_t i = 0; i < elem.second.get_elements().size(); i++)
      std::cout << "values[" << i
                << "] = " << elem.second.get_elements()[i].get_name() << '\n';
    std::cout << "\n";
  }
}