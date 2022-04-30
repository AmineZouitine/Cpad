#pragma once

#include <iostream>
#include <map>
// #include <windows.hh>

#include "element.hh"
#include "folder.hh"
#include "singleton.hh"
#include "error-handling.hh"
#include "executor.hh"

#define RESET "\033[0m"
#define BOLD "\033[1m"
#define WHITE "\033[37m"
#define BOLDBLUE "\033[1m\033[34m" /* Bold Blue */
#define BOLDRED "\033[1m\033[31m" /* Bold Red */
#define UNDERBOLDRED "\033[4m\033[1m\033[31m" /* Underligned Bold Red */
#define RED "\033[31m" /* RED */
#define BOLDGREEN "\033[1m\033[32m" /* Bold Green */
#define GREEN "\033[0m\033[32m" /*Green */
#define YELLOW "\033[33m" /* Yellow */
#define BOLDWHITE "\033[1m\033[37m" /* Bold White */
#define BOLDCYAN "\033[1m\033[36m" /* Bold Cyan */
#define BOLDMAGENTA "\033[1m\033[35m" /* Bold Magenta */

class Display : public Singleton<Display>
{
public:
    using error_map = std::map<ErrorHandling::Error, std::pair<std::string, std::string>>;
    using executor_map = std::map<Executor::ExecutionType, std::pair<std::string, std::string>>;
    using Error = ErrorHandling::Error;
    using Exec = Executor::ExecutionType;

    void display_error(ErrorHandling::Error error, bool emoji);
    void display_executor(Executor::executor_result executor,
                          Element &element_combo, bool emoji, bool clear = true);
    void display(std::map<std::string, Folder> &map, std::string& current_folder, bool emoji);
    void display_helper();
    void set_display_line(std::string& display_line, std::string end_str, std::string emoji_str, std::string replace, std::string color,bool emoji);
private:
    bool is_template(std::string command);
    void remplace_templates(std::string &command, bool clear);
    bool cd_exec(std::string command);
    void execute(std::string& command, bool emoji, bool clear);
    void execute_combo(std::string &command, std::string display_line,
                       Element &combo_elem, bool emoji);
};