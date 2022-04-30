#pragma once

#include <algorithm>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

void home_file_check(std::ifstream &cpad_file, std::string &home_path);

bool check_arguments(int argc, char** argv);

bool is_same_emoji_value(std::vector<std::string> lines, bool value);

void rewrite(std::string& path, bool display_emoji);

std::vector<std::string> get_all_lines(std::string& home_path);