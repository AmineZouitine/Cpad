#pragma once

#include "command.hh"
#include <vector>

class Folder {
public:
  Folder(std::vector<Element> &elements);
  void add_command(std::string &command_name);
  void add_folder(std::string &folder_name);

  friend std::ostream &operator<<(std::ostream &ostr, Folder &folder);

  std::vector<Element> &get_elements();

private:
  std::vector<Element> elements_;
};

std::ostream &operator<<(std::ostream &ostr, const Folder &folder);