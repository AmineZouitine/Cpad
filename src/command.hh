#pragma once

#include "element.hh"
#include <string>

class Command : public Element {
public:
  Command(std::string &command_name);
  std::string &get_command_name() const;
  void execute_command() const;
};